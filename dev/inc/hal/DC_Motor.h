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
#ifndef DEV_HAL_INC_DC_MOTOR_H_
#define DEV_HAL_INC_DC_MOTOR_H_

using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;

namespace stm32 {
namespace dev {
namespace hal {
namespace dc_motor {
class DC_Motor {
 public:
    DC_Motor(Pin pin1, Pin pin2);
    void ClockWise();
    void AntiClockWise();
    void Stop();
 private:
    Pin pin1;
    Pin pin2;
};
}   //  namespace dc_motor
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //  DEV_HAL_INC_DC_MOTOR_H_ 
