#ifndef DIALER_MACROKEYTASK_H
#define DIALER_MACROKEYTASK_H

#include "MacroKey.h"
#include "interfaces/ISchedulableDialTask.h"
#include "interfaces/sensors/IMacroKeys.h"

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
  explicit MacroKeyTask(IMacroKeys &macroKeys);

  void onSetup() override;

private:
  IMacroKeys &macroKeys;
};

#endif // DIALER_MACROKEYTASK_H
