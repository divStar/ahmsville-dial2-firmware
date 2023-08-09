#ifndef DIALER_ICAPACITIVESENSORADAPTER_H
#define DIALER_ICAPACITIVESENSORADAPTER_H

/**
 * @class   ICapacitiveSensorAdapter
 * @brief   Interface to decouple the actual capacitive sensor from the task
 * processing it.
 *
 * This interface decouples the capacitive sensor from the task, that uses it,
 * and allows for proper testing.
 *
 * @author  Igor Voronin
 * @date    06.08.2023
 */
class ICapacitiveSensorAdapter {
public:
  /**
   * @brief Sets the exact same value on the actual sensor class (or mock).
   *
   * @param millis (unsigned long) milliseconds to reset to
   */
  virtual void set_CS_AutocaL_Millis(unsigned long millis) = 0;

  /**
   * @brief Retrieves the sensor values, uses the given amount of samples.
   *
   * @param samples (uint8_t) amount of samples of the sensor value
   * @return (long) sensor value
   */
  virtual long capacitiveSensor(uint8_t samples) = 0;
};

#endif // DIALER_ICAPACITIVESENSORADAPTER_H
