//
// Created by Igor Voronin on 25.07.23.
//

#include "HapticTask.h"

HapticTask::HapticTask(LinkedList<RawDataDto *> *messagesToProcess)
        : messagesToProcess(messagesToProcess) {
    filterDoc["type"] = true;
    filterDoc["strength"] = true;
}

void HapticTask::onSetup() {
}

void HapticTask::onCallback() {
    for (int rawDataDtoIndex = messagesToProcess->size() - 1; rawDataDtoIndex >= 0; --rawDataDtoIndex) {
        RawDataDto *rawDataDto = messagesToProcess->get(rawDataDtoIndex);
        if (strstr(rawDataDto->getRawData(), R"("type":"haptic")") != nullptr) {
            StaticJsonDocument<BUFFER_SIZE> jsonDoc;
            DeserializationError error = deserializeJson(jsonDoc, rawDataDto->getRawData(),
                                                         strlen(rawDataDto->getRawData()),
                                                         DeserializationOption::Filter(filterDoc));
            if (error) {
                Log.errorln("(Haptic) deserializeJson() failed: %s", error.c_str());
                return;
            }

            HapticTask::applyData(jsonDoc.as<JsonVariantConst>());
            messagesToProcess->get(rawDataDtoIndex)->setValid(false);
        }
    }
}

void HapticTask::applyData(JsonVariantConst jsonData) {
    if (isValidData(jsonData)) {
        Log.traceln("Setting haptic with strength %d", jsonData["strength"].as<byte>());

        analogWrite(HAPTIC_PIN, jsonData["strength"].as<byte>());
    }
}

bool HapticTask::isValidData(JsonVariantConst jsonData) {
    return jsonData["type"] == "haptic" &&
           jsonData["strength"].is<byte>();
}
