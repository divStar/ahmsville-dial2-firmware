//
// Created by Igor Voronin on 25.07.23.
//

#ifndef DIALER_RAWDATADTO_H
#define DIALER_RAWDATADTO_H

#include <Arduino.h>
#include "logger/Logger.h"

class RawDataDto {
public:
    RawDataDto(char *rawData, unsigned long millisSinceExistence);

    ~RawDataDto();

    char *getRawData();

    bool isValid() const;

    void setValid(bool isValid);

private:
    static const unsigned long LIFE_SPAN = 200; // Milliseconds

    char *rawData;
    unsigned long millisSinceExistence;
    bool itemValid = true;
};

#endif //DIALER_RAWDATADTO_H
