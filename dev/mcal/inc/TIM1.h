/**
 * @file TIM1.h
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-08-05
 * @copyright Copyright (c) 2024
 */
#ifndef DEV_MCAL_INC_TIM1_H_
#define DEV_MCAL_INC_TIM1_H_

#include "utils/inc/Types.h"

using namespace stm32::utils::types;
namespace stm32 {
namespace dev {
namespace mcal {
namespace timer1 {

enum TimerDirection {
  kUP,
  kDown
};
struct TimerConfign {
	uint16_t ReloadValue;
	TimerDirection Direction;
    pFunction pfunction;
};
class Timer1 {
 public:  
    Timer1(TimerConfign & timer);
    static pFunction Helper_GetFunToISR();
 private:
    static pFunction pGlobalCallBackFunction;
};
}  // namespace timer1
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_MCAL_INC_TIM1_H_
