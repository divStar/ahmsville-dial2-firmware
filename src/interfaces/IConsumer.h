//
// Created by Igor Voronin on 27.07.23.
//

#ifndef DIALER_ICONSUMER_H
#define DIALER_ICONSUMER_H

#include "ArduinoJson.h"

class IConsumer {
public:
    virtual void applyData(JsonVariantConst jsonData) = 0;

    virtual bool isValidData(JsonVariantConst jsonData) = 0;
};

#endif //DIALER_ICONSUMER_H
