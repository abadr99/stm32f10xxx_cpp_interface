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
  static void SetPinMode(const Pin& pin, PinMode mode);
  static void SetPinValue(const Pin& pin, stm32::type::DigitalVoltage pinState);
  static PinVal_t GetPinValue(Pin pin);
 private:
  static volatile  GpioRegDef * GPIOx[3];
};

}  // namespace gpio
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_INC_MCAL_GPIO_H_
