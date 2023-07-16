//
// Created by Igor Voronin on 06.07.23.
//

#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include "logger/Logger.h"

class RotaryEncoder {
public:
    RotaryEncoder(int pin0, int pin1, int pinInterrupt0, int pinInterrupt1);

    void readValues();

    int getPin0Value();

    int getPin1Value();

    int getPin0InterruptValue();

    int getPin1InterruptValue();

    int getCurrentRotationDirection();

private:
    static const int FILTER_SIZE = 40;

    int pin0;
    int pin1;
    int pinInterrupt0;
    int pinInterrupt1;

    int pin0Value = 0;
    int pin1Value = 0;
    int filteredPin0Values[FILTER_SIZE];
    int filteredPin1Values[FILTER_SIZE];
    int filterIndex = 0;
    int pinInterrupt0Value = 0;
    int pinInterrupt1Value = 0;

    int currentRotationDirection = 0;

    int applyMovingAverageFilter(int rawValue, int *filterBuffer);

    int getRotationDirection(int rawValue0, int rawValue1);
};


#endif //ROTARYENCODER_H
