#include <Arduino.h>
#include <TaskScheduler.h>
#include <Vector.h>
#include "logger/Logger.h"
#include "led/ReadLedTask.h"
#include "led/ShowLedTask.h"
#include "led/LedDataDto.h"
#include "macrokey/WriteMacroKeyTask.h"
#include "knob/KnobTask.h"

#define NUM_LEDS            13
#define SERIAL_USB_TIMEOUT  200

Scheduler scheduler;

LedDataDto *ledData[NUM_LEDS] = {};
Vector<LedDataDto *> dataToProcess;

ReadLedTask readLedTask = ReadLedTask(&dataToProcess);
ShowLedTask showLedTask = ShowLedTask(&dataToProcess);
WriteMacroKeyTask writeMacroKeyTask = WriteMacroKeyTask();
KnobTask upperKnobTask = KnobTask("UpperKnob", A1, A0, 28, 27);
KnobTask lowerKnobTask = KnobTask("LowerKnob", A2, A3, 42, 13);

Task readLedTaskShared(0, TASK_FOREVER, []() { readLedTask.onCallback(); }, &scheduler, true);
Task showLedTaskShared(0, TASK_FOREVER, []() { showLedTask.onCallback(); }, &scheduler, true);
Task writeMacroKeyTaskShared(0, TASK_FOREVER, []() { writeMacroKeyTask.onCallback(); }, &scheduler, true);
Task upperKnobTaskShared(0, TASK_FOREVER, []() { upperKnobTask.onCallback(); }, &scheduler, true);
Task lowerKnobTaskShared(0, TASK_FOREVER, []() { lowerKnobTask.onCallback(); }, &scheduler, true);

void setup() {
    delay(5000);

    SerialUSB.begin(115200);
    SerialUSB.setTimeout(SERIAL_USB_TIMEOUT);

    setupLogger();

    dataToProcess.setStorage(ledData, NUM_LEDS, 0);
    showLedTask.onSetup();
    writeMacroKeyTask.onSetup();
    upperKnobTask.onSetup();
    lowerKnobTask.onSetup();

    Log.noticeln("Device initialized: %d", -1);
}

void loop() {
    scheduler.execute();
}