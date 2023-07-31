//
// Created by Igor Voronin on 17.06.23.
//

#ifndef DIALER_LEDTASK_H
#define DIALER_LEDTASK_H

#include <FastLED.h>
#include <LinkedList.h>
#include "ArduinoJson.h"
#include "LedIndexEnum.h"
#include "interfaces/IConsumer.h"
#include "inputprocessor/RawDataDto.h"
#include "logger/Logger.h"
#include "interfaces/ISchedulableDialTask.h"
#include "error/ErrorSerializer.h"

class LedTask : public ISchedulableDialTask, private IConsumer {
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

    void sendValidationError(const char* errorNumber, const char* message, byte data);
};

#endif //DIALER_LEDTASK_H
