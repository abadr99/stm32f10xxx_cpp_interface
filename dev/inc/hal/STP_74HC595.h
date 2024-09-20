/**
 * @file STP_74HC595.h
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-07-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_HAL_INC_STP_74HC595_H_
#define DEV_HAL_INC_STP_74HC595_H_

namespace stm32 {
namespace dev {
namespace hal {
namespace shift_register {

// TODO(@abadr99): Support multiple shift registers
// NOTES: This class requires initializing systick peripheral
class STP_74HC595 {
 public:
    using Pin = stm32::dev::mcal::pin::Pin;
    using ShiftRegisterWidth = uint8_t;
    
    STP_74HC595(const Pin& serialInputPin, 
                const Pin& shiftClkPin, 
                const Pin& storageClk);

    void Write(ShiftRegisterWidth val);
 private:
    struct Pins {
        Pin serialInputPin;
        Pin shiftClkPin;
        Pin storageClk;
    };
    Pins pins_;
    void Pulse();
};

}  // namespace shift_register
}  // namespace hal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_HAL_INC_STP_74HC595_H_

