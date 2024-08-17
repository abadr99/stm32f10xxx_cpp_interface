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
#ifndef DEV_MCAL_INC_GPIO_H_
#define DEV_MCAL_INC_GPIO_H_

namespace stm32 {
namespace dev {
namespace mcal {
namespace gpio {

class Gpio {
 public:
  using Pin = stm32::dev::mcal::pin::Pin;
  using Port = stm32::dev::mcal::pin::Port;
  using PinMode = stm32::dev::mcal::pin::PinMode;
  using PinVal_t = uint8_t;
  enum State { kLow, kHigh };
  
  // As Gpio class is used to deal with general purpose IO and all pin's 
  // configurations are abstracted in Pin class so we can use Set() method 
  // to set all gpio configurations
  static void Set(const Pin& pin);
  static void SetPinMode(const Pin& pin, PinMode mode);
  static void SetPinValue(const Pin& pin, State pinState);
  static PinVal_t GetPinValue(Pin pin);
};

}  // namespace gpio
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_MCAL_INC_GPIO_H_
