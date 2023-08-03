#include "MessagesCleanerTask.h"

MessagesCleanerTask::MessagesCleanerTask(const char *type, LinkedList<InputMessageDto *> *messagesToProcess)
        : ISchedulableDialTask("messagescleaner"), messagesToProcess(messagesToProcess) {
    setInterval(0);
    setIterations(TASK_FOREVER);
}

void MessagesCleanerTask::onCallback() {
    for (int rawDataDtoIndex = messagesToProcess->size() - 1; rawDataDtoIndex >= 0; --rawDataDtoIndex) {
        InputMessageDto *rawDataDto = messagesToProcess->get(rawDataDtoIndex);
        if (!rawDataDto->isValid()) {
            delete (messagesToProcess->remove(rawDataDtoIndex));
        }
    }
}
