//
// Created by Igor Voronin on 06.07.23.
//

#ifndef DIALER_KNOBTASK_H
#define DIALER_KNOBTASK_H

#include <Arduino.h>
#include "DialTask.h"
#include "RotaryEncoder.h"
#include "ArduinoJson.h"

class KnobTask : public DialTask {
public:
    explicit KnobTask(const char *name, int pin0, int pin1, int pinInterrupt0, int pinInterrupt1);

    void onSetup() override;

    void onCallback() override;

private:
    static const int BUFFER_SIZE = 96;
    constexpr static const float ROTATION_THRESHOLD = 0.004;
//    constexpr static const float ROTATION_THRESHOLD = 1.0;

    const char *name;

    RotaryEncoder knob;
};


#endif //DIALER_KNOBTASK_H
