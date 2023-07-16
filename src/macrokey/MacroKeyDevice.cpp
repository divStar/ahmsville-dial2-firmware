//
// Created by Igor Voronin on 03.07.23.
//

#include "MacroKeyDevice.h"

MacroKey MacroKeyDevice::keys[5] = {MacroKey(0, 0),
                    MacroKey(1, 1),
                    MacroKey(2, 5),
                    MacroKey(3, 10),
                    MacroKey(4, 12)
};

void MacroKeyDevice::init() {
    attachInterrupt(digitalPinToInterrupt(keys[0].getPin()), []() { keys[0].changeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[1].getPin()), []() { keys[1].changeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[2].getPin()), []() { keys[2].changeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[3].getPin()), []() { keys[3].changeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[4].getPin()), []() { keys[4].changeState(); }, CHANGE);
}