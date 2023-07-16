//
// Created by Igor Voronin on 17.06.23.
//

#ifndef DIALER_SHOWLEDTASK_H
#define DIALER_SHOWLEDTASK_H

#include "Vector.h"
#include "DialTask.h"
#include "LedDataDto.h"

class ShowLedTask : public DialTask {
public:
    explicit ShowLedTask(Vector<LedDataDto *> *dataToProcess);

    void onSetup() override;

    void onCallback() override;

private:
    void onUpdateLeds();

    Vector<LedDataDto *> *dataToProcess;
};

#endif //DIALER_SHOWLEDTASK_H
