/**
 * @file    main.h
 * @brief   Main program of the device.
 *
 * This class is the main program class for the AhmsVille Dial2.
 *
 * @author  Igor Voronin
 * @date    30.07.2023
 */

#ifndef DIALER_MAIN_H
#define DIALER_MAIN_H

#include <Arduino.h>
#include <TaskScheduler.h>
#include <LinkedList.h>
#include "logger/Logger.h"
#include "inputprocessor/InputProcessorTask.h"
#include "dataprocessor/MessagesCleanerTask.h"
#include "led/LedTask.h"
#include "macrokey/MacroKeyTask.h"
#include "knob/KnobTask.h"
#include "haptic/HapticTask.h"
#include "captouch/CapacitativeTouchTask.h"
#include "spacenavigator/SpaceNavigatorTask.h"

#define SERIAL_USB_TIMEOUT  200

/**
 * @brief TaskScheduler to use in order to distribute the available CPU cycles properly.
 */
Scheduler scheduler;

/**
 * @brief Pointer to the list of messages to be processed.
 */
LinkedList<InputMessageDto *> messagesToProcess;

InputProcessorTask *inputProcessorTask;
MessagesCleanerTask *messagesCleanerTask;
LedTask *ledTask;
MacroKeyTask *writeMacroKeyTask;
KnobTask *upperKnobTask;
KnobTask *lowerKnobTask;
HapticTask *hapticTask;
CapacitativeTouchTask *capacitativeTouchTask;
SpaceNavigatorTask *spaceNavigatorTask;

/**
 * @brief Creates instances of all ISchedulableDialTask objects.
 */
void createTasks();

/**
 * @brief Sets up instances of all ISchedulableDialTask objects.
 */
void setupTasks();

/**
 * @brief Adds all ISchedulableDialTask objects to the Scheduler and enables them.
 */
void addTasksToScheduler();

#endif //DIALER_MAIN_H
