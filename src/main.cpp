#include "main.h"

void setup() {
    delay(5000);
    SerialUSB.begin(115200);
    SerialUSB.setTimeout(SERIAL_USB_TIMEOUT);

    setupLogger();

    setupMPU6050();

    createTasks();
    setupTasks();
    addTasksToScheduler();

    Log.noticeln("[ALL] Device initialized");
}

void loop() {
    scheduler.execute();
}

void setupMPU6050() {
    Log.traceln("[MPU6050] Establishing connection...");
    pinMode(30, OUTPUT);
    digitalWrite(30, LOW);
    delay(250);

    Wire.begin();
    Wire.setClock(400000);
    mpu.initialize();
    mpu.dmpInitialize();
    pinMode(INTERRUPT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    Log.traceln("[MPU6050] connection established");
}

/**
 * This method creates all scheduled tasks, that run within this program.
 */
void createTasks() {
    inputProcessorTask = new InputProcessorTask(&messagesToProcess, &SerialUSB);
    messagesCleanerTask = new MessagesCleanerTask(nullptr, &messagesToProcess);
    ledTask = new LedTask(&messagesToProcess);
    writeMacroKeyTask = new MacroKeyTask();
    upperKnobTask = new KnobTask("UpperKnob", A1, A0, 38, 27);
    lowerKnobTask = new KnobTask("LowerKnob", A2, A3, 42, 13);
    hapticTask = new HapticTask(&messagesToProcess);
    capacitativeTouchTask = new CapacitativeTouchTask(9, 8);
    spaceNavigatorTask = new SpaceNavigatorTask(&mpu);
}

/**
 * This method sets up all scheduled tasks.
 */
void setupTasks() {
    inputProcessorTask->onSetup();
    inputProcessorTask->setCallback([]() { inputProcessorTask->onCallback(); });

    messagesCleanerTask->onSetup();
    messagesCleanerTask->setCallback([]() { messagesCleanerTask->onCallback(); });

    ledTask->onSetup();
    ledTask->setCallback([]() { ledTask->onCallback(); });

    writeMacroKeyTask->onSetup();
    writeMacroKeyTask->setCallback([]() { writeMacroKeyTask->onCallback(); });

    lowerKnobTask->onSetup();
    lowerKnobTask->setCallback([]() { lowerKnobTask->onCallback(); });

    upperKnobTask->onSetup();
    upperKnobTask->setCallback([]() { upperKnobTask->onCallback(); });

    hapticTask->onSetup();
    hapticTask->setCallback([]() { hapticTask->onCallback(); });

    capacitativeTouchTask->onSetup();
    capacitativeTouchTask->setCallback([]() { capacitativeTouchTask->onCallback(); });

    spaceNavigatorTask->onSetup();
    spaceNavigatorTask->setCallback([]() { spaceNavigatorTask->onCallback(); });
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
    scheduler.addTask(*spaceNavigatorTask);

    scheduler.enableAll();
}

void dmpDataReady() {
    SerialUSB.println("MPU6050 Data is ready!");
}
