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

/**
 * @struct Time
 * @brief Structure representing the current time.
 * 
 * This structure holds the hour, minute, and second of the RTC.
 */
struct Time {
    uint8_t hour;       /**< Hour component of the current time */
    uint8_t minutes;    /**< Minute component of the current time */
    uint8_t second;     /**< Second component of the current time */
};

/**
 * @struct RtcConfig
 * @brief Configuration structure for the RTC peripheral.
 * 
 * This structure defines the prescaler, counter, and alarm values, as well as interrupt service routines.
 */
struct RtcConfig {
    uint32_t prescaler_value;   /**< RTC prescaler value */
    uint32_t counter_value;     /**< RTC counter value */
    uint32_t alarm_value;       /**< RTC alarm value */
    stm32::type::pFunction SecondISR;     /**< Pointer to the ISR for the second tick interrupt */
    stm32::type::pFunction AlarmISR;      /**< Pointer to the ISR for the alarm interrupt */
    stm32::type::pFunction OverflowISR;   /**< Pointer to the ISR for the overflow interrupt */
};

/**
 * @class Rtc
 * @brief Class for controlling and configuring the RTC peripheral.
 * 
 * This class provides methods to initialize, control, and manage RTC features, including time setting, alarms, and interrupts.
 */
class Rtc {
 public:
    /**
     * @typedef pFunction
     * @brief Pointer to a function for RTC interrupt service routines.
     */
    using pFunction = stm32::type::pFunction;

    /**
     * @brief Initializes the RTC with the provided configuration.
     * 
     * @param config Configuration structure containing prescaler, counter, and alarm values.
     */
    static void Init(const RtcConfig &config);

    /**
     * @brief Gets the current time from the RTC.
     * 
     * @param pCurrent_time Pointer to the Time structure where the current time will be stored.
     */
    static void GetCurrentTime(Time *pCurrent_time);

    // Interrupt control methods
    /**
     * @brief Enables the RTC alarm interrupt.
     */
    static void AlarmInterruptEnable(void);

    /**
     * @brief Enables the RTC second tick interrupt.
     */
    static void SecondInterruptEnable(void);

    /**
     * @brief Enables the RTC overflow interrupt.
     */
    static void OverflowInterruptEnable(void);

    /**
     * @brief Disables the RTC alarm interrupt.
     */
    static void AlarmInterruptDisable(void);

    /**
     * @brief Disables the RTC second tick interrupt.
     */
    static void SecondInterruptDisable(void);

    /**
     * @brief Disables the RTC overflow interrupt.
     */
    static void OverflowInterruptDisable(void);

    // RTC control methods
    /**
     * @brief Enables the RTC peripheral.
     */
    static void Enable(void);

    /**
     * @brief Disables the RTC peripheral.
     */
    static void Disable(void);

    // ISR getter methods
    /**
     * @brief Gets the current alarm interrupt service routine.
     * 
     * @return pFunction Pointer to the current alarm ISR.
     */
    static pFunction GetAlarmISR(void);

    /**
     * @brief Gets the current overflow interrupt service routine.
     * 
     * @return pFunction Pointer to the current overflow ISR.
     */
    static pFunction GetOverflowISR(void);

    /**
     * @brief Gets the current second tick interrupt service routine.
     * 
     * @return pFunction Pointer to the current second ISR.
     */
    static pFunction GetSecondISR(void);
    
 private:
    /**
     * @brief Array of callback functions for RTC interrupts (Alarm, Overflow, Second).
     */
    static pFunction pRtcCallBackFunctions[3];

    // Configuration methods
    /**
     * @brief Enters the RTC configuration mode.
     * 
     * Allows setting various configuration values like prescaler, counter, and alarm.
     */
    static void EnterConfigMode(void);

    /**
     * @brief Exits the RTC configuration mode.
     */
    static void ExitConfigMode(void);

    /**
     * @brief Sets the RTC prescaler value.
     * 
     * @param prescaler_value Prescaler value for the RTC clock.
     */
    static void SetPrescaler(uint32_t prescaler_value);

    /**
     * @brief Sets the RTC alarm value.
     * 
     * @param alarm_value Alarm value in seconds.
     */
    static void SetAlarmValue(uint32_t alarm_value);

    /**
     * @brief Sets the RTC counter value.
     * 
     * @param time_in_seconds Counter value in seconds.
     */
    static void SetCounterValue(uint32_t time_in_seconds);

    // Utility methods
    /**
     * @brief Waits for the last RTC task to complete.
     */
    static void WaitForLastTask(void);

    /**
     * @brief Waits for RTC registers to synchronize.
     */
    static void WaitForSync(void);

    // ISR setter methods
    /**
     * @brief Sets the alarm interrupt service routine.
     * 
     * @param fun Pointer to the function to be set as the alarm ISR.
     */
    static void SetAlarmISR(pFunction fun);

    /**
     * @brief Sets the overflow interrupt service routine.
     * 
     * @param fun Pointer to the function to be set as the overflow ISR.
     */
    static void SetOverflowISR(pFunction fun);

    /**
     * @brief Sets the second tick interrupt service routine.
     * 
     * @param fun Pointer to the function to be set as the second ISR.
     */
    static void SetSecondISR(pFunction fun);
};

}  // namespace rtc 
}  // namespace mcal   
}  // namespace dev  
}  // namespace stm32


#endif  // DEV_INC_MCAL_RTC_H_
