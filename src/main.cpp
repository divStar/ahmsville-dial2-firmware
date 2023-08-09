#include "main.h"

void setup() {
  delay(5000);
  configuredSerialPort().begin(115200);
  configuredSerialPort().setTimeout(SERIAL_USB_TIMEOUT);

  setupLogger();

  createSensorAdapters();
  createTasks();
  setupTasks();
  addTasksToScheduler();

  Log.noticeln("[ALL] Device initialized");
}

void loop() { scheduler.execute(); }

void createSensorAdapters() {
  macroKeys = new HardwareMacroKeys("macrokey");
  upperKnobSensor =
      new HardwareRotaryEncoderAdapter(KNOB_UPPER_PIN_0, KNOB_UPPER_PIN_1, KNOB_UPPER_PIN_INTERRUPT_0, KNOB_UPPER_PIN_INTERRUPT_1);
  lowerKnobSensor =
      new HardwareRotaryEncoderAdapter(KNOB_LOWER_PIN_0, KNOB_LOWER_PIN_1, KNOB_LOWER_PIN_INTERRUPT_0, KNOB_LOWER_PIN_INTERRUPT_1);
  hapticSensor = new HardwareHapticSensorAdapter(HAPTIC_PIN);
  capacitiveSensor = new HardwareCapacitiveSensorAdapter(CAP_TOUCH_SENDING_PIN, CAP_TOUCH_RECEIVING_PIN);
  spaceNavigatorSensor = new HardwareSpaceNavigatorSensorAdapter(SPACE_NAVIGATOR_STARTER_PIN, SPACE_NAVIGATOR_INTERRUPT_PIN);
}

/**
 * This method creates all scheduled tasks, that run within this program.
 */
void createTasks() {
  inputProcessorTask = new InputProcessorTask(messagesToProcess);
  messagesCleanerTask = new MessagesCleanerTask(messagesToProcess);
  ledTask = new LedTask(messagesToProcess);
  macroKeyTask = new MacroKeyTask(*macroKeys);
  upperKnobTask = new KnobTask("UpperKnob", *upperKnobSensor);
  lowerKnobTask = new KnobTask("LowerKnob", *lowerKnobSensor);
  hapticTask = new HapticTask(*hapticSensor, messagesToProcess);
  capacitiveTouchTask = new CapacitiveTouchTask(*capacitiveSensor);
  spaceNavigatorTask = new SpaceNavigatorTask(*spaceNavigatorSensor);
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

  macroKeyTask->onSetup();
  macroKeyTask->setCallback([]() { macroKeyTask->onCallback(); });

  lowerKnobTask->onSetup();
  lowerKnobTask->setCallback([]() { lowerKnobTask->onCallback(); });

  upperKnobTask->onSetup();
  upperKnobTask->setCallback([]() { upperKnobTask->onCallback(); });

  hapticTask->onSetup();
  hapticTask->setCallback([]() { hapticTask->onCallback(); });

  capacitiveTouchTask->onSetup();
  capacitiveTouchTask->setCallback([]() { capacitiveTouchTask->onCallback(); });

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
  scheduler.addTask(*macroKeyTask);
  scheduler.addTask(*lowerKnobTask);
  scheduler.addTask(*upperKnobTask);
  scheduler.addTask(*hapticTask);
  scheduler.addTask(*capacitiveTouchTask);
  scheduler.addTask(*spaceNavigatorTask);

  //    scheduler.enableAll();

  inputProcessorTask->enable();
  messagesCleanerTask->enable();
  ledTask->enable();
  macroKeyTask->enable();
  lowerKnobTask->enable();
  upperKnobTask->enable();
  hapticTask->enable();
  capacitiveTouchTask->enable();
  spaceNavigatorTask->enable();
}
