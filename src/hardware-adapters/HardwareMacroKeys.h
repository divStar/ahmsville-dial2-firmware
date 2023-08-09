#ifndef DIALER_HARDWAREMACROKEYS_H
#define DIALER_HARDWAREMACROKEYS_H

#include "interfaces/sensors/IMacroKeys.h"
#include "macrokey/MacroKey.h"

/**
 * @class   HardwareMacroKeys
 * @brief   The actual hardware implementation of the macro key sensors adapter
 * used by the application.
 *
 * @author  Igor Voronin
 * @date    06.08.2023
 */
class HardwareMacroKeys : public IMacroKeys {
public:
  /**
   * @brief Constructor.
   *
   * @param taskType (const char*) name of the task responsible for the macro
   * keys
   */
  explicit HardwareMacroKeys(const char *taskType);

  void initializeMacroKeys() override;

private:
  /**
   * @brief Name of the task responsible for the macro keys.
   */
  const char *taskType;

  /**
   * @brief Array of macro-keys.
   */
  static MacroKey keys[];
};

#endif // DIALER_HARDWAREMACROKEYS_H
