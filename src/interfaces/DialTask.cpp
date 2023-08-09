#include "DialTask.h"

DialTask::DialTask(const char *type) : taskType(type) {}

const char *DialTask::getTaskType() const { return taskType; }
