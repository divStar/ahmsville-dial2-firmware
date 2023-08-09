#ifndef DIALER_HARDWARESPACENAVIGATORSENSORADAPTER_H
#define DIALER_HARDWARESPACENAVIGATORSENSORADAPTER_H

#include <Wire.h>
#include <api/Common.h>
#include "MPU6050.h"
#include "helper_3dmath.h"
#include "interfaces/sensors/ISpaceNavigatorSensorAdapter.h"
#include "json/JsonSerializer.h"
#include "logger/Logger.h"

/**
 * @class   HardwareSpaceNavigatorSensorAdapter
 * @brief   The actual hardware implementation of the MPU6050 sensor(s) adapter
 * used by the application.
 *
 * @author  Igor Voronin
 * @date    06.08.2023
 */
class HardwareSpaceNavigatorSensorAdapter : public ISpaceNavigatorSensorAdapter {
public:
  explicit HardwareSpaceNavigatorSensorAdapter(byte starterPin, byte interruptPin);

  void setup() override;

  void calibrate() override;

  bool testConnection() override;

  void getMotion6(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz) override;

  bool isDmpInitDone() override;

private:
  /**
   * @brief the starter pin (e.g. pin 30 by default).
   */
  byte starterPin;

  /**
   * @brief the interrupt pin (e.g. pin 2 by default).
   */
  byte interruptPin;

  /**
   * @brief MPU6050, that is used to set up and receive the accelerometer as
   * well as the gyroscope.
   */
  MPU6050 mpu;

  /**
   * @brief This variable describes if DMP completed. The dummy value should be
   * overwritten during setup().
   */
  unsigned int dmpInitDone = 100;

  /**
   * @brief This function currently has no use, but is passed to
   * `attachInterrupt` on set up.
   */
  static void dmpDataReady();
};

#endif // DIALER_HARDWARESPACENAVIGATORSENSORADAPTER_H
