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
#include "mcal/stm32f103xx.h"

namespace stm32 {
namespace dev {
namespace mcal {
namespace gpio {

/**
 * @brief Class to handle General-Purpose Input/Output (GPIO) operations.
 */
class Gpio {
 public:
  using Pin = stm32::dev::mcal::pin::Pin;
  using Port = stm32::dev::mcal::pin::Port;
  using PinMode = stm32::dev::mcal::pin::PinMode;
  using GpioRegDef = stm32::registers::gpio::GpioRegDef;
  using PinVal_t = uint8_t;
    // As Gpio class is used to deal with general purpose IO and all pin's 
  // configurations are abstracted in Pin class so we can use Set() method 
  // to set all gpio configurations
  static void Init();
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
 private:
  static volatile  GpioRegDef * GPIOx[3];
};

}  // namespace gpio
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_INC_MCAL_GPIO_H_
