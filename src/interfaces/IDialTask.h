//
// Created by Igor Voronin on 18.06.23.
//

#ifndef DIALER_IDIALTASK_H
#define DIALER_IDIALTASK_H

#include <TaskSchedulerDeclarations.h>

class IDialTask {
public:
    virtual void onSetup() {};

    virtual void onCallback() = 0;
};

#endif //DIALER_IDIALTASK_H
