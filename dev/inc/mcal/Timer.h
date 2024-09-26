/**
 * @file Timer.h
 * @author Manar Abdelraouf
 * @brief 
 * @version 0.1
 * @date 2024-08-05
 * @copyright Copyright (c) 2024
 */
#ifndef DEV_INC_MCAL_TIMER_H_
#define DEV_INC_MCAL_TIMER_H_

#include "mcal/stm32f103xx.h"
#include "utils/Types.h"

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
    uint32_t Prescaler;  // if bus clk = 4MHz , psc = 4000 --> time base = 1ms
    stm32::type::pFunction pfunction;
};
class Timer {
 public:
    using pFunction = stm32::type::pFunction;
    explicit Timer(const TimerConfig & config);
    void Delay_ms(uint16_t value);
    static pFunction GetFunToISR(TimerID id);
 private:
    void Init();
    const TimerConfig& config_;
    volatile stm32::registers::timer::timerRegDef* timerReg;
    static pFunction pGlobalCallBackFunction[5];
};
}  // namespace timer
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_INC_MCAL_TIMER_H_
