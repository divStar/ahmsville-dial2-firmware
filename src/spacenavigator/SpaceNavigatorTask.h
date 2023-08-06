#ifndef DIALER_SPACENAVIGATORTASK_H
#define DIALER_SPACENAVIGATORTASK_H

#include "interfaces/ISchedulableDialTask.h"
#include "logger/Logger.h"
#include "json/JsonSerializer.h"
#include "interfaces/sensors/ISpaceNavigatorSensorAdapter.h"

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
     *
     * @param sensorAdapter (ISpaceNavigatorSensorAdapter) sensor adapter to use
     */
    explicit SpaceNavigatorTask(ISpaceNavigatorSensorAdapter &sensorAdapter);

    void onSetup() override;

    void onCallback() override;

private:
    /**
     * @brief Buffer size of the JSON output.
     */
    static const int BUFFER_SIZE = 256;

    /**
     * @brief sensor adapter handling sensor-related functionality
     */
    ISpaceNavigatorSensorAdapter &sensorAdapter;
};


#endif //DIALER_SPACENAVIGATORTASK_H
