//
// Created by Igor Voronin on 06.07.23.
//

#ifndef DIALER_KNOBTASK_H
#define DIALER_KNOBTASK_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "RotaryEncoder.h"
#include "interfaces/ISchedulableDialTask.h"

class KnobTask : public ISchedulableDialTask {
public:
    explicit KnobTask(const char *name, int pin0, int pin1, int pinInterrupt0, int pinInterrupt1);

    void onSetup() override;

    void onCallback() override;

private:
    static const int BUFFER_SIZE = 96;
    constexpr static const float ROTATION_THRESHOLD = 0.004;

    const char *name;

    RotaryEncoder knob;

    void sendData();
};


#endif //DIALER_KNOBTASK_H
