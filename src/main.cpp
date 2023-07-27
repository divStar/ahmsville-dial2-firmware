#include <Arduino.h>
#include <TaskScheduler.h>
#include <LinkedList.h>
#include "logger/Logger.h"
#include "inputprocessor/InputProcessorTask.h"
#include "dataprocessor/MessagesCleanerTask.h"
#include "led/LedTask.h"
#include "macrokey/WriteMacroKeyTask.h"
#include "knob/KnobTask.h"
#include "haptic/HapticTask.h"

#define NUM_LEDS            13
#define SERIAL_USB_TIMEOUT  200

Scheduler scheduler;

LinkedList<RawDataDto *> messagesToProcess;

InputProcessorTask *inputProcessorTask;
MessagesCleanerTask *messagesCleanerTask;
LedTask *ledTask;
WriteMacroKeyTask *writeMacroKeyTask;
KnobTask *upperKnobTask;
KnobTask *lowerKnobTask;
HapticTask *hapticTask;

Task inputProcessorTaskShared(0, TASK_FOREVER, []() { inputProcessorTask->onCallback(); }, &scheduler, true);
Task messagesCleanerTaskShared(0, TASK_FOREVER, []() { messagesCleanerTask->onCallback(); }, &scheduler, true);
Task writeMacroKeyTaskShared(0, TASK_FOREVER, []() { writeMacroKeyTask->onCallback(); }, &scheduler, true);
Task ledTaskShared(0, TASK_FOREVER, []() { ledTask->onCallback(); }, &scheduler, true);
Task upperKnobTaskShared(0, TASK_FOREVER, []() { upperKnobTask->onCallback(); }, &scheduler, true);
Task lowerKnobTaskShared(0, TASK_FOREVER, []() { lowerKnobTask->onCallback(); }, &scheduler, true);
Task hapticTaskShared(0, TASK_FOREVER, []() { hapticTask->onCallback(); }, &scheduler, true);

void setup() {
    delay(5000);

    SerialUSB.begin(115200);
    SerialUSB.setTimeout(SERIAL_USB_TIMEOUT);

    setupLogger();

    inputProcessorTask = new InputProcessorTask(&messagesToProcess, &SerialUSB);
    messagesCleanerTask = new MessagesCleanerTask(&messagesToProcess);
    ledTask = new LedTask(&messagesToProcess);
    writeMacroKeyTask = new WriteMacroKeyTask();
    upperKnobTask = new KnobTask("UpperKnob", A1, A0, 38, 27);
    lowerKnobTask = new KnobTask("LowerKnob", A2, A3, 42, 13);
    hapticTask = new HapticTask(&messagesToProcess);

    inputProcessorTask->onSetup();
    messagesCleanerTask->onSetup();
    ledTask->onSetup();
    writeMacroKeyTask->onSetup();
    lowerKnobTask->onSetup();
    upperKnobTask->onSetup();
    hapticTask->onSetup();

    Log.noticeln("Device initialized");
}

void loop() {
    scheduler.execute();
}