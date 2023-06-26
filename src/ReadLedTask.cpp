//
// Created by Igor Voronin on 18.06.23.
//
#include "ReadLedTask.h"

const int BUFFER_SIZE = 2048;
const size_t MAX_JSON_ARRAY_CAPACITY = JSON_ARRAY_SIZE(13);

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
            SerialUSB.println((String)"IN " + size + " character(s): " + String(buffer, size));

            StaticJsonDocument<BUFFER_SIZE> jsonDoc;
            DeserializationError error = deserializeJson(jsonDoc, buffer, BUFFER_SIZE,
                                                         DeserializationOption::Filter(filterDoc));
            if (error) {
                SerialUSB.println((String) "deserializeJson() failed: " + error.c_str());
                return;
            }

            JsonArray ledDataJsonArray = jsonDoc.as<JsonArray>();
            SerialUSB.println((String) "Parsed " + ledDataJsonArray.size() + " LedDataDso objects");

            for (JsonObject ledDataJson: ledDataJsonArray) {
                if (isValidLedDataJson(ledDataJson)) {
                    SerialUSB.println((String) "Adding LedDataDto for LED "
                            + ledDataJson["ledIndex"].as<LedIndex>() + " with RGB("
                            + ledDataJson["toColor"][0].as<byte>() + ", "
                            + ledDataJson["toColor"][1].as<byte>() + ", "
                            + ledDataJson["toColor"][2].as<byte>() + ") and brightness "
                            + ledDataJson["misc"]["brightness"].as<byte>()
                    );

                    this->dataToProcess->push_back(new LedDataDto(
                            ledDataJson["ledIndex"],
                            ledDataJson["toColor"][0],
                            ledDataJson["toColor"][1],
                            ledDataJson["toColor"][2],
                            ledDataJson["misc"]["brightness"]
                    ));
                }
            }

            SerialUSB.println((String) "New dataToProcess count: " + dataToProcess->size());
        }
    }
}

bool ReadLedTask::isValidLedDataJson(JsonObject ledDataJson) {
    bool isLedIndexValid = ledDataJson["ledIndex"].is<LedIndex>() &&
                           ledDataJson["ledIndex"] >= 0 &&
                           ledDataJson["ledIndex"] <= 12;
    if (!isLedIndexValid) {
        SerialUSB.println((String) "LedIndex is invalid (" + ledDataJson["ledIndex"].as<LedIndex>() + ")!");
    }

    bool isToColorRValid = ledDataJson["toColor"][0].is<byte>();
    if (!isToColorRValid) {
        SerialUSB.println((String) "toColor[R] is invalid (" + ledDataJson["toColor"][0].as<byte>() + ")!");
    }

    bool isToColorGValid = ledDataJson["toColor"][1].is<byte>();
    if (!isToColorGValid) {
        SerialUSB.println((String) "toColor[G] is invalid (" + ledDataJson["toColor"][1].as<byte>() + ")!");
    }

    bool isToColorBValid = ledDataJson["toColor"][2].is<byte>();
    if (!isToColorBValid) {
        SerialUSB.println((String) "toColor[B] is invalid (" + ledDataJson["toColor"][2].as<byte>() + ")!");
    }

    bool isBrightnessValid = ledDataJson["misc"]["brightness"].is<byte>();
    if (!isBrightnessValid) {
        SerialUSB.println((String) "brightness is invalid (" + ledDataJson["misc"]["brightness"].as<byte>() + ")!");
    }

    SerialUSB.println((String) "Validation results (LedIndex, r, g, b, brightness): "
            + isLedIndexValid + ", "
            + isToColorRValid + ", " + isToColorGValid + ", " + isToColorBValid + ", "
            + isBrightnessValid);

    return isLedIndexValid && isToColorRValid && isToColorGValid && isToColorBValid && isBrightnessValid;
}
