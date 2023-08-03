#ifndef DIALER_MACROKEYTASK_H
#define DIALER_MACROKEYTASK_H

#include "MacroKey.h"
#include "interfaces/ISchedulableDialTask.h"

/**
 * @class   MacroKeyTask
 * @brief   Task to handle all macro-keys.
 *
 * This class is a ISchedulableDialTask, that handles all macro-keys.
 *
 * <p>The macro-keys can be pressed and released individually and combined.</p>
 *
 * @author  Igor Voronin
 * @date    16.07.2023
 */
class MacroKeyTask : public ISchedulableDialTask {
public:
    /**
     * @brief Constructor.
     */
    MacroKeyTask();

    void onSetup() override;

private:
    /**
     * @brief Array of macro-keys.
     */
    static MacroKey keys[];

    /**
     * @brief This function initializes all macro-keys.
     */
    static void initializeKeys();
};


#endif //DIALER_MACROKEYTASK_H
