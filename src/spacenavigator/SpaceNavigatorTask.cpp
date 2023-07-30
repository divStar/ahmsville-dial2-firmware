//
// Created by Igor Voronin on 29.07.23.
//

#include "SpaceNavigatorTask.h"

SpaceNavigatorTask::SpaceNavigatorTask(MPU6050 *mpu)
: mpu(mpu) {}

void SpaceNavigatorTask::onSetup() {
    // supply your own gyro offsets here, scaled for min sensitivity
    mpu->setXGyroOffset(220);
    mpu->setYGyroOffset(76);
    mpu->setZGyroOffset(-85);
    mpu->setZAccelOffset(1788); // 1688 factory default for my test chip

    if (mpu->testConnection()) {
        Log.traceln("[MPU6050] connection probe successfully");
    } else {
        Log.errorln("[MPU6050] connection probe has failed");
    }
}

void SpaceNavigatorTask::onCallback() {

}
