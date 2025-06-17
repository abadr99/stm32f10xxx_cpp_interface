/**
 * @file CarControl.h
 * @brief
 * @version 0.1
 * @date 2025-02-07
 * 
 * @copyright Copyright (c) 2025
 */

#ifndef DEV_INC_HAL_CAR_CONTROL_H_
#define DEV_INC_HAL_CAR_CONTROL_H_

using namespace stm32::dev::hal::dc_motor;
using namespace stm32::dev::hal::bluetooth;

namespace stm32 {
namespace dev {
namespace app {
namespace car_control {
class Car_Control {
 public:
    Car_Control(const DC_Motor& leftMotor, const DC_Motor& rightMotor, const HC05& bt);
    void ProcessCommand();
 private:
    DC_Motor leftMotor;
    DC_Motor rightMotor;
    HC05 bt;
};
}  // namespace car_control
}  // namespace app
}  // namespace dev
}  // namespace stm32
#endif  // DEV_INC_HAL_CAR_CONTROL_H_
