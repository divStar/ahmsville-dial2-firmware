//
// Created by Igor Voronin on 25.07.23.
//

#ifndef DIALER_HAPTICTASK_H
#define DIALER_HAPTICTASK_H

#include <FastLED.h>
#include <LinkedList.h>
#include "ArduinoJson.h"
#include "interfaces/IInputConsumer.h"
#include "inputprocessor/RawDataDto.h"
#include "logger/Logger.h"
#include "interfaces/ISchedulableDialTask.h"

class HapticTask : public ISchedulableDialTask, private IInputConsumer {
public:
    explicit HapticTask(LinkedList<RawDataDto *> *messagesToProcess);

    void onSetup() override;

    void onCallback() override;

private:
    static const int BUFFER_SIZE = 64;
    static const int HAPTIC_PIN = 4;

    StaticJsonDocument<64> filterDoc; // this JSON describes what to filter for
    LinkedList<RawDataDto *> *messagesToProcess;

    void applyData(JsonVariantConst jsonData) override;

    bool isValidData(JsonVariantConst jsonData) override;
};

#endif //DIALER_HAPTICTASK_H
