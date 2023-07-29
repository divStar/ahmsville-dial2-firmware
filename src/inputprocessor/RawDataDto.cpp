//
// Created by Igor Voronin on 25.07.23.
//

#include "RawDataDto.h"

RawDataDto::RawDataDto(char *rawData, unsigned long millisSinceExistence)
        : rawData(rawData), millisSinceExistence(millisSinceExistence) {}

RawDataDto::~RawDataDto() {
    delete rawData;
    rawData = nullptr;
}

char *RawDataDto::getRawData() {
    return rawData;
}

bool RawDataDto::isValid() const {
    return itemValid && (millis() - millisSinceExistence < LIFE_SPAN);
}

void RawDataDto::setValid(bool isValid) {
    itemValid = isValid;
}