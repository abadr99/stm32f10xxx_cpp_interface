/**
 * @file LKA.h
 * @author
 * @brief
 * @version 0.1
 * @date 2025-04-17
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef DEV_INC_HAL_LKA_H_
#define DEV_INC_HAL_LKA_H_

#include "hal/IR.h"
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::hal::ir;
using namespace stm32::dev::hal::dc_motor;

namespace stm32 {
namespace dev {
namespace app {
namespace lka {
class LKA {
 public:
    /**
     * @brief Construct a new LKA object
     *
     * @param buzzerPin Pin for the buzzer
     * @param leftirPin Pin for the left IR sensor
     * @param rightirPin Pin for the right IR sensor
     */
    LKA(const Pin& leftIrPin, const Pin& rightIrPin
      , const DC_Motor& leftMotor, const DC_Motor& rightMotor);

 private:
     static LKA* instance;
     IR leftIrPin_;
     IR rightIrPin_;
     DC_Motor leftMotor;
     DC_Motor rightMotor;
     static void Callback1();
     void LkaRightHandler();
     static void Callback2();
     void LkaLeftHandler();
};
}  // namespace lka
}  // namespace app 
}  // namespace dev
}  // namespace stm32
#endif  // DEV_INC_HAL_LKA_H_
