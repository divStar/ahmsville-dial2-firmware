#include "HardwareMacroKeys.h"

HardwareMacroKeys::HardwareMacroKeys(const char *taskType) : taskType(taskType) {}

MacroKey HardwareMacroKeys::keys[5] = {
        MacroKey(0, 0),
        MacroKey(1, 1),
        MacroKey(2, 5),
        MacroKey(3, 10),
        MacroKey(4, 12)
};

void HardwareMacroKeys::initializeMacroKeys() {
    attachInterrupt(digitalPinToInterrupt(keys[0].getPin()), []() { keys[0].onChangeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[1].getPin()), []() { keys[1].onChangeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[2].getPin()), []() { keys[2].onChangeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[3].getPin()), []() { keys[3].onChangeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[4].getPin()), []() { keys[4].onChangeState(); }, CHANGE);

    for (auto key: keys) {
        key.setType(taskType);
    }
}
