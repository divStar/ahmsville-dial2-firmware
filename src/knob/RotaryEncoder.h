#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include <SimpleKalmanFilter.h>
#include "logger/Logger.h"

/**
 * @class   RotaryEncoder
 * @brief   Retrieves and calculates rotation-related data.
 *
 * This class handles rotation changes and signal smoothing.
 *
 * @author  Igor Voronin
 * @date    06.07.2023
 */
class RotaryEncoder {
public:
    /**
     * @brief Constructor.
     *
     * @param pin0          (int) number of the first pin of the knob
     * @param pin1          (int) number of the second pin of the knob
     * @param pinInterrupt0 (int) number of the first interrupt-pin of the knob (currently not used)
     * @param pinInterrupt1 (int) number of the second interrupt-pin of the knob (currently not used)
     */
    explicit RotaryEncoder(int pin0, int pin1, int pinInterrupt0, int pinInterrupt1);

    /**
     * @brief Reads values from the sensor, smoothens them and calculates the rotation angle.
     */
    void readValues();

    /**
     * @return (float) Gets the positive or negative rotation angle delta between the current and the previous angle.
     */
    float getRotationAngleDelta();

private:
    /**
     * @brief This constant describes the midpoint between the north and south and south and north poles.
     *
     * <p>This constant is "good-enough", but certainly not very accurate as the magnets are not identical.</p>
     */
    static const int SENSOR_MIDPOINT = 500;

    /**
     * @brief Number of the first pin of the knob.
     */
    int pin0;
    /**
     * @brief Number of the second pin of the knob.
     */
    int pin1;

    /**
     * @brief Holder for the hall sensor values.
     */
    float *values = new float[2]{0.0, 0.0};

    /**
     * @brief Previous rotation angle.
     */
    float previousRotationAngle = 0;

    /**
     * @brief Kalman filter for the first sensor.
     */
    SimpleKalmanFilter filteredSensor1Value;
    /**
     * @brief Kalman filter for the second sensor.
     */
    SimpleKalmanFilter filteredSensor2Value;
};

#endif //ROTARYENCODER_H
