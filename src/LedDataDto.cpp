//
// Created by Igor Voronin on 23.06.23.
//
#include "LedDataDto.h"

LedDataDto::LedDataDto(LedIndex ledIndex, byte r, byte g, byte b, byte brightness) : ledIndex(ledIndex), r(r), g(g), b(b),
                                                                                brightness(brightness) {}

LedIndex LedDataDto::getIndex() const {
    return ledIndex;
}

byte LedDataDto::getR() const {
    return r;
}

byte LedDataDto::getG() const {
    return g;
}

byte LedDataDto::getB() const {
    return b;
}

byte LedDataDto::getBrightness() const {
    return brightness;
}

