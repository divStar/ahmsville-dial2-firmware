#ifndef DIALER_LEDTASK_H
#define DIALER_LEDTASK_H

#include <FastLED.h>
#include <LinkedList.h>
#include "ArduinoJson.h"
#include "LedIndexEnum.h"
#include "interfaces/IMessageConsumer.h"
#include "inputprocessor/InputMessageDto.h"
#include "logger/Logger.h"
#include "interfaces/ISchedulableDialTask.h"
#include "json/JsonSerializer.h"

#define LED_TYPE    WS2812B
#define DATA_PIN    3
#define COLOR_ORDER GRB
#define NUM_LEDS    13
#define BRIGHTNESS  96

/**
 * @class   LedTask
 * @brief   Task to handle the LEDs.
 *
 * This class is a ISchedulableDialTask, that handles the LEDs on the AhmsVille Dial2.
 *
 * @author  Igor Voronin
 * @date    06.07.2023
 */
class LedTask : public ISchedulableDialTask, private ISerialPortUser, private IMessageConsumer {
public:
    /**
     * @brief Constructor.
     *
     * @param messagesToProcess (LinkedList<InputMessageDto *>*) pointer to the list containing messages to be processed
     */
    explicit LedTask(LinkedList<InputMessageDto *> &messagesToProcess);

    void onSetup() override;

    void onCallback() override;

private:
    /**
     * @brief Buffer size of the JSON output.
     */
    static const int BUFFER_SIZE = 2048;

    /**
     * @brief JSON-formatted filter string, that describes which attributes are kept when parsing a message.
     */
    StaticJsonDocument<128> filterDoc; // this JSON describes what to filter for

    void useData(JsonVariantConst jsonData) override;

    bool isValidData(JsonVariantConst jsonData) override;

    /**
     * @brief Sends a validation json using the JsonSerializer.
     *
     * @param error     (const char*) json (number or name)
     * @param message   (const char*) message to send
     * @param data      (byte) supposedly invalid data
     */
    void sendValidationError(const char *error, const char *message, byte data);
};

#endif //DIALER_LEDTASK_H
