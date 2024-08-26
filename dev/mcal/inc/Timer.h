/**
 * @file Timer.h
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-08-05
 * @copyright Copyright (c) 2024
 */
#ifndef DEV_MCAL_INC_TIMER_H_
#define DEV_MCAL_INC_TIMER_H_

#include "../../mcal/inc/stm32f103xx.h"
#include "utils/inc/Types.h"

using namespace stm32::registers::timer;
using namespace stm32::utils::types;
namespace stm32 {
namespace dev {
namespace mcal {
namespace timer {

enum TimerID {
    kTimer1,
    kTimer2,
    kTimer3,
    kTimer4,
    kTimer5
};

enum TimerDirection {
  kUP,
  kDown
};
struct TimerConfig {
    TimerID Timerid;
    TimerDirection Direction;
    uint16_t ReloadValue;
    uint16_t Prescaler = 44999;  // if bus clk = 45MHz , psc = 44999+1 --> time base = 1ms
    pFunction pfunction;
};
class Timer {
 public:  
    explicit Timer(const TimerConfig & config);
    void Init(const TimerConfig & config);
    static pFunction Helper_GetFunToISR(TimerID id);
 private:
    const TimerConfig& config_;
    volatile timerRegDef* timerReg;
    static pFunction pGlobalCallBackFunction[5];
};
}  // namespace timer
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_MCAL_INC_TIMER_H_
