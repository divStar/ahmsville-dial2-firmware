//
// Created by Igor Voronin on 25.07.23.
//

#include "InputProcessorTask.h"

InputProcessorTask::InputProcessorTask(LinkedList<RawDataDto *> *messagesToProcess, Stream *serial)
        : messagesToProcess(messagesToProcess), serial(serial) {
    setInterval(0);
    setIterations(TASK_FOREVER);
}

void InputProcessorTask::onSetup() {}

void InputProcessorTask::onCallback() {
    if (serial->available()) {
        char readBuffer[BUFFER_SIZE];
        size_t dataSize = serial->readBytesUntil(TERMINATOR, readBuffer, BUFFER_SIZE);
        if (dataSize > 0) {
            processInputData(readBuffer, dataSize);
        }
    }
}

void InputProcessorTask::processInputData(char readBuffer[BUFFER_SIZE], size_t dataSize) {
    char *dataBuffer = new char[dataSize + 1];
    strncpy(dataBuffer, readBuffer, dataSize);
    // null-terminate the dataBuffer
    dataBuffer[dataSize] = '\0';

    messagesToProcess->add(new RawDataDto(dataBuffer, millis()));

    // delete dataBuffer
    delete[](dataBuffer);

    // clear readBuffer
    memset(readBuffer, 0, BUFFER_SIZE);
}
