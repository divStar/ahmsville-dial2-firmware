#include "MacroKeyTask.h"

MacroKey MacroKeyTask::keys[5] = {MacroKey(0, 0),
                                  MacroKey(1, 1),
                                  MacroKey(2, 5),
                                  MacroKey(3, 10),
                                  MacroKey(4, 12)
};

MacroKeyTask::MacroKeyTask() : ISchedulableDialTask("macrokey") {
    setInterval(0);
    setIterations(TASK_FOREVER);

    // set the correct type, that will be displayed in the JSON each key will be sending
    // since `MacroKey::type` is initialized to `macrokey`, this is technically not necessary
    for (auto key : keys) {
        key.setType(getTaskType());
    }
}

void MacroKeyTask::onSetup() {
    MacroKeyTask::initializeKeys();
}

void MacroKeyTask::initializeKeys() {
    attachInterrupt(digitalPinToInterrupt(keys[0].getPin()), []() { keys[0].onChangeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[1].getPin()), []() { keys[1].onChangeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[2].getPin()), []() { keys[2].onChangeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[3].getPin()), []() { keys[3].onChangeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[4].getPin()), []() { keys[4].onChangeState(); }, CHANGE);
}