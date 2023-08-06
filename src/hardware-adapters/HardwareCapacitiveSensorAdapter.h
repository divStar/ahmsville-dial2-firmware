#ifndef DIALER_HARDWARECAPACITIVESENSORADAPTER_H
#define DIALER_HARDWARECAPACITIVESENSORADAPTER_H

#include <CapacitiveSensor.h>
#include "interfaces/sensors/ICapacitiveSensorAdapter.h"

/**
 * @class   HardwareCapacitiveSensorAdapter
 * @brief   The actual hardware implementation of the capacitive sensor adapter used by the application.
 *
 * @author  Igor Voronin
 * @date    06.08.2023
 */
class HardwareCapacitiveSensorAdapter : public ICapacitiveSensorAdapter {
public:
    /**
     * @brief Constructor.
     *
     * @param sendingPin    (byte) number of the pin sending information to the sensorAdapter
     * @param receivingPin  (byte) number of the pin receiving information from the sensorAdapter
     */
    explicit HardwareCapacitiveSensorAdapter(uint8_t sendingPin, uint8_t receivingPin);

    void set_CS_AutocaL_Millis(unsigned long millis) override;

    long capacitiveSensor(uint8_t samples) override;

private:
    /**
     * @brief Actual hardware capacitive sensor.
     */
    CapacitiveSensor sensor;
};

#endif //DIALER_HARDWARECAPACITIVESENSORADAPTER_H
