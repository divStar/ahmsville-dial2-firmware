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

    void onSetup() override;

    void onCallback() override;

private:
    static const auto SAMPLES = 255;
    static const auto PROXIMITY_THRESHOLD = 300;
    static const auto BUFFER_SIZE = 96;

    CapacitiveSensor sensor;

    void sendData(long sensorValue);
};


#endif //DIALER_CAPACITATIVETOUCHTASK_H
