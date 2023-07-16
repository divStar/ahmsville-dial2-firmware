//
// Created by Igor Voronin on 17.06.23.
//
#include "FastLED.h"
#include "ShowLedTask.h"
#include "logger/Logger.h"

#define LED_TYPE    WS2812B
#define DATA_PIN    3
#define COLOR_ORDER GRB
#define NUM_LEDS    13
#define BRIGHTNESS  96

CRGB leds[NUM_LEDS];
CRGB defaultColor = CRGB::Black;

ShowLedTask::ShowLedTask(Vector<LedDataDto *> *dataToProcess) : dataToProcess(dataToProcess) {}

void ShowLedTask::onSetup() {
    CFastLED::addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
}

void ShowLedTask::onCallback() {
    bool updateLeds = !dataToProcess->empty();
    if (updateLeds) {
        onUpdateLeds();
    }
}

void ShowLedTask::onUpdateLeds() {
    Log.trace("Processing new LED data: ");

    for (auto data: *dataToProcess) {
        Log.trace("%d, ", data->getIndex());
        leds[data->getIndex()].setRGB(data->getR(), data->getG(), data->getB());
        leds[data->getIndex()].maximizeBrightness(data->getBrightness());
    }
    Log.traceln("DONE!");

    // update LEDs
    Log.traceln("New data was processed");
    FastLED.show();
    Log.traceln("LEDs were updated");

    // clear dataToProcess since it has been processed already
    dataToProcess->clear();
    Log.traceln("dataToProcess array was cleared");
}
