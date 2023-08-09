#ifndef DIALER_JSONSERIALIZER_H
#define DIALER_JSONSERIALIZER_H

#include <ArduinoJson.h>
#include "interfaces/ISerialPortUser.h"

/**
 * @class   JsonSerializer
 * @brief   Serializer for json messages.
 *
 * This class handles the json serialization to JSON. It also sends the
 * serialized JSON to a Serial port.
 *
 * @author  Igor Voronin
 * @date    30.07.2023
 */
class JsonSerializer : public ISerialPortUser {
public:
  /**
   * @brief Serializes the given type, info and message references to a JSON
   * message and sends it to the Serial port.
   *
   * @param serial    (Stream) reference to the Serial port to output to
   * @param type      (const char*) message type (`type` attribute in the
   * resulting JSON)
   * @param info      (const char*) info(number) (`info` attribute in the
   * resulting JSON)
   * @param message   (const char*) message (`message` attribute in the
   * resulting JSON)
   */
  static void sendJsonInfo(Stream &serial, const char *type, const char *info, const char *message);

  /**
   * @brief Serializes the given type, error and message references to a JSON
   * message and sends it to the Serial port.
   *
   * @param serial    (Stream) reference to the Serial port to output to
   * @param type      (const char*) message type (`type` attribute in the
   * resulting JSON)
   * @param error     (const char*) error(number) (`error` attribute in the
   * resulting JSON)
   * @param message   (const char*) message (`message` attribute in the
   * resulting JSON)
   */
  static void sendJsonError(Stream &serial, const char *type, const char *error, const char *message);

private:
  /**
   * @brief Buffer size of the JSON output
   */
  static const auto BUFFER_SIZE = 256;
};

#endif // DIALER_JSONSERIALIZER_H
