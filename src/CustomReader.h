//
// Created by Igor Voronin on 24.06.23.
//

#ifndef DIALER_CUSTOMREADER_H
#define DIALER_CUSTOMREADER_H
#include <ArduinoJson.h>

class CustomReader {
    // Reads one byte, or returns -1
    int read();
    // Reads several bytes, returns the number of bytes read.
    size_t readBytes(char* buffer, size_t length);
};


#endif //DIALER_CUSTOMREADER_H
