//
// Created by Igor Voronin on 25.07.23.
//

#ifndef DIALER_MESSAGESCLEANERTASK_H
#define DIALER_MESSAGESCLEANERTASK_H

#include <LinkedList.h>
#include "logger/Logger.h"
#include "inputProcessor/RawDataDto.h"
#include "interfaces/ISchedulableDialTask.h"

class MessagesCleanerTask : public ISchedulableDialTask {
public:
    explicit MessagesCleanerTask(const char *type, LinkedList<RawDataDto *> *messagesToProcess);

    void onSetup() override;

    void onCallback() override;

private:
    LinkedList<RawDataDto *> *messagesToProcess;
};


#endif //DIALER_MESSAGESCLEANERTASK_H
