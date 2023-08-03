#include "HapticTask.h"

HapticTask::HapticTask(LinkedList<InputMessageDto *> &messagesToProcess)
        : ISchedulableDialTask("haptic"), ISerialPortUser(configuredSerialPort()),
          IMessageConsumer(messagesToProcess) {
    setInterval(0);
    setIterations(TASK_FOREVER);
    filterDoc["type"] = true;
    filterDoc["strength"] = true;
}

void HapticTask::onCallback() {
    for (int rawDataDtoIndex = messagesToProcess.size() - 1; rawDataDtoIndex >= 0; --rawDataDtoIndex) {
        InputMessageDto *rawDataDto = messagesToProcess.get(rawDataDtoIndex);
        char taskType[30];
        sprintf(taskType, R"("type":"%s")", getTaskType());

        if (strstr(rawDataDto->getRawInputData(), taskType) != nullptr) {
            StaticJsonDocument<BUFFER_SIZE> jsonDoc;
            DeserializationError error = deserializeJson(jsonDoc, rawDataDto->getRawInputData(),
                                                         strlen(rawDataDto->getRawInputData()),
                                                         DeserializationOption::Filter(filterDoc));
            if (error) {
                char errorMessage[150];
                sprintf(errorMessage, "[%s] deserializeJson() failed: %s", getTaskType(), error.c_str());
                JsonSerializer::sendJsonError(serial, getTaskType(), "H1", errorMessage);

                Log.errorln(errorMessage);
                return;
            }

            HapticTask::useData(jsonDoc.as<JsonVariantConst>());
            messagesToProcess.get(rawDataDtoIndex)->setValid(false);
        }
    }
}

void HapticTask::useData(JsonVariantConst jsonData) {
    if (isValidData(jsonData)) {
        Log.traceln("[%s] Setting haptic with strength %d", getTaskType(), jsonData["strength"].as<byte>());

        analogWrite(HAPTIC_PIN, jsonData["strength"].as<byte>());
    }
}

bool HapticTask::isValidData(JsonVariantConst jsonData) {
    return jsonData["type"] == getTaskType() &&
           jsonData["strength"].is<byte>();
}
