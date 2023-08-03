#ifndef DIALER_ISCHEDULABLEDIALTASK_H
#define DIALER_ISCHEDULABLEDIALTASK_H

#include <TaskSchedulerDeclarations.h>
#include "DialTask.h"

/**
 * @class   ISchedulableDialTask
 * @brief   Inherits from Task and DialTask to provide one class for Tasks to implement.
 *
 * This abstract class inherits form Task and DialTask and thereby allows its subclasses to implement a single class.
 *
 * @author  Igor Voronin
 * @date    27.07.2023
 */
class ISchedulableDialTask : public Task, public DialTask {
public:
    /**
     * @brief Constructor.
     *
     * @param taskType  (const char*) name of the task type (e.g. "haptic" or "led")
     */
    explicit ISchedulableDialTask(const char* taskType) : DialTask(taskType) {};
};

#endif //DIALER_ISCHEDULABLEDIALTASK_H
