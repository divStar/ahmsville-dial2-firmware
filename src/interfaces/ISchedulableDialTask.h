//
// Created by Igor Voronin on 29.07.23.
//

#ifndef DIALER_ISCHEDULABLEDIALTASK_H
#define DIALER_ISCHEDULABLEDIALTASK_H

#include <TaskSchedulerDeclarations.h>
#include "DialTask.h"

class ISchedulableDialTask : public Task, public DialTask {
public:
    explicit ISchedulableDialTask(const char* taskType) : DialTask(taskType) {};
};

#endif //DIALER_ISCHEDULABLEDIALTASK_H
