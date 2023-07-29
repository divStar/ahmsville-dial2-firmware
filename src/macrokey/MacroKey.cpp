#include "ArduinoJson.h"
#include "MacroKey.h"

MacroKey::MacroKey(int keyId, int pin) : keyId(keyId), pin(pin) {
    riseTime = 0;
    fallTime = 0;
}

int MacroKey::getPin() const {
    return pin;
}

void MacroKey::onChangeState() {
    StaticJsonDocument<BUFFER_SIZE> jsonDoc;
    jsonDoc["type"] = "macrokey";
    jsonDoc["keyId"] = keyId;
    jsonDoc["pin"] = pin;

    if (riseTime <= fallTime) {
        riseTime = millis();
        jsonDoc["event"] = "pressed";
        jsonDoc["riseTime"] = riseTime;
    } else if (riseTime > fallTime) {
        fallTime = millis();
        jsonDoc["type"] = "released";
        jsonDoc["fallTime"] = fallTime;
    }

    serializeJson(jsonDoc, SerialUSB);
    SerialUSB.println();
}
