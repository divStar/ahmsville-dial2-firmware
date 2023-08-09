#include "CapacitiveTouchTask.h"

CapacitiveTouchTask::CapacitiveTouchTask(ICapacitiveSensorAdapter &sensorAdapter)
    : ISchedulableDialTask("captouch"), ISerialPortUser(configuredSerialPort()), sensorAdapter(sensorAdapter) {
  setInterval(0);
  setIterations(TASK_FOREVER);
}

void CapacitiveTouchTask::onSetup() {
  // reset millis
  sensorAdapter.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void CapacitiveTouchTask::onCallback() {
  long sensorValue = sensorAdapter.capacitiveSensor(SAMPLES);

  if (sensorValue > PROXIMITY_THRESHOLD) {
    // Create and output serialized JSON
    sendData(sensorValue);
  }
}

void CapacitiveTouchTask::sendData(long sensorValue) {
  StaticJsonDocument<BUFFER_SIZE> jsonDoc;
  jsonDoc["type"] = getTaskType();
  jsonDoc["value"] = sensorValue;
  jsonDoc["time"] = millis();

  serializeJson(jsonDoc, serial);
  serial.println();
}
