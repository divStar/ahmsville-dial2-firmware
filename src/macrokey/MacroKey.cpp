#include "ArduinoJson.h"
#include "MacroKey.h"

MacroKey::MacroKey(int keyId, int pin)
        : ISerialPortUser(configuredSerialPort()),
          keyId(keyId), pin(pin), riseTime(0), fallTime(0), lastInterrupttime(0), type("macrokey") {}

int MacroKey::getPin() const {
    return pin;
}

void MacroKey::onChangeState() {
    unsigned long interruptTime = millis();
    if (interruptTime - lastInterrupttime > DEBOUNCE_DELAY) {
        StaticJsonDocument<BUFFER_SIZE> jsonDoc;
        jsonDoc["type"] = type;
        jsonDoc["keyId"] = keyId;
        jsonDoc["pin"] = pin;

        if (riseTime <= fallTime) {
            riseTime = millis();
            jsonDoc["event"] = "pressed";
            jsonDoc["riseTime"] = riseTime;
            jsonDoc["_fT"] = fallTime;
        } else if (riseTime > fallTime) {
            fallTime = millis();
            jsonDoc["event"] = "released";
            jsonDoc["fallTime"] = fallTime;
            jsonDoc["_rT"] = riseTime;
        }

        serializeJson(jsonDoc, serial);
        serial.println();
    }
}

void MacroKey::setType(const char *newType) {
    this->type = newType;
}
