//
// Created by Igor Voronin on 23.06.23.
//

#ifndef DIALER_LEDDATADTO_H
#define DIALER_LEDDATADTO_H

#include <Arduino.h>
#include "LedIndex.h"

class LedDataDto {
public:
    LedDataDto(LedIndex ledIndex, byte r, byte g, byte b, byte brightness);

    LedIndex getIndex() const;

    byte getR() const;

    byte getG() const;

    byte getB() const;

    byte getBrightness() const;

private:
    LedIndex ledIndex;
    byte r;
    byte g;
    byte b;
    byte brightness;
};


#endif //DIALER_LEDDATADTO_H
