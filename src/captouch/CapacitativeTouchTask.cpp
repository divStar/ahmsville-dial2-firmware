//
// Created by Igor Voronin on 29.07.23.
//

#include "CapacitativeTouchTask.h"

CapacitativeTouchTask::CapacitativeTouchTask(byte sendingPin, byte receivingPin)
        : sensor(CapacitiveSensor(sendingPin, receivingPin)) {
    setInterval(0);
    setIterations(TASK_FOREVER);

    tapTypes[0] = TapTypeEnum(DEFAULT_PROXIMITY_THRESHOLD);
    tapTypes[1] = TapTypeEnum(DEFAULT_SLIGHT_TAP_THRESHOLD);
    tapTypes[2] = TapTypeEnum(DEFAULT_TAP_THRESHOLD);
    tapTypes[3] = TapTypeEnum(DEFAULT_STRONG_TAP_THRESHOLD);
    tapTypes[4] = TapTypeEnum(DEFAULT_MAX_TAP_THRESHOLD);
}

CapacitativeTouchTask::~CapacitativeTouchTask() {
    delete (lastTap);
}

void CapacitativeTouchTask::onSetup() {
    sensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void CapacitativeTouchTask::onCallback() {
    readValues();
}

void CapacitativeTouchTask::readValues() {
    long sensorValue = sensor.capacitiveSensor(SAMPLES);

    TapTypeEnum *currentTap = nullptr;
    for (auto &tapType: tapTypes) {
        if (!tapType.isValid()) {
            break;
        }
        if (sensorValue >= tapType.getThreshold()) {
            currentTap = &tapType;
        }
    }

    if (currentTap != nullptr &&
        (lastTap == nullptr ||
         currentTap->getThreshold() >= lastTap->getThreshold())) {
        // if currentTap is not a nullptr and lasttap is either a nullptr or of a lesser threshold
        if (touchStart == 0) {
            touchStart = millis();
        }
        if (millis() - touchStart >= TIME_THRESHOLD) {
            // Create and output serialized JSON
            sendData(currentTap->getThreshold(), sensorValue);
            lastTap = currentTap;
        }
    } else if (currentTap == nullptr || currentTap->getThreshold() < lastTap->getThreshold()) {
        // if currentTap is a nullptr or its threshold is lesser than that of lasttap
        touchStart = 0;
        lastTap = nullptr;
    }
}

void CapacitativeTouchTask::sendData(int threshold, long sensorValue) {
    StaticJsonDocument<BUFFER_SIZE> jsonDoc;
    jsonDoc["type"] = "captouch";
    jsonDoc["thresholdValue"] = threshold;
    jsonDoc["value"] = sensorValue;
    jsonDoc["time"] = millis();

    serializeJson(jsonDoc, SerialUSB);
    SerialUSB.println();
}
