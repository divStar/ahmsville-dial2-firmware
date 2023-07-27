//
// Created by Igor Voronin on 25.07.23.
//

#ifndef DIALER_MESSAGESCLEANERTASK_H
#define DIALER_MESSAGESCLEANERTASK_H

#include <LinkedList.h>
#include "interfaces/IDialTask.h"
#include "logger/Logger.h"
#include "inputProcessor/RawDataDto.h"

class MessagesCleanerTask : public IDialTask {
public:
    explicit MessagesCleanerTask(LinkedList<RawDataDto *> *messagesToProcess);

    void onSetup() override;

    void onCallback() override;

private:
    LinkedList<RawDataDto *> *messagesToProcess;
};


#endif //DIALER_MESSAGESCLEANERTASK_H
