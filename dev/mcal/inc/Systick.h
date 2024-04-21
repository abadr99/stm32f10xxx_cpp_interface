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

#define SYSTICK_MAX_VALUE   (16777216)  //  24 bit

enum CLKSource {
    kAHB_Div_8,
    kAHB
};
class Systick {
 public:
    Systick();
    void delay_ms(CLKSource clksource, uint32_t value);
    void delay_micro_s(CLKSource clksource, uint32_t value);
    void Counter(CLKSource clksource, uint32_t value, pFunction * func);
    uint32_t GetElapsedTime(void);
};


}  // namespace systick
}  // namespace mcal
}  // namespace dev
}  // namespace stm32
// Name function
// static
// function 

#endif  // DEV_MCAL_INC_SYSTICK_H_
