#ifndef DIALER_DIALTASK_H
#define DIALER_DIALTASK_H

#include <TaskSchedulerDeclarations.h>

/**
 * @class   DialTask
 * @brief   Provides basic functions, that are used by every subclass of this class.
 *
 * This class should be used as an abstract class, that provides a task type and default functions, which every subclass
 * will override.
 *
 * <p>Since the functions <code>onSetup</code> and <code>onCallback</code> are virtual, yet defined,
 * subclasses <strong>should</strong> override them if they need to be invoked during <code>setup()</code> or
 * <code>loop()</code> of the main.h file.</p>
 *
 * @author  Igor Voronin
 * @date    31.07.2023
 */
class DialTask {
public:
    /**
     * @brief Constructor.
     *
     * @param type  (const char*) name of the task type (e.g. "haptic" or "led")
     */
    explicit DialTask(const char *type);

    /**
     * @return (const char*) name of the task type (e.g. "haptic" or "led")
     */
    const char *getTaskType() const;

    /**
     * @brief Function, which usually runs in the setup() function of the main.h file.
     *
     * <p>The purpose of this function is to set up whatever task is supposed to run.</p>
     * <p><em>Implementing this function is <u>optional</u> since some tasks do not need to be set up first.</em></p>
     */
    virtual void onSetup() {};

    /**
     * @brief Function, which usually runs in the loop() function of the main.h file.
     *
     * <p>The purpose of this function is to be called repeatedly each time a task is executed.</p>
     * <p><em>Implementing this function is <u>optional</u> since some tasks are interrupt-driven
     * and do not run within the loop() function.</em></p>
     */
    virtual void onCallback() {};

private:
    /**
     * @brief (const char*) name of the task type.
     */
    const char *taskType;
};

#endif //DIALER_DIALTASK_H
