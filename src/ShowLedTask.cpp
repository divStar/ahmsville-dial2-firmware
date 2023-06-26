//
// Created by Igor Voronin on 17.06.23.
//
#include <FastLED.h>
#include "ShowLedTask.h"

#define LED_TYPE    WS2812B
#define DATA_PIN    3
#define COLOR_ORDER GRB
#define NUM_LEDS    13
#define BRIGHTNESS  96

CRGB leds[NUM_LEDS];
CRGB defaultColor = CRGB::Black;

ShowLedTask::ShowLedTask(Vector<LedDataDto*>* dataToProcess): dataToProcess(dataToProcess) {}

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
    SerialUSB.print("Processing new data for LED ");

    int i = 0;
    for (auto it = dataToProcess->begin(); it != dataToProcess->end(); ++it, ++i) {
        LedDataDto* data = *it;
        SerialUSB.print((String) data->getIndex() + ", ");
        leds[data->getIndex()].setRGB(data->getR(), data->getG(), data->getB());
        leds[data->getIndex()].maximizeBrightness(data->getBrightness());
    }
    SerialUSB.println("DONE!");

    // update LEDs
    SerialUSB.println("New data was processed");
    FastLED.show();
    SerialUSB.println("LEDs were updated");

    // clear dataToProcess since it has been processed already
    dataToProcess->clear();
    SerialUSB.println("dataToProcess array was cleared");
}
