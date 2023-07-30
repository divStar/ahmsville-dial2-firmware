//
// Created by Igor Voronin on 29.07.23.
//

#ifndef DIALER_SPACENAVIGATORTASK_H
#define DIALER_SPACENAVIGATORTASK_H

#include <Arduino.h>
#include <MPU6050.h>
#include "interfaces/ISchedulableDialTask.h"
#include "logger/Logger.h"

class SpaceNavigatorTask : public ISchedulableDialTask {
public:
    explicit SpaceNavigatorTask(MPU6050 *mpu);

    void onSetup() override;

    void onCallback() override;

private:
    MPU6050 *mpu;
};


#endif //DIALER_SPACENAVIGATORTASK_H
