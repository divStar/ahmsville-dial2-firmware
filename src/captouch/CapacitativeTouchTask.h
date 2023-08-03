#ifndef DIALER_CAPACITATIVETOUCHTASK_H
#define DIALER_CAPACITATIVETOUCHTASK_H

#include <CapacitiveSensor.h>
#include <ArduinoJson.h>
#include "logger/Logger.h"
#include "interfaces/ISchedulableDialTask.h"

/**
 * @class   CapacitativeTouchTask
 * @brief   Task to handle the capacitative touch button sensor.
 *
 * This class is a ISchedulableDialTask, that handles the capacitative touch button sensor.
 *
 * @author  Igor Voronin
 * @date    29.07.2023
 */
class CapacitativeTouchTask : public ISchedulableDialTask {
public:
    /**
     * @brief Constructor.
     *
     * @param sendingPin    (byte) number of the pin sending information to the sensor
     * @param receivingPin  (byte) number of the pin receiving information from the sensor
     */
    explicit CapacitativeTouchTask(byte sendingPin, byte receivingPin);

    void onSetup() override;

    void onCallback() override;

private:
    /**
     * @brief Amount of samples taken into account when detecting the sensor value.
     */
    static const auto SAMPLES = 255;
    /**
     * @brief Determines how high the value must be to detect proximity.
     */
    static const auto PROXIMITY_THRESHOLD = 300;
    /**
     * @brief Buffer size of the JSON output.
     */
    static const auto BUFFER_SIZE = 96;

    /**
     * @brief CapacitativeSensor class handling the sensor access
     */
    CapacitiveSensor sensor;

    /**
     * @brief Command to handle sending retrieved sensor values to the Serial port.
     *
     * @param sensorValue (long) sensor value retrieved from the sensor
     */
    void sendData(long sensorValue);
};


#endif //DIALER_CAPACITATIVETOUCHTASK_H
