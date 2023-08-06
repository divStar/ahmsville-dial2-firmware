#ifndef ROTARYENCODER_H
#define ROTARYENCODER_H

#include "SimpleKalmanFilter.h"
#include "logger/Logger.h"
#include "interfaces/sensors/IRotaryEncoderAdapter.h"

/**
 * @class   HardwareRotaryEncoderAdapter
 * @brief   Retrieves and calculates rotation-related data.
 *
 * This class handles rotation changes and signal smoothing.
 *
 * @author  Igor Voronin
 * @date    06.07.2023
 */
class HardwareRotaryEncoderAdapter: public IRotaryEncoderAdapter {
public:
    /**
     * @brief Constructor.
     *
     * @param pin0          (int) number of the first pin of the sensorAdapter
     * @param pin1          (int) number of the second pin of the sensorAdapter
     * @param pinInterrupt0 (int) number of the first interrupt-pin of the sensorAdapter (currently not used)
     * @param pinInterrupt1 (int) number of the second interrupt-pin of the sensorAdapter (currently not used)
     */
    explicit HardwareRotaryEncoderAdapter(int pin0, int pin1, int pinInterrupt0, int pinInterrupt1);

    /**
     * @brief Reads values from the sensorAdapter, smoothens them and calculates the rotation angle.
     */
    void readValues() override;

    float getRotationAngleDelta() const override;

private:
    /**
     * @brief This constant describes the midpoint between the north and south and south and north poles.
     *
     * <p>This constant is "good-enough", but certainly not very accurate as the magnets are not identical.</p>
     */
    static const int SENSOR_MIDPOINT = 500;

    /**
     * @brief Number of the first pin of the sensorAdapter.
     */
    int pin0;
    /**
     * @brief Number of the second pin of the sensorAdapter.
     */
    int pin1;

    /**
     * @brief Holder for the hall sensorAdapter values.
     */
    float *values = new float[2]{0.0, 0.0};

    /**
     * @brief Previous rotation angle.
     */
    float previousRotationAngle = 0;

    /**
     * @brief Current rotation angle delta.
     */
    float currentRotationAngleDelta = 0;

    /**
     * @brief Kalman filter for the first sensorAdapter.
     */
    SimpleKalmanFilter filteredSensor1Value;
    /**
     * @brief Kalman filter for the second sensorAdapter.
     */
    SimpleKalmanFilter filteredSensor2Value;

    /**
     * @brief Calculates the rotation angle delta between the current and previous rotation angles.
     *
     * @return (float) current rotation angle delta
     */
    float calculateRotationAngleDelta();
};

#endif //ROTARYENCODER_H
