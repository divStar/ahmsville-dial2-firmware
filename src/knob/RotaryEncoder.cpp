//
// Created by Igor Voronin on 06.07.23.
//

#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int pin0, int pin1, int pinInterrupt0, int pinInterrupt1)
        : pin0(pin0), pin1(pin1), pinInterrupt0(pinInterrupt0), pinInterrupt1(pinInterrupt1),
          filteredSensor1Value(0.0), filteredSensor2Value(0.0) {
    pinMode(this->pin0, INPUT);
    pinMode(this->pin1, INPUT);
    pinMode(this->pinInterrupt0, INPUT);
    pinMode(this->pinInterrupt1, INPUT);
}

void RotaryEncoder::readValues() {
    // Read new values
    this->values[0] = static_cast<float>(analogRead(this->pin0));
    this->values[1] = static_cast<float>(analogRead(this->pin1));

    // Smoothen the analog values
    this->values[0] = filteredSensor1Value.update(this->values[0]);
    this->values[1] = filteredSensor2Value.update(this->values[1]);

    this->rotationDelta = getRotationAngle();
}

float RotaryEncoder::getRotationDelta() const {
    return this->rotationDelta;
}

float RotaryEncoder::getRotationAngle() {
    // Get sensor values
    auto normalizedSensor1Value = this->values[0] - SENSOR_MIDPOINT;
    auto normalizedSensor2Value = this->values[1] - SENSOR_MIDPOINT;

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

