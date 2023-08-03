#include "KnobTask.h"

KnobTask::KnobTask(const char *name, int pin0, int pin1, int pinInterrupt0, int pinInterrupt1)
        : ISchedulableDialTask("knob"), name(name), knob(RotaryEncoder(pin0, pin1, pinInterrupt0, pinInterrupt1)) {
    setInterval(0);
    setIterations(TASK_FOREVER);
}

void KnobTask::onSetup() {
    Log.traceln("[KNOB] Auto-Calibrating '%s'...", name);
    auto startMillis = millis();

    while (millis() - startMillis < 500) {
        // reading values in order to prevent an "initial spike" of wrong values in the beginning
        knob.readValues();
        startMillis = startMillis; // NOOP to satisfy Cling-Tidy
    }
}

void KnobTask::onCallback() {
    knob.readValues();
    auto rotationAngleDelta = knob.getRotationAngleDelta();

    if (rotationAngleDelta > ROTATION_THRESHOLD || rotationAngleDelta < -ROTATION_THRESHOLD) {
        sendData();
    }
}

void KnobTask::sendData() {
    // Create and output serialized JSON
    StaticJsonDocument<BUFFER_SIZE> jsonDoc;
    jsonDoc["type"] = getTaskType();
    jsonDoc["name"] = name;
    jsonDoc["time"] = millis();
    jsonDoc["rotationDelta"] = knob.getRotationAngleDelta();

    serializeJson(jsonDoc, SerialUSB);
    SerialUSB.println();
}