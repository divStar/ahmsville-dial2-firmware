#ifndef DIALER_INPUTMESSAGEDTO_H
#define DIALER_INPUTMESSAGEDTO_H

#include "logger/Logger.h"

/**
 * @class   InputMessageDto
 * @brief   DTO (data transfer object) used to transport a message from the Serial port to a sensorAdapter task.
 *
 * This class describes a DTO (data transfer object), which is used to transport a message from the Serial port
 * to a sensorAdapter task. It also provides a function to make it possible to determine whether this object is still valid or
 * subject to be pruned by the MessagesCleanerTask.
 *
 * @author  Igor Voronin
 * @date    28.07.2023
 */
class InputMessageDto {
public:
    /**
     * @brief Constructor.
     *
     * @param rawInputData      (char*) raw input data
     * @param millisSinceBirth  (unsigned long) milliseconds since birth
     */
    InputMessageDto(char *rawInputData, unsigned long millisSinceBirth);

    /**
     * @brief Destructor.
     */
    ~InputMessageDto();

    /**
     * @brief Gets the raw input data (char*) for this message.
     *
     * @return (char*) raw input data
     */
    char *getRawInputData();

    /**
     * @brief Returns whether this message is still considered to be valid or not.
     *
     * @return (bool) <code>true</code> if this message is still valid, <code>false</code> otherwise
     */
    bool isValid() const;

    /**
     * @brief Sets the validity of this message.
     *
     * @param validity (bool) new validity of the given message
     */
    void setValid(bool validity);

private:
    /**
     * @brief Life span of this message.
     */
    static const unsigned long LIFE_SPAN = 200; // Milliseconds

    /**
     * @brief Raw input data for this message.
     */
    char *rawInputData;

    /**
     * @brief Milliseconds since the creation of this message.
     */
    unsigned long millisSinceBirth;

    /**
     * @brief Flag, that shows whether this message is still to be considered valid or not.
     */
    bool itemValid = true;
};

#endif //DIALER_INPUTMESSAGEDTO_H
