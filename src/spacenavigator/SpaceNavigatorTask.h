//
// Created by Igor Voronin on 29.07.23.
//

#ifndef DIALER_SPACENAVIGATORTASK_H
#define DIALER_SPACENAVIGATORTASK_H

#include <Arduino.h>
#include "../../lib/mpu6050-custom/helper_3dmath.h"
#include "../../lib/mpu6050-custom/MPU6050.h"
#include "interfaces/ISchedulableDialTask.h"
#include "logger/Logger.h"
#include "error/ErrorSerializer.h"

class SpaceNavigatorTask : public ISchedulableDialTask {
public:
    explicit SpaceNavigatorTask();

    void onSetup() override;

    void onCallback() override;

private:
    static const auto STARTER_PIN = 30;
    static const auto INTERRUPT_PIN = 2;

    unsigned int dmpInitDone = 100;
    MPU6050 mpu;

    static void dmpDataReady();
};


#endif //DIALER_SPACENAVIGATORTASK_H
