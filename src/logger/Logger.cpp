#include "Logger.h"

/**
 * @brief Real-time clock (RTC) of the Arduino Zero.
 *
 * This variables needs to stay here since in the header file it'd be imported multiple times.
 */
RTCZero rtc;

void printTimestamp(Print *logOutput) {
    // Time in components
    const unsigned int milliSeconds = millis();
    const unsigned int seconds = rtc.getSeconds();
    const unsigned int minutes = rtc.getMinutes();
    const unsigned int hours = rtc.getHours();

    // Time as string
    char timestamp[20];
    sprintf(timestamp, DEFAULT_LOG_FORMAT, hours, minutes, seconds, milliSeconds);
    logOutput->print(timestamp);
}

void printLogLevel(Print *logOutput, int logLevel) {
    // Show log description based on log level
    switch (logLevel) {
        default:
        case 0:
            logOutput->print("SILENT ");
            break;
        case 1:
            logOutput->print("FATAL ");
            break;
        case 2:
            logOutput->print("ERROR ");
            break;
        case 3:
            logOutput->print("WARNING ");
            break;
        case 4:
            logOutput->print("INFO ");
            break;
        case 5:
            logOutput->print("TRACE ");
            break;
        case 6:
            logOutput->print("VERBOSE ");
            break;
    }
}

void printPrefix(Print *logOutput, int logLevel) {
    printTimestamp(logOutput);
    printLogLevel(logOutput, logLevel);
}

void setupLogger() {
    rtc.begin();
    Log.begin(LOG_LEVEL_VERBOSE, &SerialUSB);
    Log.setPrefix(printPrefix);
}
