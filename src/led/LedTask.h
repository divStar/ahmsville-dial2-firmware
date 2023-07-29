//
// Created by Igor Voronin on 17.06.23.
//

#ifndef DIALER_LEDTASK_H
#define DIALER_LEDTASK_H

#include <FastLED.h>
#include <LinkedList.h>
#include "ArduinoJson.h"
#include "LedIndex.h"
#include "interfaces/IInputConsumer.h"
#include "inputprocessor/RawDataDto.h"
#include "logger/Logger.h"
#include "interfaces/ISchedulableDialTask.h"

class LedTask : public ISchedulableDialTask, private IInputConsumer {
public:
    explicit LedTask(LinkedList<RawDataDto *> *messagesToProcess);

    void onSetup() override;

    void onCallback() override;

private:
    static const int BUFFER_SIZE = 2048;

    StaticJsonDocument<128> filterDoc; // this JSON describes what to filter for
    LinkedList<RawDataDto *> *messagesToProcess;

    void applyData(JsonVariantConst jsonData) override;

    bool isValidData(JsonVariantConst jsonData) override;
};

#endif //DIALER_LEDTASK_H
