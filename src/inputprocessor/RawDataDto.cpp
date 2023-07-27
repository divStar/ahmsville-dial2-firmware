//
// Created by Igor Voronin on 25.07.23.
//

#include "RawDataDto.h"

RawDataDto::RawDataDto(char *rawData, unsigned long millisSinceExistence)
        : rawData(rawData), millisSinceExistence(millisSinceExistence) {}

RawDataDto::~RawDataDto() {
    delete this->rawData;
    this->rawData = nullptr;
}

char *RawDataDto::getRawData() {
    return this->rawData;
}

bool RawDataDto::isValid() const {
    return this->itemValid && (millis() - this->millisSinceExistence < LIFE_SPAN);
}

void RawDataDto::setValid(bool isValid) {
    this->itemValid = isValid;
}