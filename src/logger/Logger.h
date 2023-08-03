/**
 * @file    Logger.h
 * @brief   Sets up the ArduinoLog Logger.
 *
 * This class sets up the ArduinoLog (Log) Logger.
 *
 * @author  Igor Voronin
 * @date    06.07.2023
 */

#ifndef DIALER_LOGGER_H
#define DIALER_LOGGER_H

#include <Arduino.h>
#include "ArduinoLog.h"
#include "RTCZero.h"
#include "interfaces/ISerialPort.h"

/**
 * @brief Default Log format.
 */
static const char *const DEFAULT_LOG_FORMAT = "%02u:%02u:%02u.%03u ";

/**
 * @brief Prints the timestamp, prepending the actual message.
 *
 * @param serial (Print) reference to the output
 */
void printTimestamp(Print &serial);

/**
 * @brief Prints the log level, prepending the actual message.
 *
 * @param serial (Print) reference to the output
 * @param logLevel  (int) log level (see ArduinoLog.h for more details)
 */
void printLogLevel(Print &serial, int logLevel);

/**
 * @brief Prints a set prefix, prepending the actual message.
 *
 * @param serial (Print) pointer to the output
 * @param logLevel  (int) log level (see ArduinoLog.h for more details)
 */
void printPrefix(Print *serial, int logLevel);

/**
 * @brief Sets up the ArduinoLog logger (`Log`).
 */
void setupLogger();

#endif //DIALER_LOGGER_H
