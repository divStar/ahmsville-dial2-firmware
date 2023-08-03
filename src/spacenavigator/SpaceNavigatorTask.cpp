#include "SpaceNavigatorTask.h"

SpaceNavigatorTask::SpaceNavigatorTask()
        : ISchedulableDialTask("spacenavigator"), mpu(MPU6050_IMU::MPU6050_ADDRESS_AD0_HIGH) {
    setInterval(100);
    setIterations(TASK_FOREVER);
}

void SpaceNavigatorTask::onSetup() {
    pinMode(STARTER_PIN, OUTPUT);
    digitalWrite(STARTER_PIN, LOW);
    delay(250);

    Wire.begin();
    Wire.setClock(400000);
    mpu.initialize();
    dmpInitDone = mpu.dmpInitialize();
    pinMode(INTERRUPT_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    if (mpu.testConnection()) {
        Log.traceln("[MPU6050] connection probe successfully");
    } else {
        ErrorSerializer::serializeToJsonAndSend(getTaskType(), "SN1", "[MPU6050] connection probe has failed");

        Log.errorln("[MPU6050] connection probe has failed");
    }
}

void SpaceNavigatorTask::onCallback() {
    if (dmpInitDone == 0) {
        int16_t accelX, accelY, accelZ;
        int16_t gyroX, gyroY, gyroZ;

        // Read raw accelerometer and gyroscope values
        mpu.getMotion6(&accelX, &accelY, &accelZ, &gyroX, &gyroY, &gyroZ);

        // Print accelerometer values
        SerialUSB.print("Accelerometer: ");
        SerialUSB.print("X: ");
        SerialUSB.print(accelX);
        SerialUSB.print(" Y: ");
        SerialUSB.print(accelY);
        SerialUSB.print(" Z: ");
        SerialUSB.println(accelZ);

        // Print gyroscope values
        SerialUSB.print("Gyroscope: ");
        SerialUSB.print("X: ");
        SerialUSB.print(gyroX);
        SerialUSB.print(" Y: ");
        SerialUSB.print(gyroY);
        SerialUSB.print(" Z: ");
        SerialUSB.println(gyroZ);
    }
}

void SpaceNavigatorTask::dmpDataReady() {
}
