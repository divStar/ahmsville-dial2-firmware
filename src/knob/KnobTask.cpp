//
// Created by Igor Voronin on 06.07.23.
//

#include "KnobTask.h"

KnobTask::KnobTask(const char *name, int pin0, int pin1, int pinInterrupt0, int pinInterrupt1)
        : name(name), knob(new RotaryEncoder(pin0, pin1, pinInterrupt0, pinInterrupt1)) {}

void KnobTask::onSetup() {
    Log.traceln("Auto-Calibrating %s...", this->name);
    auto startMillis = millis();

    while (millis() - startMillis < 500) {
        // reading values in order to prevent an "initial spike" of wrong values in the beginning
        knob->readValues();
        startMillis = startMillis; // NOOP to satisfy Cling-Tidy
    }
}

void KnobTask::onCallback() {
    knob->readValues();

    if (knob->getRotationDelta() > ROTATION_THRESHOLD
         || knob->getRotationDelta() < -ROTATION_THRESHOLD) {
        // Create and output serialized JSON
        StaticJsonDocument<BUFFER_SIZE> jsonDoc;
        jsonDoc["type"] = "knob";
        jsonDoc["name"] = this->name;
        jsonDoc["time"] = millis();
        jsonDoc["rotationDelta"] = knob->getRotationDelta();

        serializeJson(jsonDoc, SerialUSB);
        SerialUSB.println();
    }
}
