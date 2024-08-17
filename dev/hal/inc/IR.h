/**
 * @file IR.h
 * @author
 * @brief
 * @version 0.1
 * @date 2024-07-29
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_IR_H_
#define DEV_HAL_INC_IR_H_
using namespace stm32::dev::mcal::pin;
namespace stm32 {
namespace dev {
namespace hal {
namespace ir {
class IR {
 public:
    using IrState = uint8_t;
    explicit IR(const Pin& IrPin);
    IrState GetIrStatus();
 private:
    Pin IrPin_;
};
}  // namespace ir
}  // namespace hal
}  // namespace dev
}  // namespace stm32  
#endif  // DEV_HAL_INC_IR_H_
