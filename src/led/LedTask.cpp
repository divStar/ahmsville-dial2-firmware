//
// Created by Igor Voronin on 17.06.23.
//
#include "FastLED.h"
#include "LedTask.h"
#include "logger/Logger.h"

#define LED_TYPE    WS2812B
#define DATA_PIN    3
#define COLOR_ORDER GRB
#define NUM_LEDS    13
#define BRIGHTNESS  96

CRGB leds[NUM_LEDS];

LedTask::LedTask(LinkedList<RawDataDto *> *messagesToProcess)
        : messagesToProcess(messagesToProcess) {
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
        RawDataDto *rawDataDto = messagesToProcess->get(rawDataDtoIndex);

        if (strstr(rawDataDto->getRawData(), R"("type":"led")") != nullptr) {
            StaticJsonDocument<BUFFER_SIZE> jsonDoc;
            DeserializationError error = deserializeJson(jsonDoc, rawDataDto->getRawData(),
                                                         strlen(rawDataDto->getRawData()),
                                                         DeserializationOption::Filter(filterDoc));
            if (error) {
                Log.errorln("(LED) deserializeJson() failed: %s", error.c_str());
                return;
            }

            LedTask::applyData(jsonDoc.as<JsonVariantConst>());
            messagesToProcess->get(rawDataDtoIndex)->setValid(false);
        }
    }
}

void LedTask::applyData(JsonVariantConst jsonData) {
    JsonArrayConst ledDataJsonArray = jsonData.as<JsonArrayConst>();

    for (JsonObjectConst ledDataJson: ledDataJsonArray) {
        if (isValidData(ledDataJson)) {
            Log.traceln("Setting leds with (index, r, g, b, brightness) to (%d, %d, %d, %d, %d)",
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
    bool isLedIndexValid = jsonData["type"] == "led" &&
                           jsonData["ledIndex"].is<LedIndex>() &&
                           jsonData["ledIndex"] >= 0 &&
                           jsonData["ledIndex"] <= 12;
    if (!isLedIndexValid) {
        Log.errorln("LedIndex is invalid: %d", jsonData["ledIndex"].as<LedIndex>());
    }

    bool isToColorRValid = jsonData["toColor"][0].is<byte>();
    if (!isToColorRValid) {
        Log.errorln("toColor[R] is invalid: %d", jsonData["toColor"][0].as<LedIndex>());
    }

    bool isToColorGValid = jsonData["toColor"][1].is<byte>();
    if (!isToColorGValid) {
        Log.errorln("toColor[G] is invalid: %d", jsonData["toColor"][1].as<LedIndex>());
    }

    bool isToColorBValid = jsonData["toColor"][2].is<byte>();
    if (!isToColorBValid) {
        Log.errorln("toColor[B] is invalid: %d", jsonData["toColor"][2].as<LedIndex>());
    }

    bool isBrightnessValid = jsonData["misc"]["brightness"].is<byte>();
    if (!isBrightnessValid) {
        Log.errorln("brightness is invalid: %d", jsonData["misc"]["brightness"].as<LedIndex>());
    }

    return isLedIndexValid && isToColorRValid && isToColorGValid && isToColorBValid && isBrightnessValid;
}
