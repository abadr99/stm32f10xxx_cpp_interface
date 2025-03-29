/**
 * @file Ultrasonic.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2025-03-28
 *
 * @copyright Copyright (c) 2025
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
 * @struct UltrasonicConfig
 * @brief Configuration structure for the ultrasonic sensor.
 * 
 * This structure contains the pin configuration for the trigger and echo pins of the ultrasonic sensor.
 */
struct UltrasonicConfig {
    Pin trigger;  /**< Trigger pin for the ultrasonic sensor */
    Pin echo;     /**< Echo pin for the ultrasonic sensor */
};
/**
 * @class Ultrasonic
 * @brief Class for controlling an ultrasonic sensor.
 * 
 * This class allows the control of an ultrasonic sensor by managing a trigger pin and a timer.
 * It provides methods to initialize the sensor, send a trigger pulse, and measure the distance.
 */
class Ultrasonic {
 public:
   /**
    * @brief Constructs an Ultrasonic sensor object.
    * @param config Configuration structure containing the trigger and echo pins.
    * @param timer Reference to a Timer object for measuring the pulse duration.
    */
    Ultrasonic(const UltrasonicConfig& config, Timer *timer);
    /**
    * @brief Measures and returns the distance to an object.
    * @return Distance in centimeters.
    */
    uint32_t GetDistance();
    
 private:
    const UltrasonicConfig& config_;  /**< Reference to the ultrasonic configuration */
    Timer *timer_;   /**< Reference to the timer used for echo measurement */
    /**
    * @brief Sends a trigger pulse to the ultrasonic sensor.
    * 
    * This method generates a 10 microsecond pulse on the trigger pin to initiate the ultrasonic measurement.
    */
    void Trigger();
    /**
    * @brief Measures the duration of the echo pulse.
    * @return Echo pulse duration in timer ticks.
    */
    uint32_t MeasureEchoDuration();
};  //  class Ultrasonic    
}   //  namespace ultrasonic
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32

#endif  // DEV_INC_HAL_ULTRASONIC_H_
