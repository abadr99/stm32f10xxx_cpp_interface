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
#ifndef DEV_INC_HAL_BUZZER_H_
#define DEV_INC_HAL_BUZZER_H_

#include "mcal/Pin.h"

using namespace stm32::dev::mcal::pin;
namespace stm32 {
namespace dev {
namespace hal {
namespace buzzer {


/**
 * @enum BuzzerState
 * @brief Enumeration representing the state of the buzzer.
 * 
 * This enum defines the possible states of the buzzer, either On or Off.
 */
enum BuzzerState : uint8_t {
    kOn,  /**< Buzzer is On */
    kOff  /**< Buzzer is Off */
};

/**
 * @class Buzzer
 * @brief Class representing a Buzzer controller.
 * 
 * This template class allows controlling a buzzer, including turning it on, off, and toggling its state.
 * It also allows querying the current state of the buzzer.
 * 
 * @tparam CT The connection type for the buzzer, typically defined as stm32::type::ConnectionType.
 */
template<stm32::type::ConnectionType CT>
class Buzzer {
 public:
    /**
     * @brief Constructs a Buzzer object.
     * 
     * @param buzzerPin The pin connected to the buzzer.
     */
    explicit Buzzer(const Pin& buzzerPin);

    /**
     * @brief Turns the buzzer on.
     */
    void TurnOn();

    /**
     * @brief Turns the buzzer off.
     */
    void TurnOff();

    /**
     * @brief Toggles the current state of the buzzer.
     * 
     * If the buzzer is currently on, it will be turned off. If it is off, it will be turned on.
     */
    void Toggle();

    /**
     * @brief Gets the current state of the buzzer.
     * 
     * @return BuzzerState The current state of the buzzer (either kOn or kOff).
     */
    BuzzerState GetBuzzerState();

 private:
    BuzzerState buzzerState_;  /**< Holds the current state of the buzzer */
    Pin buzzerPin_;            /**< The pin connected to the buzzer */
};

}  // namespace buzzer
}  // namespace hal
}  // namespace dev
}  // namespace stm32
#endif  // DEV_INC_HAL_BUZZER_H_
