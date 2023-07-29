//
// Created by Igor Voronin on 25.07.23.
//

#ifndef DIALER_INPUTPROCESSORTASK_H
#define DIALER_INPUTPROCESSORTASK_H

#include <LinkedList.h>
#include "RawDataDto.h"
#include "logger/Logger.h"
#include "interfaces/ISchedulableDialTask.h"

class InputProcessorTask : public ISchedulableDialTask {
public:
    explicit InputProcessorTask(LinkedList<RawDataDto *> *messagesToProcess, Stream *serial);

    void onSetup() override;

    void onCallback() override;

private:
    static const char TERMINATOR = '\n';
    static const int BUFFER_SIZE = 2048;

    LinkedList<RawDataDto *> *messagesToProcess;
    Stream *serial;

    void processInputData(char readBuffer[BUFFER_SIZE], size_t dataSize);
};


#endif //DIALER_INPUTPROCESSORTASK_H
