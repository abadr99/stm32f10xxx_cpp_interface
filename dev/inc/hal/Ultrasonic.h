/**
 * @file Ultrasonic.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2025-03-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_INC_HAL_ULTRASONIC_H_
#define DEV_INC_HAL_ULTRASONIC_H_

using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::timer;

namespace stm32 {
namespace dev {
namespace hal {
namespace ultrasonic {
class Ultrasonic {
 public:
    /**
     * @brief Constructs an Ultrasonic object and initializes the ultrasonic pins and timer.
     *
     * @param triggerPin The pin used to trigger the ultrasonic sensor.
     * @param echoPin The pin used to receive the echo from the ultrasonic sensor.
     * @param timer The timer used for measuring time intervals.
     */
    Ultrasonic(const Pin& triggerPin, const Pin& echoPin, Timer *timer);

    /**
     * @brief Measures the distance using the ultrasonic sensor.
     *
     * @return The measured distance in centimeters.
     */
    float MeasureDistance();

 private:
    Pin triggerPin_;  /**< Pin used to trigger the ultrasonic sensor */
    Pin echoPin_;     /**< Pin used to receive the echo from the ultrasonic sensor */
    Timer *timer_;    /**< Timer used for measuring time intervals */

    void Trigger();
};
}   // namespace ultrasonic
}   // namespace hal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_INC_HAL_ULTRASONIC_H_
