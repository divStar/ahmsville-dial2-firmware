#include "HardwareSpaceNavigatorSensorAdapter.h"

HardwareSpaceNavigatorSensorAdapter::HardwareSpaceNavigatorSensorAdapter(byte starterPin, byte interruptPin)
    : starterPin(starterPin), interruptPin(interruptPin), mpu(MPU6050_IMU::MPU6050_ADDRESS_AD0_HIGH) {}

void HardwareSpaceNavigatorSensorAdapter::setup() {
  pinMode(starterPin, OUTPUT);
  digitalWrite(starterPin, LOW);
  delay(250);

  Wire.begin();
  Wire.setClock(400000);
  mpu.initialize();
  dmpInitDone = mpu.dmpInitialize();
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), dmpDataReady, RISING);
}

void HardwareSpaceNavigatorSensorAdapter::calibrate() {
  // supply your own gyro offsets here, scaled for min sensitivity
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
}

bool HardwareSpaceNavigatorSensorAdapter::testConnection() { return mpu.testConnection(); }

void HardwareSpaceNavigatorSensorAdapter::getMotion6(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz) {
  return mpu.getMotion6(ax, ay, az, gx, gy, gz);
}

bool HardwareSpaceNavigatorSensorAdapter::isDmpInitDone() { return dmpInitDone == 0; }

void HardwareSpaceNavigatorSensorAdapter::dmpDataReady() {}
