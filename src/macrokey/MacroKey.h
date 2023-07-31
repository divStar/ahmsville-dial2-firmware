#ifndef MACROKEY_H
#define MACROKEY_H

#include <Arduino.h>

class MacroKey {
public:
    explicit MacroKey(int keyId, int pin);

    [[nodiscard]] int getPin() const;

    void onChangeState();

    void setType(const char *type);

private:
    static const int BUFFER_SIZE = 256;
    static const unsigned long DEBOUNCE_DELAY = 100;

    int keyId;
    int pin;
    volatile unsigned long riseTime;
    volatile unsigned long fallTime;
    volatile unsigned long lastInterrupttime;

    const char *type;
};

#endif
