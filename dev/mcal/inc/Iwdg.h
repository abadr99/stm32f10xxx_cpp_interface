/**
 * @file Iwdg.h
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-07-22
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_MCAL_INC_IWDG_H_
#define DEV_MCAL_INC_IWDG_H_

namespace stm32 {
namespace dev {
namespace mcal {
namespace iwdg {
enum Prescaler {
    kDiv4,
    kDiv8,
    kDiv16,
    kDiv32,
    kDiv64,
    kDiv128,
    kDiv256
};
template<Prescaler prescaler, uint16_t reloadVal = 0xFFF>
class Iwdg {
 public: 
    Iwdg();
    void Refresh();
}; 
}   // namespace iwdg
}   // namespace mcal
}   // namespace dev
}   // namespace stm32



#endif  // DEV_MCAL_INC_IWDG_H_
