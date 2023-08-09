/**
 * @class   KnobTask
 * @brief   Enumeration of named LEDs.
 *
 * This enumeration contains all named LEDs and its purpose is to make it easier
 * to understand which LED is which.
 *
 * <p><em>Note:</em><ul>
 * <li>For <strong><code>BASE_LED#</code></strong> turn your device
 * <strong>upside down</strong> with the USB-C port at the top.
 * <code>BASE_LED1</code> is the LED next to the USB-C port on the left and the
 * numbering follows the indices counter-clockwise.</li> <li>For
 * <strong><code>MK_LED#</code></strong> let the macro-keys face you from left
 * to right while the device is standing as intended. <code>MK_LED1</code> is
 * the LED under the left-most key and the numbering follows the indices from
 * left to right.</li>
 * </ul></p>
 *
 * @author  Igor Voronin
 * @date    25.06.2023
 */
enum LedIndexEnum {
  TOP_LED = 0,
  BASE_LED1 = 1,
  BASE_LED2 = 2,
  BASE_LED3 = 3,
  BASE_LED4 = 4,
  BASE_LED5 = 5,
  BASE_LED6 = 6,
  BASE_LED7 = 7,
  MK_LED1 = 8,
  MK_LED2 = 9,
  MK_LED3 = 10,
  MK_LED4 = 11,
  MK_LED5 = 12
};