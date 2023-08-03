#ifndef DIALER_HAPTICTASK_H
#define DIALER_HAPTICTASK_H

#include <FastLED.h>
#include <LinkedList.h>
#include "ArduinoJson.h"
#include "interfaces/IMessageConsumer.h"
#include "inputprocessor/InputMessageDto.h"
#include "logger/Logger.h"
#include "interfaces/ISchedulableDialTask.h"
#include "json/JsonSerializer.h"

/**
 * @class   HapticTask
 * @brief   Task to handle the haptic motor.
 *
 * This class is a ISchedulableDialTask, that handles haptic motor.
 *
 * @author  Igor Voronin
 * @date    28.07.2023
 */
class HapticTask : public ISchedulableDialTask, private ISerialPortUser, private IMessageConsumer {
public:
    /**
     * @brief Constructor.
     *
     * @param messagesToProcess (LinkedList<InputMessageDto *>*) pointer to the list containing messages to be processed
     */
    explicit HapticTask(LinkedList<InputMessageDto *> &messagesToProcess);

    void onCallback() override;

private:
    /**
     * @brief pin number for the haptic vibration motor.
     */
    static const int HAPTIC_PIN = 4;

    /**
     * @brief Buffer size of the JSON output.
     */
    static const int BUFFER_SIZE = 64;

    /**
     * @brief JSON-formatted filter string, that describes which attributes are kept when parsing a message.
     */
    StaticJsonDocument<64> filterDoc; // this JSON describes what to filter for

    void useData(JsonVariantConst jsonData) override;

    bool isValidData(JsonVariantConst jsonData) override;
};

#endif //DIALER_HAPTICTASK_H
