#ifndef DIALER_HARDWAREHAPTICSENSORADAPTER_H
#define DIALER_HARDWAREHAPTICSENSORADAPTER_H

#include <api/Common.h>
#include "interfaces/sensors/IHapticSensorAdapter.h"

/**
 * @class   HardwareHapticSensorAdapter
 * @brief   The actual hardware implementation of the haptic sensor adapter used by the application.
 *
 * @author  Igor Voronin
 * @date    06.08.2023
 */
class HardwareHapticSensorAdapter : public IHapticSensorAdapter {
public:
    /**
     * @brief Constructor.
     *
     * @param hapticPin (byte) pin of the haptic sensor
     */
    explicit HardwareHapticSensorAdapter(byte hapticPin);

    void writeStrength(byte strength) override;

private:
    /**
     * @brief pin of the haptic sensor.
     */
    byte hapticPin;
};

#endif //DIALER_HARDWAREHAPTICSENSORADAPTER_H
