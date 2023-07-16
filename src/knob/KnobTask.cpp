//
// Created by Igor Voronin on 06.07.23.
//

#include "KnobTask.h"

KnobTask::KnobTask(int pin0, int pin1, int pinInterrupt0, int pinInterrupt1)
        : knob(RotaryEncoder(pin0, pin1, pinInterrupt0, pinInterrupt1)) {}

void KnobTask::onSetup() {
//    attachInterrupt(digitalPinToInterrupt(knob.pinInterrupt1), [](){knob.onRotate(); }, CHANGE);
}

void KnobTask::onCallback() {
    knob.readValues();
    Log.traceln("%d | %d | %d | %d | %d | %u",
                knob.getPin0Value(),
                knob.getPin1Value(),
                knob.getPin0InterruptValue(),
                knob.getPin1InterruptValue(),
                knob.getCurrentRotationDirection(),
                millis()
    );

    // if (pinInterrupt0) == 1 then pinInterrupt1 = 0 && pin0 = ~520 && pin1 = ~320
    // if (pinInterrupt0) == 1 then pinInterrupt1 = 0 && pin0 = ~520 && pin1 = ~700
    // if (pinInterrupt1) == 1 then pinInterrupt0 = 0 && pin1 = ~520 && pin0 = ~320
    // if (pinInterrupt1) == 1 then pinInterrupt0 = 0 && pin1 = ~520 && pin0 = ~700
}
