#ifndef DIALER_ISPACENAVIGATORSENSORADAPTER_H
#define DIALER_ISPACENAVIGATORSENSORADAPTER_H

/**
 * @class   ISpaceNavigatorSensorAdapter
 * @brief   Interface to decouple the actual MPU6050 sensor(s) from the task processing it.
 *
 * This interface decouples the MPU6050 sensor(s) from the task, that uses it, and allows for proper testing.
 *
 * @author  Igor Voronin
 * @date    06.08.2023
 */
class ISpaceNavigatorSensorAdapter {
public:
    /**
     * @brief Sets up the MPU6050 sensor (or a mock thereof).
     */
    virtual void setup() = 0;

    /**
     * @brief Calibrates the MPU6050 sensor (or a mock thereof).
     */
    virtual void calibrate() = 0;

    /**
     * @brief Tests the connection to the MPU6050 sensor (or a mock thereof).
     */
    virtual bool testConnection() = 0;

    /**
     * @brief Retrieves the accelerometer and gyroscope x, y and z values and writes them to the supplied variables.
     *
     * @param ax (int16_t) accelerometer X
     * @param ay (int16_t) accelerometer Y
     * @param az (int16_t) accelerometer Z
     * @param gx (int16_t) gyroscope X
     * @param gy (int16_t) gyroscope Y
     * @param gz (int16_t) gyroscope Z
     */
    virtual void getMotion6(int16_t *ax, int16_t *ay, int16_t *az, int16_t *gx, int16_t *gy, int16_t *gz) = 0;

    /**
     * @brief Retrieves whether the DMP initialization has finished successfully (<code>dmpInitDone = 0</code>).
     *
     * @return (bool) <code>true</code> if the DMP initialization finished successfully, <code>false</code> otherwise
     */
    virtual bool isDmpInitDone() = 0;
};

#endif //DIALER_ISPACENAVIGATORSENSORADAPTER_H
