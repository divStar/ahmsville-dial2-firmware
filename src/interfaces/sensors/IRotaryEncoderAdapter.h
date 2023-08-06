#ifndef DIALER_IROTARYENCODERADAPTER_H
#define DIALER_IROTARYENCODERADAPTER_H

/**
 * @class   IRotaryEncoderAdapter
 * @brief   Interface to decouple the actual rotary encoder sensors from the task processing it.
 *
 * This interface decouples the rotary encoder sensors from the task, that uses it, and allows for proper testing.
 *
 * @author  Igor Voronin
 * @date    06.08.2023
 */
class IRotaryEncoderAdapter {
public:
    /**
     * @brief Reads values from the sensor.
     */
    virtual void readValues() = 0;

    /**
     * @return (float) Gets the positive or negative rotation angle delta between the current and the previous angle.
     */
    virtual float getRotationAngleDelta() const = 0;
};

#endif //DIALER_IROTARYENCODERADAPTER_H
