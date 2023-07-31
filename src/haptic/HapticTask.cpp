//
// Created by Igor Voronin on 25.07.23.
//

#include "HapticTask.h"

HapticTask::HapticTask(LinkedList<RawDataDto *> *messagesToProcess)
        : ISchedulableDialTask("haptic"), messagesToProcess(messagesToProcess) {
    setInterval(0);
    setIterations(TASK_FOREVER);
    filterDoc["type"] = true;
    filterDoc["strength"] = true;
}

void HapticTask::onSetup() {
}

void HapticTask::onCallback() {
    for (int rawDataDtoIndex = messagesToProcess->size() - 1; rawDataDtoIndex >= 0; --rawDataDtoIndex) {
        RawDataDto *rawDataDto = messagesToProcess->get(rawDataDtoIndex);
        char taskType[30];
        sprintf(taskType, R"("type":"%s")", getTaskType());

        if (strstr(rawDataDto->getRawData(), taskType) != nullptr) {
            StaticJsonDocument<BUFFER_SIZE> jsonDoc;
            DeserializationError error = deserializeJson(jsonDoc, rawDataDto->getRawData(),
                                                         strlen(rawDataDto->getRawData()),
                                                         DeserializationOption::Filter(filterDoc));
            if (error) {
                char errorMessage[150];
                sprintf(errorMessage, "[HAPTIC] deserializeJson() failed: %s", error.c_str());
                ErrorSerializer::serializeError(getTaskType(), "H1", errorMessage);

                Log.errorln(errorMessage);
                return;
            }

            HapticTask::applyData(jsonDoc.as<JsonVariantConst>());
            messagesToProcess->get(rawDataDtoIndex)->setValid(false);
        }
    }
}

void HapticTask::applyData(JsonVariantConst jsonData) {
    if (isValidData(jsonData)) {
        Log.traceln("[HAPTIC] Setting haptic with strength %d", jsonData["strength"].as<byte>());

        analogWrite(HAPTIC_PIN, jsonData["strength"].as<byte>());
    }
}

bool HapticTask::isValidData(JsonVariantConst jsonData) {
    return jsonData["type"] == getTaskType() &&
           jsonData["strength"].is<byte>();
}