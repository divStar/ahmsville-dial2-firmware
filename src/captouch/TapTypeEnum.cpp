//
// Created by Igor Voronin on 29.07.23.
//

#include "TapTypeEnum.h"

TapTypeEnum::TapTypeEnum(int threshold) : threshold(threshold) {}

void TapTypeEnum::setThreshold(int newThreshold) {
    threshold = newThreshold;
}

int TapTypeEnum::getThreshold() const {
    return threshold;
}

bool TapTypeEnum::isValid() const {
    return threshold != INVALID;
}
