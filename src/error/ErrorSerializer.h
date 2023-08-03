#ifndef DIALER_ERRORSERIALIZER_H
#define DIALER_ERRORSERIALIZER_H

#include <ArduinoJson.h>

/**
 * @class   ErrorSerializer
 * @brief   Serializer for error messages.
 *
 * This class handles the error serialization to JSON. It also sends the serialized JSON to a Serial port.
 *
 * @author  Igor Voronin
 * @date    30.07.2023
 */
class ErrorSerializer {
public:
    /**
     * @brief Serializes the given type, error and message references to a JSON message and sends it to the Serial port.
     *
     * @param type      (const char*) message type (`type` attribute in the resulting JSON)
     * @param error     (const char*) error (`error` attribute in the resulting JSON)
     * @param message   (const char*) message (`message` attribute in the resulting JSON)
     */
    static void serializeToJsonAndSend(const char *type, const char *error, const char *message);

private:
    /**
     * @brief Buffer size of the JSON output
     */
    static const auto BUFFER_SIZE = 256;
};


#endif //DIALER_ERRORSERIALIZER_H
