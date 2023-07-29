//
// Created by Igor Voronin on 29.07.23.
//

#include "CapacitativeTouchTask.h"

CapacitativeTouchTask::CapacitativeTouchTask()
        : sensor(new CapacitiveSensor(9, 8)) {
    this->setInterval(0);
    this->setIterations(TASK_FOREVER);
}

void CapacitativeTouchTask::onSetup() {
    sensor->set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void CapacitativeTouchTask::onCallback() {
    long sensorValue = sensor->capacitiveSensor(50);
    Log.traceln("CapTouch sensor value: %l", sensorValue);
}
