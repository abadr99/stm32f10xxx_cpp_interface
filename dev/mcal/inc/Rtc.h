/**
 * @file RTC.h
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-07-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_MCAL_INC_RTC_H_
#define DEV_MCAL_INC_RTC_H_

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
    pFunction SecondISR;
    pFunction AlarmISR;
    pFunction OverflowISR;
};

class Rtc {
 public:
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


#endif  // DEV_MCAL_INC_RTC_H_
