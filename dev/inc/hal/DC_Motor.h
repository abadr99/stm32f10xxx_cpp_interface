/**
 * @file DC_Motor.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-07-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_INC_HAL_DC_MOTOR_H_
#define DEV_INC_HAL_DC_MOTOR_H_

using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;

namespace stm32 {
namespace dev {
namespace hal {
namespace dc_motor {
/**
 * @class DC_Motor
 * @brief Class for controlling a DC motor.
 * 
 * This class allows the control of a DC motor by managing two control pins. 
 * It provides methods to rotate the motor in clockwise and anti-clockwise directions, 
 * as well as to stop the motor.
 */
class DC_Motor {
 public:
    /**
     * @brief Constructs a DC_Motor object.
     * 
     * @param pin1 First pin controlling the DC motor direction.
     * @param pin2 Second pin controlling the DC motor direction.
     */
    DC_Motor(const Pin& pin1, const Pin& pin2);

    /**
     * @brief Rotates the DC motor in a clockwise direction.
     */
    void ClockWise();

    /**
     * @brief Rotates the DC motor in an anti-clockwise direction.
     */
    void AntiClockWise();

    /**
     * @brief Stops the DC motor.
     */
    void Stop();

 private:
    Pin pin1; /**< First control pin for the DC motor */
    Pin pin2; /**< Second control pin for the DC motor */
};
}   //  namespace dc_motor
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //  DEV_INC_HAL_DC_MOTOR_H_ 
