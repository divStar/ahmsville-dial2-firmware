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
#include "captouch/CapacitativeTouchTask.h"

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
CapacitativeTouchTask *capacitativeTouchTask;

void createTasks();

void setupTasks();

void addTasksToScheduler();

void setup() {
    delay(5000);

    SerialUSB.begin(115200);
    SerialUSB.setTimeout(SERIAL_USB_TIMEOUT);

    setupLogger();

    createTasks();
    setupTasks();
    addTasksToScheduler();

    Log.noticeln("Device initialized");
}

/**
 * This method creates all scheduled tasks, that run within this program.
 */
void createTasks() {
    inputProcessorTask = new InputProcessorTask(&messagesToProcess, &SerialUSB);
    messagesCleanerTask = new MessagesCleanerTask(&messagesToProcess);
    ledTask = new LedTask(&messagesToProcess);
    writeMacroKeyTask = new WriteMacroKeyTask();
    upperKnobTask = new KnobTask("UpperKnob", A1, A0, 38, 27);
    lowerKnobTask = new KnobTask("LowerKnob", A2, A3, 42, 13);
    hapticTask = new HapticTask(&messagesToProcess);
    capacitativeTouchTask = new CapacitativeTouchTask();
}

/**
 * This method sets up all scheduled tasks.
 */
void setupTasks() {
    inputProcessorTask->onSetup();
    inputProcessorTask->setCallback([]() { inputProcessorTask->onCallback(); });

    writeMacroKeyTask->onSetup();
    writeMacroKeyTask->setCallback([]() { writeMacroKeyTask->onCallback(); });

    messagesCleanerTask->onSetup();
    messagesCleanerTask->setCallback([]() { messagesCleanerTask->onCallback(); });

    ledTask->onSetup();
    ledTask->setCallback([]() { ledTask->onCallback(); });

    lowerKnobTask->onSetup();
    lowerKnobTask->setCallback([]() { lowerKnobTask->onCallback(); });

    upperKnobTask->onSetup();
    upperKnobTask->setCallback([]() { upperKnobTask->onCallback(); });

    hapticTask->onSetup();
    hapticTask->setCallback([]() { hapticTask->onCallback(); });

    capacitativeTouchTask->onSetup();
    capacitativeTouchTask->setCallback([]() { capacitativeTouchTask->onCallback(); });
}

/**
 * This method adds all tasks to the scheduler and enables them.
 */
void addTasksToScheduler() {
    scheduler.addTask(*inputProcessorTask);
    scheduler.addTask(*messagesCleanerTask);
    scheduler.addTask(*ledTask);
    scheduler.addTask(*writeMacroKeyTask);
    scheduler.addTask(*lowerKnobTask);
    scheduler.addTask(*upperKnobTask);
    scheduler.addTask(*hapticTask);
    scheduler.addTask(*capacitativeTouchTask);

    scheduler.enableAll();
}

void loop() {
    scheduler.execute();
}