/**
 * @file Led.h
 * @author
 * @brief
 * @version 0.1
 * @date 2024-04-30
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_LED_H_
#define DEV_HAL_INC_LED_H_

using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;

namespace stm32 {
namespace dev {
namespace hal {
namespace led {

template<stm32::utils::types::ConnectionType CT>
class Led {
 public:
  explicit Led(Pin LedPin);
  void TurnOn();
  void TurnOff();
  void Toggle();
 private:
  enum State_t { kTurnedOn, kTurnedOff };
  Pin LedPin;
  State_t LedState;
};

}  // namespace led
}  // namespace hal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_HAL_INC_LED_H_