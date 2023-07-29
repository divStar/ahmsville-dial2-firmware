//
// Created by Igor Voronin on 26.06.23.
//
#include "WriteMacroKeyTask.h"

MacroKey WriteMacroKeyTask::keys[5] = {MacroKey(0, 0),
                                       MacroKey(1, 1),
                                       MacroKey(2, 5),
                                       MacroKey(3, 10),
                                       MacroKey(4, 12)
};

WriteMacroKeyTask::WriteMacroKeyTask() {
    setInterval(0);
    setIterations(TASK_FOREVER);
}

void WriteMacroKeyTask::onSetup() {
    WriteMacroKeyTask::initializeKeys();
}

void WriteMacroKeyTask::onCallback() {
    // nothing to do during the loop since data is sent during interrupt
}

void WriteMacroKeyTask::initializeKeys() {
    attachInterrupt(digitalPinToInterrupt(keys[0].getPin()), []() { keys[0].onChangeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[1].getPin()), []() { keys[1].onChangeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[2].getPin()), []() { keys[2].onChangeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[3].getPin()), []() { keys[3].onChangeState(); }, CHANGE);
    attachInterrupt(digitalPinToInterrupt(keys[4].getPin()), []() { keys[4].onChangeState(); }, CHANGE);
}