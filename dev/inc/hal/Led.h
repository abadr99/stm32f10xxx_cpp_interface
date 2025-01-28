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
#ifndef DEV_INC_HAL_LED_H_
#define DEV_INC_HAL_LED_H_

using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;

namespace stm32 {
namespace dev {
namespace hal {
namespace led {

/**
 * @brief Template class to control an LED.
 * 
 * This class provides methods to turn the LED on, off, or toggle its state.
 * 
 * @tparam CT The connection type of the LED, which could specify if it's 
 *            connected to ground (common anode) or VCC (common cathode).
 */
template<stm32::type::ConnectionType CT>
class Led {
 public:
    /**
     * @brief Constructs an LED object for controlling the specified pin.
     * 
     * @param LedPin The pin where the LED is connected.
     */
    explicit Led(const Pin& LedPin);

    /**
     * @brief Turns the LED on.
     */
    void TurnOn();

    /**
     * @brief Turns the LED off.
     */
    void TurnOff();

    /**
     * @brief Toggles the state of the LED (on/off).
     */
    void Toggle();

 private:
    /**
     * @brief Enum representing the current state of the LED.
     */
    enum State_t { 
        kTurnedOn,      /**< LED is on */
        kTurnedOff      /**< LED is off */
    };

    Pin LedPin;         /**< Pin controlling the LED */
    State_t LedState;   /**< Current state of the LED */
};

}  // namespace led
}  // namespace hal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_INC_HAL_LED_H_
