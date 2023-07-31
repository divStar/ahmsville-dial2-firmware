//
// Created by Igor Voronin on 31.07.23.
//
#include "DialTask.h"

DialTask::DialTask(const char *type)
        : taskType(type) {}

const char *DialTask::getTaskType() const {
    return taskType;
}

