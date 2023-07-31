//
// Created by Igor Voronin on 29.07.23.
//

#include "CapacitativeTouchTask.h"

CapacitativeTouchTask::CapacitativeTouchTask(byte sendingPin, byte receivingPin)
        : ISchedulableDialTask("captouch"), sensor(CapacitiveSensor(sendingPin, receivingPin)) {
    setInterval(0);
    setIterations(TASK_FOREVER);
}

void CapacitativeTouchTask::onSetup() {
    sensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void CapacitativeTouchTask::onCallback() {
    long sensorValue = sensor.capacitiveSensor(SAMPLES);

    if (sensorValue > PROXIMITY_THRESHOLD) {
        // Create and output serialized JSON
        sendData(sensorValue);
    }
}

void CapacitativeTouchTask::sendData(long sensorValue) {
    StaticJsonDocument<BUFFER_SIZE> jsonDoc;
    jsonDoc["type"] = getTaskType();
    jsonDoc["value"] = sensorValue;
    jsonDoc["time"] = millis();

    serializeJson(jsonDoc, SerialUSB);
    SerialUSB.println();
}
