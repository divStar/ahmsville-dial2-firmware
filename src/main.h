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

#include <LinkedList.h>
#include <TaskScheduler.h>
#include "captouch/CapacitiveTouchTask.h"
#include "dataprocessor/MessagesCleanerTask.h"
#include "haptic/HapticTask.h"
#include "hardware-adapters/HardwareCapacitiveSensorAdapter.h"
#include "hardware-adapters/HardwareHapticSensorAdapter.h"
#include "hardware-adapters/HardwareMacroKeys.h"
#include "hardware-adapters/HardwareRotaryEncoderAdapter.h"
#include "hardware-adapters/HardwareSpaceNavigatorSensorAdapter.h"
#include "inputprocessor/InputProcessorTask.h"
#include "interfaces/ISerialPort.h"
#include "knob/KnobTask.h"
#include "led/LedTask.h"
#include "logger/Logger.h"
#include "macrokey/MacroKeyTask.h"
#include "spacenavigator/SpaceNavigatorTask.h"

#define SERIAL_USB_TIMEOUT 200

/**
 * @brief pin 0 of the upper sensorAdapter.
 */
static const byte KNOB_UPPER_PIN_0 = A1;
/**
 * @brief pin 1 of the upper sensorAdapter.
 */
static const byte KNOB_UPPER_PIN_1 = A0;
/**
 * @brief pin interrupt 0 of the upper sensorAdapter.
 */
static const byte KNOB_UPPER_PIN_INTERRUPT_0 = 38;
/**
 * @brief pin interrupt 1 of the upper sensorAdapter.
 */
static const byte KNOB_UPPER_PIN_INTERRUPT_1 = 27;
/**
 * @brief pin 0 of the lower sensorAdapter.
 */
static const byte KNOB_LOWER_PIN_0 = A2;
/**
 * @brief pin 1 of the lower sensorAdapter.
 */
static const byte KNOB_LOWER_PIN_1 = A3;
/**
 * @brief pin interrupt 0 of the lower sensorAdapter.
 */
static const byte KNOB_LOWER_PIN_INTERRUPT_0 = 42;
/**
 * @brief pin interrupt 1 of the lower sensorAdapter.
 */
static const byte KNOB_LOWER_PIN_INTERRUPT_1 = 13;
/**
 * @brief pin number for the haptic vibration motor.
 */
static const byte HAPTIC_PIN = 4;
/**
 * @brief sending pin for the capacitive touch sensor.
 */
static const uint8_t CAP_TOUCH_SENDING_PIN = 9;
/**
 * @brief receiving pin for the capacitive touch sensor.
 */
static const uint8_t CAP_TOUCH_RECEIVING_PIN = 8;
/**
 * @brief Number of the pin, that is being written to to start the space
 * navigator capabilities.
 */
static const byte SPACE_NAVIGATOR_STARTER_PIN = 30;
/**
 * @brief Number of the interrupt pin.
 */
static const byte SPACE_NAVIGATOR_INTERRUPT_PIN = 2;

/**
 * @brief TaskScheduler to use in order to distribute the available CPU cycles
 * properly.
 */
Scheduler scheduler;

/**
 * @brief reference to the list of messages to be processed.
 */
LinkedList<InputMessageDto *> messagesToProcess;

HardwareMacroKeys *macroKeys;
HardwareRotaryEncoderAdapter *upperKnobSensor;
HardwareRotaryEncoderAdapter *lowerKnobSensor;
HardwareHapticSensorAdapter *hapticSensor;
HardwareCapacitiveSensorAdapter *capacitiveSensor;
HardwareSpaceNavigatorSensorAdapter *spaceNavigatorSensor;

InputProcessorTask *inputProcessorTask;
MessagesCleanerTask *messagesCleanerTask;
LedTask *ledTask;
MacroKeyTask *macroKeyTask;
KnobTask *upperKnobTask;
KnobTask *lowerKnobTask;
HapticTask *hapticTask;
CapacitiveTouchTask *capacitiveTouchTask;
SpaceNavigatorTask *spaceNavigatorTask;

/**
 * @brief Creates instances of all sensor adapter objects.
 */
void createSensorAdapters();

/**
 * @brief Creates instances of all ISchedulableDialTask objects.
 */
void createTasks();

/**
 * @brief Sets up instances of all ISchedulableDialTask objects.
 */
void setupTasks();

/**
 * @brief Adds all ISchedulableDialTask objects to the Scheduler and enables
 * them.
 */
void addTasksToScheduler();

#endif // DIALER_MAIN_H
