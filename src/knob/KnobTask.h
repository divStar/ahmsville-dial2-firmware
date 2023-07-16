//
// Created by Igor Voronin on 06.07.23.
//

#ifndef DIALER_KNOBTASK_H
#define DIALER_KNOBTASK_H

#include <Arduino.h>
#include "DialTask.h"
#include "RotaryEncoder.h"

class KnobTask : public DialTask {
public:
    explicit KnobTask(int pin0, int pin1, int pinInterrupt0, int pinInterrupt1);

    void onSetup() override;

    void onCallback() override;

private:
    RotaryEncoder knob;
};


#endif //DIALER_KNOBTASK_H
