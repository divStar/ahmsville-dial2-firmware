#ifndef MACROKEY_H
#define MACROKEY_H

#include "interfaces/ISerialPortUser.h"

/**
 * @class   MacroKey
 * @brief   Class to handle a single macro-key.
 *
 * This class handles a single macro-key and sends the state upon interrupt.
 *
 * @author  Igor Voronin
 * @date    16.07.2023
 */
class MacroKey : private ISerialPortUser {
public:
    /**
     * @brief Constructor.
     *
     * @param keyId     (int) the ID of the key
     * @param pin       (int) number of the pin of this macro-key
     */
    explicit MacroKey(int keyId, int pin);

    /**
     * @brief Returns the set pin.
     *
     * @return (int) number of the pin
     */
    [[nodiscard]] int getPin() const;

    /**
     * @brief Function, which is called upon state change via interrupt.
     */
    void onChangeState();

    /**
     * @brief Sets the name of the type of this macro-key.
     *
     * @param type (const char*) name of the type of this macro-key
     */
    void setType(const char *type);

private:
    /**
     * @brief Buffer size of the JSON output.
     */
    static const int BUFFER_SIZE = 256;
    /**
     * @brief Default debounce delay for the macro-key.
     */
    static const unsigned long DEBOUNCE_DELAY = 100;

    /**
     * @brief ID of the macro-key.
     */
    int keyId;
    /**
     * @brief Number of the pin of the macro-key.
     */
    int pin;
    /**
     * @brief Rise time (when the very first press has been registered).
     */
    volatile unsigned long riseTime;
    /**
     * @brief Fall time (when the very last press has been registered).
     */
    volatile unsigned long fallTime;
    /**
     * @brief Last time an interrupt occured.
     */
    volatile unsigned long lastInterrupttime;

    /**
     * @brief Name of the type of the macro-key.
     */
    const char *type;
};

#endif
