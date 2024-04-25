/**
 * @file Systick.h
 * @brief 
 * @version 0.1
 * @date 2024-03-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_MCAL_INC_SYSTICK_H_
#define DEV_MCAL_INC_SYSTICK_H_

using namespace stm32::utils::types;
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
    static void Enable(void);
    static void Delay_ms(CLKSource clksource, uint32_t value);
    static void Delay_us(CLKSource clksource, uint32_t value);
    static void Delay_By_Exception(CLKSource clksource, uint32_t value, pFunction func);
    uint32_t GetElapsedTime();
 private:
    static pFunction PointerToISR;
};


}  // namespace systick
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_MCAL_INC_SYSTICK_H_
