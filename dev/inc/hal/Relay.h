/**
 * @file Relay.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-07-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_INC_HAL_RELAY_H_
#define DEV_INC_HAL_RELAY_H_

using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;

namespace stm32 {
namespace dev {
namespace hal {
namespace relay {
class Relay {
 public:
    explicit Relay(Pin relayPin);
    void Control(stm32::type::DigitalVoltage state);
 private:
    Pin relayPin;
};
}   //  namespace relay
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  // DEV_INC_HAL_RELAY_H_
