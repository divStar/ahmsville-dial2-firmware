#ifndef DIALER_IHAPTICSENSORADAPTER_H
#define DIALER_IHAPTICSENSORADAPTER_H

/**
 * @class   IHapticSensorAdapter
 * @brief   Interface to decouple the actual haptic sensor from the task
 * processing it.
 *
 * This interface decouples the haptic sensor from the task, that uses it, and
 * allows for proper testing.
 *
 * @author  Igor Voronin
 * @date    06.08.2023
 */
class IHapticSensorAdapter {
public:
  /**
   * @brief Writes the given strength value to the haptic sensor.
   *
   * @param strength (byte) strength value for the haptic sensor; 0 to 255 seem
   * like sensible values
   */
  virtual void writeStrength(byte strength) = 0;
};

#endif // DIALER_IHAPTICSENSORADAPTER_H
