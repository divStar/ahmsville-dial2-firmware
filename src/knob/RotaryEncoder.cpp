//
// Created by Igor Voronin on 06.07.23.
//

#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(int pin0, int pin1, int pinInterrupt0, int pinInterrupt1)
        : pin0(pin0), pin1(pin1), pinInterrupt0(pinInterrupt0), pinInterrupt1(pinInterrupt1) {
    pinMode(this->pin0, INPUT);
    pinMode(this->pin1, INPUT);
    pinMode(this->pinInterrupt0, INPUT);
    pinMode(this->pinInterrupt1, INPUT);
}

void RotaryEncoder::readValues() {
    // Read new values
    this->currentRotationDirection = this->getRotationDirection(
            analogRead(this->pin0),
            analogRead(this->pin1)
    );
    this->pinInterrupt0Value = digitalRead(pinInterrupt0);
    this->pinInterrupt1Value = digitalRead(pinInterrupt1);
}

int RotaryEncoder::getPin0Value() {
    return this->pin0Value;
}

int RotaryEncoder::getPin1Value() {
    return this->pin1Value;
}

int RotaryEncoder::getCurrentRotationDirection() {
    return this->currentRotationDirection;
}

int RotaryEncoder::applyMovingAverageFilter(int rawValue, int *filterBuffer) {
    // Store the new value in the filter buffer
    filterBuffer[filterIndex] = rawValue;

    // Update the filter index
    filterIndex = (filterIndex + 1) % FILTER_SIZE;

    // Calculate the average
    int sum = 0;
    for (int i = 0; i < FILTER_SIZE; ++i) {
        sum += filterBuffer[i];
    }
    int average = sum / FILTER_SIZE;

    return average;
}

int RotaryEncoder::getRotationDirection(int rawValue0, int rawValue1) {
    // Apply the moving average filter to each sensor
    int filteredValue0 = applyMovingAverageFilter(rawValue0, filteredPin0Values);
    int filteredValue1 = applyMovingAverageFilter(rawValue1, filteredPin1Values);

    // Calculate the change in values
    int delta0 = filteredValue0 - this->pin0Value;
    int delta1 = filteredValue1 - this->pin1Value;

    // Update the previous values
    this->pin0Value = filteredValue0;
    this->pin1Value = filteredValue1;

    // Determine the rotation direction
    if (filteredValue0 >= 150 && filteredValue0 < 250 && pinInterrupt0Value == 1 && pinInterrupt1Value == 0) {
        return 1;  // Clockwise rotation
    } else if (filteredValue0 >= 250 && filteredValue0 < 350 && pinInterrupt0Value == 0 && pinInterrupt1Value == 1) {
        return -1; // Counterclockwise rotation
    } else {
        return 0;  // No rotation or indeterminate state
    }
}

int RotaryEncoder::getPin0InterruptValue() {
    return this->pinInterrupt0Value;
}

int RotaryEncoder::getPin1InterruptValue() {
    return this->pinInterrupt1Value;
}
