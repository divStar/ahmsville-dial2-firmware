//
// Created by Igor Voronin on 30.07.23.
//

#ifndef DIALER_ERRORSERIALIZER_H
#define DIALER_ERRORSERIALIZER_H

#include <ArduinoJson.h>

class ErrorSerializer {
public:
    static void serializeError(const char *type, const char *error, const char *message);

private:
    static const auto BUFFER_SIZE = 256;
};


#endif //DIALER_ERRORSERIALIZER_H
