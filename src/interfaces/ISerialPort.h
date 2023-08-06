/**
 * @file    SerialPort.h
 * @brief   Defines a constant to use as the SERIAL_PORT.
 *
 * @author  Igor Voronin
 * @date    04.08.2023
 */

#ifndef DIALER_ISERIALPORT_H
#define DIALER_ISERIALPORT_H

inline Serial_ &configuredSerialPort() {
    return SerialUSB;
}

#endif //DIALER_ISERIALPORT_H
