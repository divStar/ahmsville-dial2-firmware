//
// Created by Igor Voronin on 06.07.23.
//

#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int pin0, int pin1, int pinInterrupt0, int pinInterrupt1)
        : pin0(pin0), pin1(pin1),
          filteredSensor1Value(0.0), filteredSensor2Value(0.0) {
    pinMode(pin0, INPUT);
    pinMode(pin1, INPUT);
    pinMode(pinInterrupt0, INPUT);
    pinMode(pinInterrupt1, INPUT);
}

void RotaryEncoder::readValues() {
    // Read new values
    values[0] = static_cast<float>(analogRead(pin0));
    values[1] = static_cast<float>(analogRead(pin1));

    // Smoothen the analog values
    values[0] = filteredSensor1Value.update(values[0]);
    values[1] = filteredSensor2Value.update(values[1]);

    rotationDelta = getRotationAngle();
}

float RotaryEncoder::getRotationDelta() const {
    return rotationDelta;
}

float RotaryEncoder::getRotationAngle() {
    // Get sensor values
    auto normalizedSensor1Value = values[0] - SENSOR_MIDPOINT;
    auto normalizedSensor2Value = values[1] - SENSOR_MIDPOINT;

    // Calculate intermediate values
    auto currentRotationAngle = atan2(normalizedSensor1Value, normalizedSensor2Value);
    auto rotationAngleDelta = getRotationAngleDelta(currentRotationAngle);

    // Save the current rotation angle as the previous one for next iteration
    previousRotationAngle = currentRotationAngle;

    return rotationAngleDelta;
}

float RotaryEncoder::getRotationAngleDelta(float currentRotationAngle) const {
    auto rotationAngleDelta = currentRotationAngle - previousRotationAngle;

    if (rotationAngleDelta > M_PI) {
        rotationAngleDelta -= 2 * M_PI;
    } else if (rotationAngleDelta < -M_PI) {
        rotationAngleDelta += 2 * M_PI;
    }

    return rotationAngleDelta;
}

