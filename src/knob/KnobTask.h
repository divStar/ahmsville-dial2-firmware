#ifndef DIALER_KNOBTASK_H
#define DIALER_KNOBTASK_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "RotaryEncoder.h"
#include "interfaces/ISchedulableDialTask.h"

/**
 * @class   KnobTask
 * @brief   Task to handle a knob.
 *
 * This class is a ISchedulableDialTask, that handles a knob.
 *
 * <p>Make sure to register proper pins and give the knob a proper name to be able to distinguish it from other knobs.</p>
 *
 * @author  Igor Voronin
 * @date    06.07.2023
 */
class KnobTask : public ISchedulableDialTask {
public:
    /**
     * @brief Constructor.
     *
     * @param name          (const char*) name of the knob
     * @param pin0          (int) number of the first pin of the knob
     * @param pin1          (int) number of the second pin of the knob
     * @param pinInterrupt0 (int) number of the first interrupt-pin of the knob (currently not used)
     * @param pinInterrupt1 (int) number of the second interrupt-pin of the knob (currently not used)
     */
    explicit KnobTask(const char *name, int pin0, int pin1, int pinInterrupt0, int pinInterrupt1);

    void onSetup() override;

    void onCallback() override;

private:
    /**
     * @brief Buffer size of the JSON output.
     */
    static const int BUFFER_SIZE = 96;

    /**
     * @brief Rotation threshold, which specifies the angle, at which a rotation is first registered.
     */
    constexpr static const float ROTATION_THRESHOLD = 0.004;

    /**
     * @brief Name of the knob.
     */
    const char *name;

    /**
     * @brief Rotatry encoder for the knob, which handles all necessary calculations.
     */
    RotaryEncoder knob;

    /**
     * @brief Command to handle sending retrieved sensor values to the Serial port.
     */
    void sendData();
};


#endif //DIALER_KNOBTASK_H
