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
#include "mcal/inc/Pin.h"
using namespace stm32::dev::mcal::pin;
namespace stm32 {
namespace dev {
namespace hal {
namespace buzzer {

enum ConnectionType : uint8_t {
    kForward_Bias,  // active high
    kReverse_Bias,  // active low
};

class Buzzer {
 public:
    Buzzer(const Pin buzzerPin, const ConnectionType connectionType);
    void TurnOn();
    void TurnOff();
    void Toggle();
 private:
    enum BuzzerState : uint8_t {kOn, kOff};
    BuzzerState buzzerState_;
    Pin buzzerPin_;
    ConnectionType connectionType_;
};
}  // namespace buzzer
}  // namespace hal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_HAL_INC_BUZZER_H_
