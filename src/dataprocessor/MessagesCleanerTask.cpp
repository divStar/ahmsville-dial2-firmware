//
// Created by Igor Voronin on 25.07.23.
//

#include "MessagesCleanerTask.h"

MessagesCleanerTask::MessagesCleanerTask(LinkedList<RawDataDto *> *messagesToProcess)
        : messagesToProcess(messagesToProcess) {
    setInterval(0);
    setIterations(TASK_FOREVER);
}

void MessagesCleanerTask::onSetup() {}

void MessagesCleanerTask::onCallback() {
    for (int rawDataDtoIndex = messagesToProcess->size() - 1; rawDataDtoIndex >= 0; --rawDataDtoIndex) {
        RawDataDto *rawDataDto = messagesToProcess->get(rawDataDtoIndex);
        if (!rawDataDto->isValid()) {
            delete(messagesToProcess->remove(rawDataDtoIndex));
        }
    }
}
