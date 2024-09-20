/**
 * @file Buzzer.h
 * @author
 * @brief
 * @version 0.1
 * @date 2024-07-7
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_BUZZER_H_
#define DEV_HAL_INC_BUZZER_H_

#include "Pin.h"

using namespace stm32::dev::mcal::pin;
namespace stm32 {
namespace dev {
namespace hal {
namespace buzzer {


enum BuzzerState : uint8_t {
    kOn, kOff
};

template<stm32::type::ConnectionType CT>
class Buzzer {
 public:
    explicit Buzzer(const Pin& buzzerPin);
    void TurnOn();
    void TurnOff();
    void Toggle();
    BuzzerState GetBuzzerState();
 private:
    BuzzerState buzzerState_;
    Pin buzzerPin_;
};
}  // namespace buzzer
}  // namespace hal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_HAL_INC_BUZZER_H_
