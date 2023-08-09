#include "MacroKeyTask.h"

MacroKeyTask::MacroKeyTask(IMacroKeys &macroKeys) : ISchedulableDialTask("macrokey"), macroKeys(macroKeys) {
  setInterval(0);
  setIterations(TASK_FOREVER);
}

void MacroKeyTask::onSetup() { macroKeys.initializeMacroKeys(); }
