#ifndef DIALER_MESSAGESCLEANERTASK_H
#define DIALER_MESSAGESCLEANERTASK_H

#include <LinkedList.h>
#include "logger/Logger.h"
#include "inputProcessor/InputMessageDto.h"
#include "interfaces/ISchedulableDialTask.h"

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
class MessagesCleanerTask : public ISchedulableDialTask {
public:
    /**
     * @brief Constructor.
     *
     * @param type              (const char*) short type name of the task
     * @param messagesToProcess (LinkedList<InputMessageDto *>*) pointer to the list containing the messages to be processed
     */
    explicit MessagesCleanerTask(const char *type, LinkedList<InputMessageDto *> *messagesToProcess);

    void onCallback() override;

private:
    /**
     * @brief Pointer to the list of messages to be processed.
     */
    LinkedList<InputMessageDto *> *messagesToProcess;
};


#endif //DIALER_MESSAGESCLEANERTASK_H
