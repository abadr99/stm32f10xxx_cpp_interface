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
/**
 * @brief Class for controlling a relay via a GPIO pin.
 * 
 * This class provides an interface to control a relay by setting its corresponding GPIO pin 
 * to a high or low digital voltage state.
 */
class Relay {
 public:
    /**
     * @brief Constructs a Relay control object.
     * 
     * @param relayPin The GPIO pin connected to the relay.
     */
    explicit Relay(const Pin& relayPin);

    /**
     * @brief Controls the relay by setting the voltage state of the GPIO pin.
     * 
     * @param state The desired voltage state to control the relay (high or low).
     */
    void Control(stm32::type::DigitalVoltage state);

 private:
    Pin relayPin;   /**< The GPIO pin used to control the relay. */
};
}   //  namespace relay
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  // DEV_INC_HAL_RELAY_H_
