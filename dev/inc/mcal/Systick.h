/**
 * @file Systick.h
 * @brief 
 * @version 0.1
 * @date 2024-03-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_INC_MCAL_SYSTICK_H_
#define DEV_INC_MCAL_SYSTICK_H_

#include "utils/Types.h"
namespace stm32 {
namespace dev {
namespace mcal {
namespace systick {

enum CLKSource {
    kAHB_Div_8,
    kAHB
};

class Systick {
 public:
    using pFunction = stm32::type::pFunction;
    using time_t = uint32_t;
    static void Enable(CLKSource clksource);
    static void SetCounterValue(uint32_t value);
    static void Delay_ms(uint32_t time_ms);
    static void Delay_us(uint32_t time_us);
    static void Delay_By_Exception(uint32_t value, pFunction func);
    time_t      GetElapsedTime();
    static void Disable();
    static pFunction GetPointerToISR();
 private:
    static pFunction PointerToISR;
    static void SetPointerToISR(pFunction func);
};


}  // namespace systick
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_INC_MCAL_SYSTICK_H_
