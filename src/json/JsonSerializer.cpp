#include "JsonSerializer.h"

void JsonSerializer::sendJsonInfo(Stream &serial, const char *type, const char *info, const char *message) {
    StaticJsonDocument<BUFFER_SIZE> jsonInfoDoc;
    jsonInfoDoc["type"] = type;
    jsonInfoDoc["json"] = info;
    jsonInfoDoc["message"] = message;

    serializeJson(jsonInfoDoc, serial);
}

void JsonSerializer::sendJsonError(Stream &serial, const char *type, const char *error, const char *message) {
    StaticJsonDocument<BUFFER_SIZE> jsonErrorDoc;
    jsonErrorDoc["type"] = type;
    jsonErrorDoc["json"] = error;
    jsonErrorDoc["message"] = message;

    serializeJson(jsonErrorDoc, serial);
}
