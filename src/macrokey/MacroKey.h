#ifndef MACROKEY_H
#define MACROKEY_H
#include <Arduino.h>

class MacroKey {
public:
    explicit MacroKey(int keyId, int pin);

    [[nodiscard]] int getPin() const;

    void onChangeState();

private:
    static const int BUFFER_SIZE = 256;

    int keyId;
    int pin;
    volatile unsigned long riseTime;
    volatile unsigned long fallTime;
};

#endif
