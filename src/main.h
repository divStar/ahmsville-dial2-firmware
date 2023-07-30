//
// Created by Igor Voronin on 30.07.23.
//

#ifndef DIALER_MAIN_H
#define DIALER_MAIN_H

#include <MPU6050_6Axis_MotionApps20.h>
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

#define NUM_LEDS            13
#define SERIAL_USB_TIMEOUT  200

static const int INTERRUPT_PIN = 2;

MPU6050 mpu(MPU6050_IMU::MPU6050_ADDRESS_AD0_HIGH);

Scheduler scheduler;

LinkedList<RawDataDto *> messagesToProcess;

InputProcessorTask *inputProcessorTask;
MessagesCleanerTask *messagesCleanerTask;
LedTask *ledTask;
MacroKeyTask *writeMacroKeyTask;
KnobTask *upperKnobTask;
KnobTask *lowerKnobTask;
HapticTask *hapticTask;
CapacitativeTouchTask *capacitativeTouchTask;
SpaceNavigatorTask *spaceNavigatorTask;

void dmpDataReady();

void setup();

void loop();

void setupMPU6050();

void createTasks();

void setupTasks();

void addTasksToScheduler();

#endif //DIALER_MAIN_H
