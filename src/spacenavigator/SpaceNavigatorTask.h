#ifndef DIALER_SPACENAVIGATORTASK_H
#define DIALER_SPACENAVIGATORTASK_H

#include <Arduino.h>
#include "../../lib/mpu6050-custom/helper_3dmath.h"
#include "../../lib/mpu6050-custom/MPU6050.h"
#include "interfaces/ISchedulableDialTask.h"
#include "logger/Logger.h"
#include "json/JsonSerializer.h"

/**
 * @class   SpaceNavigatorTask
 * @brief   Task to handle the space navigator (joystick).
 *
 * This class is a ISchedulableDialTask, that handles the space navigator (joystick) of the AhmsVille Dial2.
 *
 * @author  Igor Voronin
 * @date    29.07.2023
 */
class SpaceNavigatorTask : public ISchedulableDialTask, private ISerialPortUser {
public:
    /**
     * @brief Constructor.
     */
    SpaceNavigatorTask();

    void onSetup() override;

    void onCallback() override;

private:
    /**
     * @brief Number of the pin, that is being written to to start the space navigator capabilities.
     */
    static const auto STARTER_PIN = 30;
    /**
     * @brief Number of the interrupt pin.
     */
    static const auto INTERRUPT_PIN = 2;

    /**
     * @brief This variable describes if DMP completed. The dummy value should be overwritten during setup().
     */
    unsigned int dmpInitDone = 100;

    /**
     * @brief MPU6050, that is used to set up and receive the accelerometer as well as the gyroscope.
     */
    MPU6050 mpu;

    /**
     * @brief This function currently has no use, but is passed to `attachInterrupt` on set up.
     */
    static void dmpDataReady();
};


#endif //DIALER_SPACENAVIGATORTASK_H
