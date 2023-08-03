#include "LedTask.h"

/**
 * @brief Array of LEDs, initialized with the amount of LEDs.
 *
 * This variables needs to stay here since in the header file it'd be imported multiple times.
 */
CRGB leds[NUM_LEDS];

LedTask::LedTask(LinkedList<InputMessageDto *> *messagesToProcess)
        : ISchedulableDialTask("led"), messagesToProcess(messagesToProcess) {
    setInterval(0);
    setIterations(TASK_FOREVER);
    filterDoc[0]["type"] = true;
    filterDoc[0]["ledIndex"] = true;
    filterDoc[0]["toColor"] = true;
    filterDoc[0]["misc"] = true;
}

void LedTask::onSetup() {
    CFastLED::addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
            .setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}

void LedTask::onCallback() {
    for (int rawDataDtoIndex = messagesToProcess->size() - 1; rawDataDtoIndex >= 0; --rawDataDtoIndex) {
        InputMessageDto *rawDataDto = messagesToProcess->get(rawDataDtoIndex);
        char taskType[30];
        sprintf(taskType, R"("type":"%s")", getTaskType());

        if (strstr(rawDataDto->getRawInputData(), taskType) != nullptr) {
            StaticJsonDocument<BUFFER_SIZE> jsonDoc;
            DeserializationError error = deserializeJson(jsonDoc, rawDataDto->getRawInputData(),
                                                         strlen(rawDataDto->getRawInputData()),
                                                         DeserializationOption::Filter(filterDoc));
            if (error) {
                char errorMessage[150];
                sprintf(errorMessage, "[LED] deserializeJson() failed: %s", error.c_str());
                ErrorSerializer::serializeToJsonAndSend(getTaskType(), "L1", errorMessage);

                Log.errorln(errorMessage);
                return;
            }

            LedTask::useData(jsonDoc.as<JsonVariantConst>());
            messagesToProcess->get(rawDataDtoIndex)->setValid(false);
        }
    }
}

void LedTask::useData(JsonVariantConst jsonData) {
    JsonArrayConst ledDataJsonArray = jsonData.as<JsonArrayConst>();

    for (JsonObjectConst ledDataJson: ledDataJsonArray) {
        if (isValidData(ledDataJson)) {
            Log.traceln("[LED] Setting leds with (index, r, g, b, brightness) to (%d, %d, %d, %d, %d)",
                        ledDataJson["ledIndex"].as<byte>(),
                        ledDataJson["toColor"][0].as<byte>(),
                        ledDataJson["toColor"][1].as<byte>(),
                        ledDataJson["toColor"][2].as<byte>(),
                        ledDataJson["misc"]["brightness"].as<byte>());

            leds[ledDataJson["ledIndex"].as<byte>()].setRGB(
                    ledDataJson["toColor"][0].as<byte>(),
                    ledDataJson["toColor"][1].as<byte>(),
                    ledDataJson["toColor"][2].as<byte>()
            );

            leds[ledDataJson["ledIndex"].as<byte>()].maximizeBrightness(
                    ledDataJson["misc"]["brightness"].as<byte>());

            FastLED.show();
        }
    }
}

bool LedTask::isValidData(JsonVariantConst jsonData) {
    bool isLedIndexValid = jsonData["type"] == getTaskType() &&
                           jsonData["ledIndex"].is<LedIndexEnum>() &&
                           jsonData["ledIndex"] >= 0 &&
                           jsonData["ledIndex"] <= 12;
    if (!isLedIndexValid) {
        sendValidationError("L2", "[LED] LedIndexEnum is invalid: %d", jsonData["ledIndex"].as<byte>());
    }

    bool isToColorRValid = jsonData["toColor"][0].is<byte>();
    if (!isToColorRValid) {
        sendValidationError("L3", "[LED] toColor[R] is invalid: %d", jsonData["toColor"][0].as<byte>());
    }

    bool isToColorGValid = jsonData["toColor"][1].is<byte>();
    if (!isToColorGValid) {
        sendValidationError("L4", "[LED] toColor[G] is invalid: %d", jsonData["toColor"][1].as<byte>());
    }

    bool isToColorBValid = jsonData["toColor"][2].is<byte>();
    if (!isToColorBValid) {
        sendValidationError("L5", "[LED] toColor[B] is invalid: %d", jsonData["toColor"][1].as<byte>());
    }

    bool isBrightnessValid = jsonData["misc"]["brightness"].is<byte>();
    if (!isBrightnessValid) {
        sendValidationError("L6", "[LED] brightness is invalid: %d", jsonData["misc"]["brightness"].as<byte>());
    }

    return isLedIndexValid && isToColorRValid && isToColorGValid && isToColorBValid && isBrightnessValid;
}

void LedTask::sendValidationError(const char *error, const char *message, byte data) {
    char validationErrorMessage[50];
    sprintf(validationErrorMessage, message, data);
    ErrorSerializer::serializeToJsonAndSend(getTaskType(), error, validationErrorMessage);

    Log.errorln(validationErrorMessage);
}
