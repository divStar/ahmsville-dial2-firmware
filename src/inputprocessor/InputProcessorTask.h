#ifndef DIALER_INPUTPROCESSORTASK_H
#define DIALER_INPUTPROCESSORTASK_H

#include <LinkedList.h>
#include "InputMessageDto.h"
#include "interfaces/ISchedulableDialTask.h"
#include "interfaces/ISerialPortUser.h"
#include "logger/Logger.h"

/**
 * @class   InputProcessorTask
 * @brief   Task to handle the incoming messages from the Serial port.
 *
 * This class is a ISchedulableDialTask, that handles the incoming messages from
 * the Serial port.
 *
 * @author  Igor Voronin
 * @date    29.07.2023
 */
class InputProcessorTask : public ISchedulableDialTask, private ISerialPortUser {
public:
  /**
   * @brief Constructor.
   *
   * @param messagesToProcess (LinkedList<InputMessageDto *>*) reference to the
   * list to add messages to
   */
  explicit InputProcessorTask(LinkedList<InputMessageDto *> &messagesToProcess);

  void onCallback() override;

private:
  /**
   * @brief Terminating symbol used to to recognize the end of a message.
   */
  static const char TERMINATOR = '\n';

  /**
   * @brief Buffer size of the JSON output.
   */
  static const int BUFFER_SIZE = 2048;

  /**
   * @brief Process the input from the given Serial port.
   *
   * This method processes the input from the given Serial port and places it in
   * the <code>InputProcessorTask::messagesToProcess</code> list.
   *
   * @param readBuffer    (char [BUFFER_SIZE]) buffer to process
   * @param dataSize      (size_t) size of the data inside the buffer
   */
  void processInputData(char readBuffer[BUFFER_SIZE], size_t dataSize);

  /**
   * @brief reference to the list of messages to be processed.
   */
  LinkedList<InputMessageDto *> &messagesToProcess;
};

#endif // DIALER_INPUTPROCESSORTASK_H
