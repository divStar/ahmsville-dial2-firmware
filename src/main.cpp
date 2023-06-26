#include <Arduino.h>
#include <TaskScheduler.h>
#include <Vector.h>
#include "ReadLedTask.h"
#include "ShowLedTask.h"
#include "LedDataDto.h"

#define NUM_LEDS            13
#define SERIAL_USB_TIMEOUT  200

LedDataDto* ledData[NUM_LEDS] = {};
Vector<LedDataDto*> dataToProcess;

Scheduler scheduler;

ReadLedTask ledReadTask = ReadLedTask(&dataToProcess);
ShowLedTask ledTask = ShowLedTask(&dataToProcess);

Task schedulerLedReadTask(0, TASK_FOREVER, []() { ledReadTask.onCallback(); }, &scheduler, true);
Task schedulerLedTask(0, TASK_FOREVER, []() { ledTask.onCallback(); }, &scheduler, true);

void setup() {
    delay(5000);
    SerialUSB.begin(115200);
    SerialUSB.setTimeout(SERIAL_USB_TIMEOUT);
    dataToProcess.setStorage(ledData, NUM_LEDS, 0);
    ledTask.onSetup();
    SerialUSB.println("Device initialized");
}

void loop() {
    scheduler.execute();
}