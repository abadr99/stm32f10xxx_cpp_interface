/**
 * @file Ultrasonic.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2025-03-28
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
/**
 * @class Ultrasonic
 * @brief Class for controlling an ultrasonic sensor.
 * 
 * This class allows the control of an ultrasonic sensor by managing a trigger pin and a timer.
 * It provides methods to initialize the sensor, send a trigger pulse, and measure the distance.
 */
class Ultrasonic {
 public:
    Ultrasonic(const Pin& trigger, const Pin& echo, const Timer& timer);
    float GetDistance();
 private:
    Pin trigger;
    Pin echo;
    Timer timer;
};  //  class Ultrasonic    
}   //  namespace ultrasonic
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32

#endif  // DEV_INC_HAL_ULTRASONIC_H_
