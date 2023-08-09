#ifndef DIALER_KNOBTASK_H
#define DIALER_KNOBTASK_H

#include <ArduinoJson.h>
#include "interfaces/ISchedulableDialTask.h"
#include "interfaces/ISerialPortUser.h"
#include "interfaces/sensors/IRotaryEncoderAdapter.h"
#include "logger/Logger.h"

/**
 * @class   KnobTask
 * @brief   Task to handle a sensorAdapter.
 *
 * This class is a ISchedulableDialTask, that handles a sensorAdapter.
 *
 * <p>Make sure to register proper pins and give the sensorAdapter a proper name
 * to be able to distinguish it from other knobs.</p>
 *
 * @author  Igor Voronin
 * @date    06.07.2023
 */
class KnobTask : public ISchedulableDialTask, public ISerialPortUser {
public:
  /**
   * @brief Constructor.
   *
   * @param name          (const char*) name of the sensorAdapter
   * @param sensorAdapter (IRotaryEncoderAdapter) sensor adapter to use
   */
  explicit KnobTask(const char *name, IRotaryEncoderAdapter &sensorAdapter);

  void onSetup() override;

  void onCallback() override;

private:
  /**
   * @brief Buffer size of the JSON output.
   */
  static const int BUFFER_SIZE = 96;

  /**
   * @brief Rotation threshold, which specifies the angle, at which a rotation
   * is first registered.
   */
  constexpr static const float ROTATION_THRESHOLD = 0.004;

  /**
   * @brief Name of the sensorAdapter.
   */
  const char *name;

  /**
   * @brief Rotatry encoder for the sensorAdapter, which handles all necessary
   * calculations.
   */
  IRotaryEncoderAdapter &sensorAdapter;

  /**
   * @brief Handles sending the retrieved sensorAdapter values to the Serial
   * port.
   */
  void sendData();
};

#endif // DIALER_KNOBTASK_H
