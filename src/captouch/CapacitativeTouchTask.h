//
// Created by Igor Voronin on 29.07.23.
//

#ifndef DIALER_CAPACITATIVETOUCHTASK_H
#define DIALER_CAPACITATIVETOUCHTASK_H

#include <CapacitiveSensor.h>
#include "logger/Logger.h"
#include "interfaces/ISchedulableDialTask.h"

class CapacitativeTouchTask : public ISchedulableDialTask {
public:
    CapacitativeTouchTask();

    void onSetup() override;

    void onCallback() override;
private:
    CapacitiveSensor *sensor;
};


#endif //DIALER_CAPACITATIVETOUCHTASK_H
