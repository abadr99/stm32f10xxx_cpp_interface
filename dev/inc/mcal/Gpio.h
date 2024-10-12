/**
 * @file Gpio.h
 * @author
 * @brief
 * @version 0.1
 * @date 2024-03-16
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_INC_MCAL_GPIO_H_
#define DEV_INC_MCAL_GPIO_H_

#include "utils/Types.h"

namespace stm32 {
namespace dev {
namespace mcal {
namespace gpio {

/**
 * @brief Class to handle General-Purpose Input/Output (GPIO) operations.
 */
class Gpio {
 public:
  using Pin = stm32::dev::mcal::pin::Pin;             /**< Type alias for Pin class. */
  using Port = stm32::dev::mcal::pin::Port;           /**< Type alias for Port class. */
  using PinMode = stm32::dev::mcal::pin::PinMode;     /**< Type alias for PinMode enum. */
  using PinVal_t = uint8_t;                           /**< Type alias for pin value type. */

  /**
   * @brief Configures the given GPIO pin with all settings defined in the Pin class.
   * 
   * @param pin The Pin object containing the configuration details.
   */
  static void Set(const Pin& pin);

  /**
   * @brief Sets the mode (input, output, etc.) for the given GPIO pin.
   * 
   * @param pin The Pin object for which the mode needs to be set.
   * @param mode The desired PinMode for the pin.
   */
  static void SetPinMode(const Pin& pin, PinMode mode);

  /**
   * @brief Sets the voltage level (high/low) for the specified GPIO pin.
   * 
   * @param pin The Pin object for which the value needs to be set.
   * @param pinState The digital voltage level (high/low).
   */
  static void SetPinValue(const Pin& pin, stm32::type::DigitalVoltage pinState);

  /**
   * @brief Gets the current voltage level (high/low) of the specified GPIO pin.
   * 
   * @param pin The Pin object to read the value from.
   * @return PinVal_t The current voltage level of the pin (0 for low, 1 for high).
   */
  static PinVal_t GetPinValue(Pin pin);
};

}  // namespace gpio
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_INC_MCAL_GPIO_H_
