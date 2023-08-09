#ifndef DIALER_ISERIALPORTUSER_H
#define DIALER_ISERIALPORTUSER_H

#include <Stream.h>
#include "ISerialPort.h"

/**
 * @class   IMessageConsumer
 * @brief   Provides function signatures, that an output producer subclass must
 * implement.
 *
 * This abstract class provides function signatures, that determine a subclass
 * as an output producer.
 *
 * @author  Igor Voronin
 * @date    03.08.2023
 */
class ISerialPortUser {
public:
  /**
   * @brief Constructor.
   *
   * @param serial (Stream) reference to the Serial port to use
   */
  explicit ISerialPortUser(Stream &serial) : serial(serial){};

protected:
  /**
   * @brief Reference to the Serial port to listen on or write to.
   */
  Stream &serial;
};

#endif // DIALER_ISERIALPORTUSER_H
