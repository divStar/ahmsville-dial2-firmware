#include "KnobTask.h"

KnobTask::KnobTask(const char *name, IRotaryEncoderAdapter &sensorAdapter)
    : ISchedulableDialTask("sensorAdapter"), ISerialPortUser(configuredSerialPort()), name(name), sensorAdapter(sensorAdapter) {
  setInterval(0);
  setIterations(TASK_FOREVER);
}

void KnobTask::onSetup() {
  Log.traceln("[KNOB] Auto-Calibrating '%s'...", name);
  auto startMillis = millis();

  while (millis() - startMillis < 500) {
    // reading values in order to prevent an "initial spike" of wrong values in
    // the beginning
    sensorAdapter.readValues();
    startMillis = startMillis; // NOOP to satisfy Cling-Tidy
  }
}

void KnobTask::onCallback() {
  sensorAdapter.readValues();
  auto rotationAngleDelta = sensorAdapter.getRotationAngleDelta();

  if (rotationAngleDelta > ROTATION_THRESHOLD || rotationAngleDelta < -ROTATION_THRESHOLD) {
    sendData();
  }
}

void KnobTask::sendData() {
  // Create and output serialized JSON
  StaticJsonDocument<BUFFER_SIZE> jsonDoc;
  jsonDoc["type"] = getTaskType();
  jsonDoc["name"] = name;
  jsonDoc["time"] = millis();
  jsonDoc["rotationDelta"] = sensorAdapter.getRotationAngleDelta();

  serializeJson(jsonDoc, serial);
  serial.println();
}