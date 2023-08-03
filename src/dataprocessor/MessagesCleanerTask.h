#ifndef DIALER_MESSAGESCLEANERTASK_H
#define DIALER_MESSAGESCLEANERTASK_H

#include <LinkedList.h>
#include "logger/Logger.h"
#include "inputProcessor/InputMessageDto.h"
#include "interfaces/ISchedulableDialTask.h"
#include "interfaces/IMessageConsumer.h"

/**
 * @class   MessagesCleanerTask
 * @brief   Task to handle the cleanup of input messages.
 *
 * This class is a ISchedulableDialTask, that handles the cleanup of the messages the InputProcessorTask produces.
 * <p>In particular it deletes all messages, that are invalid.
 * See InputMessageDto for more details on when a message is valid.</p>
 *
 * @author  Igor Voronin
 * @date    28.07.2023
 */
class MessagesCleanerTask : public ISchedulableDialTask, private IMessageConsumer {
public:
    /**
     * @brief Constructor.
     *
     * @param messagesToProcess (LinkedList<InputMessageDto *>*) reference to the list containing the messages to be processed
     */
    explicit MessagesCleanerTask(LinkedList<InputMessageDto *> &messagesToProcess);

    void onCallback() override;

private:
    void useData(JsonVariantConst jsonData) override { /* data is not used, but only processed */ };

    bool isValidData(JsonVariantConst jsonData) override { /* there is no data to validate */ return false; };
};


#endif //DIALER_MESSAGESCLEANERTASK_H
