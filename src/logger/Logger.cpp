//
// Created by Igor Voronin on 06.07.23.
//

#include "Logger.h"

RTCZero rtc;

void printTimestamp(Print *_logOutput) {
    // Time in components
    const unsigned int milliSeconds = millis();
    const unsigned int seconds = rtc.getSeconds();
    const unsigned int minutes = rtc.getMinutes();
    const unsigned int hours = rtc.getHours();

    // Time as string
    char timestamp[20];
    sprintf(timestamp, "%02u:%02u:%02u.%03u ", hours, minutes, seconds, milliSeconds);
    _logOutput->print(timestamp);
}

void printLogLevel(Print *_logOutput, int logLevel) {
    /// Show log description based on log level
    switch (logLevel) {
        default:
        case 0:
            _logOutput->print("SILENT ");
            break;
        case 1:
            _logOutput->print("FATAL ");
            break;
        case 2:
            _logOutput->print("ERROR ");
            break;
        case 3:
            _logOutput->print("WARNING ");
            break;
        case 4:
            _logOutput->print("INFO ");
            break;
        case 5:
            _logOutput->print("TRACE ");
            break;
        case 6:
            _logOutput->print("VERBOSE ");
            break;
    }
}

void printPrefix(Print *_logOutput, int logLevel) {
    printTimestamp(_logOutput);
    printLogLevel(_logOutput, logLevel);
}

void setupLogger() {
    rtc.begin();
    Log.begin(LOG_LEVEL_VERBOSE, &SerialUSB);
    Log.setPrefix(printPrefix);
}
