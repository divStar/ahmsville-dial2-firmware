#include "SpaceNavigatorTask.h"

SpaceNavigatorTask::SpaceNavigatorTask(ISpaceNavigatorSensorAdapter &sensorAdapter)
    : ISchedulableDialTask("spacenavigator"), ISerialPortUser(configuredSerialPort()), sensorAdapter(sensorAdapter) {
  setInterval(100);
  setIterations(TASK_FOREVER);
}

void SpaceNavigatorTask::onSetup() {
  sensorAdapter.setup();
  sensorAdapter.calibrate();

  if (sensorAdapter.testConnection()) {
    Log.traceln("[MPU6050] connection probe successfully");
  } else {
    JsonSerializer::sendJsonError(serial, getTaskType(), "SN1", "[MPU6050] connection probe has failed");

    Log.errorln("[MPU6050] connection probe has failed");
  }
}

void SpaceNavigatorTask::onCallback() {
  if (sensorAdapter.isDmpInitDone()) {
    int16_t accelX, accelY, accelZ;
    int16_t gyroX, gyroY, gyroZ;

    // Read raw accelerometer and gyroscope values
    sensorAdapter.getMotion6(&accelX, &accelY, &accelZ, &gyroX, &gyroY, &gyroZ);

    // Output raw accelerometer and gyroscope values
    StaticJsonDocument<BUFFER_SIZE> jsonDoc;
    jsonDoc["type"] = getTaskType();
    jsonDoc["time"] = millis();
    jsonDoc["accel"][0] = accelX;
    jsonDoc["accel"][1] = accelY;
    jsonDoc["accel"][2] = accelZ;
    jsonDoc["gyro"][0] = gyroX;
    jsonDoc["gyro"][1] = gyroY;
    jsonDoc["gyro"][2] = gyroZ;
    serializeJson(jsonDoc, serial);
    serial.println();
  }
}
