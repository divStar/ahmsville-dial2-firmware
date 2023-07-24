//
// Created by Igor Voronin on 06.07.23.
//

#include "KnobTask.h"

KnobTask::KnobTask(const char *name, int pin0, int pin1, int pinInterrupt0, int pinInterrupt1)
        : name(name), knob(RotaryEncoder(pin0, pin1, pinInterrupt0, pinInterrupt1)) {}

void KnobTask::onSetup() {}

void KnobTask::onCallback() {
    knob.readValues();

    if (millis() > 7000 &&
        (knob.getRotationDelta() > ROTATION_THRESHOLD
         || knob.getRotationDelta() < -ROTATION_THRESHOLD)) {
        // Create and output serialized JSON
        StaticJsonDocument<BUFFER_SIZE> jsonDoc;
        jsonDoc["type"] = "knob";
        jsonDoc["name"] = this->name;
        jsonDoc["time"] = millis();
        jsonDoc["rotationDelta"] = knob.getRotationDelta();

        serializeJson(jsonDoc, SerialUSB);
        SerialUSB.println();
    }
}
