//
// Created by Igor Voronin on 06.07.23.
//

#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include "logger/Logger.h"
#include "KalmanFilter.h"

class RotaryEncoder {
public:
    RotaryEncoder(int pin0, int pin1, int pinInterrupt0, int pinInterrupt1);

    void readValues();

    [[nodiscard]] float getRotationDelta() const;

private:
    static const int SENSOR_MIDPOINT = 500;

    int pin0;
    int pin1;

    float *values = new float[2]{0.0, 0.0};
    float previousRotationAngle = 0;
    float rotationDelta = 0;

    KalmanFilter filteredSensor1Value;
    KalmanFilter filteredSensor2Value;

    float getRotationAngle();

    [[nodiscard]] float getRotationAngleDelta(float currentRotationAngle) const;
};

#endif //ROTARYENCODER_H
