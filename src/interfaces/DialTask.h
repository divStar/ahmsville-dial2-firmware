//
// Created by Igor Voronin on 18.06.23.
//

#ifndef DIALER_DIALTASK_H
#define DIALER_DIALTASK_H

#include <TaskSchedulerDeclarations.h>

class DialTask {
public:
    explicit DialTask(const char *type);

    const char *getTaskType() const;

    virtual void onSetup() {};

    virtual void onCallback() = 0;

private:
    const char *taskType;
};

#endif //DIALER_DIALTASK_H
