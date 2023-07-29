//
// Created by Igor Voronin on 29.07.23.
//

#ifndef DIALER_ISCHEDULABLEDIALTASK_H
#define DIALER_ISCHEDULABLEDIALTASK_H

#include <TaskSchedulerDeclarations.h>
#include "IDialTask.h"

class ISchedulableDialTask: public Task, public virtual IDialTask {};

#endif //DIALER_ISCHEDULABLEDIALTASK_H
