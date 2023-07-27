//
// Created by Igor Voronin on 27.07.23.
//

#ifndef DIALER_IINPUTCONSUMER_H
#define DIALER_IINPUTCONSUMER_H

#include "ArduinoJson.h"

class IInputConsumer {
public:
    virtual void applyData(JsonVariantConst jsonData) = 0;

    virtual bool isValidData(JsonVariantConst jsonData) = 0;
};

#endif //DIALER_IINPUTCONSUMER_H
