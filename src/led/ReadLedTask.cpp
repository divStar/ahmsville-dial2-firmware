//
// Created by Igor Voronin on 18.06.23.
//
#include "ReadLedTask.h"
#include "logger/Logger.h"

ReadLedTask::ReadLedTask(Vector<LedDataDto *> *dataToProcess) : dataToProcess(dataToProcess) {
    filterDoc[0]["ledIndex"] = true;
    filterDoc[0]["toColor"] = true;
    filterDoc[0]["misc"] = true;
}

void ReadLedTask::onCallback() {
    if (SerialUSB.available()) {
        char buffer[BUFFER_SIZE];
        size_t size = SerialUSB.readBytesUntil('\n', buffer, BUFFER_SIZE);
        if (size > 0) {
            Log.traceln("Received %d character(s): %s", size, String(buffer, size).c_str());

            StaticJsonDocument<BUFFER_SIZE> jsonDoc;
            DeserializationError error = deserializeJson(jsonDoc, buffer, BUFFER_SIZE,
                                                         DeserializationOption::Filter(filterDoc));
            if (error) {
                Log.errorln("deserializeJson() failed: %s", error.c_str());
                return;
            }

            JsonArray ledDataJsonArray = jsonDoc.as<JsonArray>();
            Log.traceln("Parsed %d LedDataDto objects!", ledDataJsonArray.size());

            for (JsonObject ledDataJson: ledDataJsonArray) {
                if (isValidLedDataJson(ledDataJson)) {
                    Log.traceln("Adding LedDataDto for LED %d with RGB(%d,%d,%d) and brightness %d",
                                ledDataJson["ledIndex"].as<LedIndex>(),
                                ledDataJson["toColor"][0].as<byte>(),
                                ledDataJson["toColor"][0].as<byte>(),
                                ledDataJson["toColor"][0].as<byte>(),
                                ledDataJson["misc"]["brightness"].as<byte>());

                    this->dataToProcess->push_back(new LedDataDto(
                            ledDataJson["ledIndex"],
                            ledDataJson["toColor"][0],
                            ledDataJson["toColor"][1],
                            ledDataJson["toColor"][2],
                            ledDataJson["misc"]["brightness"]
                    ));
                }
            }

            Log.traceln("New dataToProcess count: %d", dataToProcess->size());
        }
    }
}

bool ReadLedTask::isValidLedDataJson(JsonObject ledDataJson) {
    bool isLedIndexValid = ledDataJson["ledIndex"].is<LedIndex>() &&
                           ledDataJson["ledIndex"] >= 0 &&
                           ledDataJson["ledIndex"] <= 12;
    if (!isLedIndexValid) {
        Log.error("LedIndex is invalid: %d", ledDataJson["ledIndex"].as<LedIndex>());
    }

    bool isToColorRValid = ledDataJson["toColor"][0].is<byte>();
    if (!isToColorRValid) {
        Log.error("toColor[R] is invalid: %d", ledDataJson["toColor"][0].as<LedIndex>());
    }

    bool isToColorGValid = ledDataJson["toColor"][1].is<byte>();
    if (!isToColorGValid) {
        Log.error("toColor[G] is invalid: %d", ledDataJson["toColor"][1].as<LedIndex>());
    }

    bool isToColorBValid = ledDataJson["toColor"][2].is<byte>();
    if (!isToColorBValid) {
        Log.error("toColor[B] is invalid: %d", ledDataJson["toColor"][2].as<LedIndex>());
    }

    bool isBrightnessValid = ledDataJson["misc"]["brightness"].is<byte>();
    if (!isBrightnessValid) {
        Log.error("brightness is invalid: %d", ledDataJson["misc"]["brightness"].as<LedIndex>());
    }

    Log.traceln("Validation results (LedIndex, r, g, b, brightness; 0 = invalid, 1 = valid): %b, %b, %b, %b, %b",
                isLedIndexValid, isToColorRValid, isToColorGValid, isToColorBValid, isBrightnessValid);

    return isLedIndexValid && isToColorRValid && isToColorGValid && isToColorBValid && isBrightnessValid;
}
