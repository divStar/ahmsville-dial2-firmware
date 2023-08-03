#include "ErrorSerializer.h"

void ErrorSerializer::serializeToJsonAndSend(const char *type, const char *error, const char *message) {
    StaticJsonDocument<BUFFER_SIZE> jsonErrorDoc;
    jsonErrorDoc["type"] = type;
    jsonErrorDoc["error"] = error;
    jsonErrorDoc["message"] = message;

    serializeJson(jsonErrorDoc, SerialUSB);
}
