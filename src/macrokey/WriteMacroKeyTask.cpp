//
// Created by Igor Voronin on 26.06.23.
//
#include "WriteMacroKeyTask.h"

void WriteMacroKeyTask::onSetup() {
    MacroKeyDevice::init();
}

void WriteMacroKeyTask::onCallback() {
    // nothing to do during the loop since data is sent during interrupt
}
