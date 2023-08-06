#ifndef DIALER_CAPACITIVETOUCHTASK_H
#define DIALER_CAPACITIVETOUCHTASK_H

#include <CapacitiveSensor.h>
#include <ArduinoJson.h>
#include "logger/Logger.h"
#include "interfaces/ISchedulableDialTask.h"
#include "interfaces/ISerialPortUser.h"
#include "interfaces/sensors/ICapacitiveSensorAdapter.h"

/**
 * @class   CapacitiveTouchTask
 * @brief   Task to handle the capacitative touch button sensorAdapter.
 *
 * This class is a ISchedulableDialTask, that handles the capacitative touch button sensorAdapter.
 *
 * @author  Igor Voronin
 * @date    29.07.2023
 */
class CapacitiveTouchTask : public ISchedulableDialTask, private ISerialPortUser {
public:
    /**
     * @brief Constructor.
     *
     * @param sensorAdapter (ICapacitiveSensorAdapter) sensor adapter to use
     */
    explicit CapacitiveTouchTask(ICapacitiveSensorAdapter &sensorAdapter);

    void onSetup() override;

    void onCallback() override;

private:
    /**
     * @brief Amount of samples taken into account when detecting the sensorAdapter value.
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
     * @brief sensor adapter handling sensor-related functionality
     */
    ICapacitiveSensorAdapter &sensorAdapter;

    /**
     * @brief Command to handle sending retrieved sensorAdapter values to the Serial port.
     *
     * @param sensorValue (long) sensorAdapter value retrieved from the sensorAdapter
     */
    void sendData(long sensorValue);
};


#endif //DIALER_CAPACITIVETOUCHTASK_H
