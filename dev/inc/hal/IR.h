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
#ifndef DEV_INC_HAL_IR_H_
#define DEV_INC_HAL_IR_H_
using namespace stm32::dev::mcal::pin;
namespace stm32 {
namespace dev {
namespace hal {
namespace ir {
class IR {
 public:
    /**
     * @typedef IrState
     * @brief Defines the data type for representing the state of the IR sensor.
     */
    using IrState = uint8_t;

    /**
     * @brief Constructs an IR sensor object.
     * 
     * @param IrPin The GPIO pin where the IR sensor is connected.
     */
    explicit IR(const Pin& IrPin);

    /**
     * @brief Retrieves the current status of the IR sensor.
     * 
     * @return The IR sensor state as a value of type IrState.
     */
    IrState GetIrStatus();

 private:
    Pin IrPin_;   /**< The GPIO pin connected to the IR sensor. */
};
}  // namespace ir
}  // namespace hal
}  // namespace dev
}  // namespace stm32  
#endif  // DEV_INC_HAL_IR_H_
