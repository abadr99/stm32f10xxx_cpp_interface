/**
 * @file RTC.h
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-07-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_INC_MCAL_RTC_H_
#define DEV_INC_MCAL_RTC_H_

namespace stm32 {
namespace dev   {
namespace mcal  {
namespace rtc   {

struct Time {
    uint8_t hour;
    uint8_t minutes;
    uint8_t second;
};

struct RtcConfig {
    uint32_t prescaler_value;
    uint32_t counter_value;
    uint32_t alarm_value;
    stm32::type::pFunction SecondISR;
    stm32::type::pFunction AlarmISR;
    stm32::type::pFunction OverflowISR;
};

class Rtc {
 public:
    using pFunction = stm32::type::pFunction;
    static volatile stm32::registers::rtc::RtcRegDef* GetRtcRegister();
    // Initialization and control
    static void Init(const RtcConfig &config);
    static void GetCurrentTime(Time *pCurrent_time);

    static void AlarmInterruptEnable(void);
    static void SecondInterruptEnable(void);
    static void OverflowInterruptEnable(void);

    static void AlarmInterruptDisable(void);
    static void SecondInterruptDisable(void);
    static void OverflowInterruptDisable(void);
    
    static void Enable(void);
    static void Disable(void);
    
    static pFunction GetAlarmISR(void);
    static pFunction GetOverflowISR(void);
    static pFunction GetSecondISR(void);
    
 private:
    static volatile stm32::registers::rtc:: RtcRegDef* RTC;
    static pFunction pRtcCallBackFunctions[3];

    // Configuration
    static void EnterConfigMode(void);
    static void ExitConfigMode(void);
    static void SetPrescaler(uint32_t prescaler_value);
    static void SetAlarmValue(uint32_t alarm_value);
    static void SetCounterValue(uint32_t time_in_seconds);
    
    static void WaitForLastTask(void);
    static void WaitForSync(void);

    // Interrupts
    static void SetAlarmISR(pFunction fun);
    static void SetOverflowISR(pFunction fun);
    static void SetSecondISR(pFunction fun);
};

}  // namespace rtc 
}  // namespace mcal   
}  // namespace dev  
}  // namespace stm32


#endif  // DEV_INC_MCAL_RTC_H_
