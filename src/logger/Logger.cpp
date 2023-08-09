#include "Logger.h"

/**
 * @brief Real-time clock (RTC) of the Arduino Zero.
 *
 * This variables needs to stay here since in the header file it'd be imported
 * multiple times.
 */
RTCZero rtc;

void printTimestamp(Print &serial) {
  // Time in components
  const unsigned int milliSeconds = millis();
  const unsigned int seconds = rtc.getSeconds();
  const unsigned int minutes = rtc.getMinutes();
  const unsigned int hours = rtc.getHours();

  // Time as string
  char timestamp[20];
  sprintf(timestamp, DEFAULT_LOG_FORMAT, hours, minutes, seconds, milliSeconds);
  serial.print(timestamp);
}

void printLogLevel(Print &serial, int logLevel) {
  // Show log description based on log level
  switch (logLevel) {
  default:
  case 0:
    serial.print("SILENT ");
    break;
  case 1:
    serial.print("FATAL ");
    break;
  case 2:
    serial.print("ERROR ");
    break;
  case 3:
    serial.print("WARNING ");
    break;
  case 4:
    serial.print("INFO ");
    break;
  case 5:
    serial.print("TRACE ");
    break;
  case 6:
    serial.print("VERBOSE ");
    break;
  }
}

void printPrefix(Print *serial, int logLevel) {
  printTimestamp(*serial);
  printLogLevel(*serial, logLevel);
}

void setupLogger() {
  rtc.begin();
  Log.begin(LOG_LEVEL_VERBOSE, (Print *)&configuredSerialPort());
  Log.setPrefix(printPrefix);
}
