//
// Created by Igor Voronin on 29.07.23.
//

#ifndef DIALER_CAPACITATIVETOUCHTASK_H
#define DIALER_CAPACITATIVETOUCHTASK_H

#include <CapacitiveSensor.h>
#include <ArduinoJson.h>
#include "TapTypeEnum.h"
#include "logger/Logger.h"
#include "interfaces/ISchedulableDialTask.h"

class CapacitativeTouchTask : public ISchedulableDialTask {
public:
    CapacitativeTouchTask(byte sendingPin, byte receivingPin);

    ~CapacitativeTouchTask() override;

    void onSetup() override;

    void onCallback() override;

private:
    static const auto SAMPLES = 80;
    static const auto TIME_THRESHOLD = 75;  // milliseconds
    static const auto DEFAULT_PROXIMITY_THRESHOLD = 180;
    static const auto DEFAULT_SLIGHT_TAP_THRESHOLD = 280;
    static const auto DEFAULT_TAP_THRESHOLD = 450;
    static const auto DEFAULT_STRONG_TAP_THRESHOLD = 650;
    static const auto DEFAULT_MAX_TAP_THRESHOLD = 750;
    static const auto MAX_STATES = 5;
    static const auto BUFFER_SIZE = 2048;

    CapacitiveSensor sensor;
    TapTypeEnum tapTypes[MAX_STATES];
    TapTypeEnum *lastTap = nullptr;
    unsigned long touchStart = 0;

    void readValues();
    static void sendData(int threshold, long sensorValue);
};


#endif //DIALER_CAPACITATIVETOUCHTASK_H
