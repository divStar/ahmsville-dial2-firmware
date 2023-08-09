#ifndef DIALER_IMESSAGECONSUMER_H
#define DIALER_IMESSAGECONSUMER_H

#include <ArduinoJson.h>
#include <LinkedList.h>
#include "inputprocessor/InputMessageDto.h"

/**
 * @class   IMessageConsumer
 * @brief   Provides function signatures, that an input consumer subclass must
 * implement.
 *
 * This abstract class provides function signatures, that determine a subclass
 * as an input consumer.
 *
 * <p>The functions force the subclass to implement a method to check whether
 * the data is valid (isValid(JsonVariantConst)) and if so, use the data
 * (useData(JsonVariantConst)).</p>
 *
 * @author  Igor Voronin
 * @date    27.07.2023
 */
class IMessageConsumer {
public:
  explicit IMessageConsumer(LinkedList<InputMessageDto *> &messagesToProcess) : messagesToProcess(messagesToProcess){};

  /**
   * @brief uses the given data, usually to send it to a particular
   * sensorAdapter
   *
   * @param jsonData  (JsonVariantConst) data to validate and use
   */
  virtual void useData(JsonVariantConst jsonData) = 0;

  /**
   * @brief validates the given data (e.g. check particular JSON attributes for
   * particular values)
   *
   * @param jsonData  (JsonVariantConst) data to validate
   * @return          (bool) <code>true</code> if the given data is valid,
   * <code>false</code> otherwise
   */
  virtual bool isValidData(JsonVariantConst jsonData) = 0;

protected:
  /**
   * @brief reference to the list of messages to be processed.
   */
  LinkedList<InputMessageDto *> &messagesToProcess;
};

#endif // DIALER_IMESSAGECONSUMER_H
