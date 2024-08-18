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
	uint8_t TimerID;
	TimerDirection Direction;
};
class Timer1 {
 public:  
    static Init(TimerConfign & timer);
 private:
};



}  // namespace timer1
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_MCAL_INC_TIM1_H_
