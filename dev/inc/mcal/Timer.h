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
/**
 * @enum TimerID
 * @brief Enumeration representing the ID of the timer.
 */
enum TimerID {
    kTimer1,  /**< Timer 1 */
    kTimer2,  /**< Timer 2 */
    kTimer3,  /**< Timer 3 */
    kTimer4,  /**< Timer 4 */
    kTimer5   /**< Timer 5 */
};

/**
 * @enum TimerDirection
 * @brief Enumeration representing the counting direction of the timer.
 */
enum TimerDirection {
    kUP,    /**< Count up */
    kDown   /**< Count down */
};
enum TimerClkDivision {
    kDIV1 = 0x0000,
    kDIV2 = 0x0100,
    kDIV4 = 0x0200
};
enum TimerPolarity {
    kRisingEdge,
    kFallingEdge
};
enum TimerChannels {
    kChannel1,
    kChannel2,
    kChannel3,
    kChannel4
};
enum TimerSelection {
    kDirectTI, /**<TIM Input 1 is selected to be connected to IC1*/
    kIndirectTI, /**<TIM Input 1 is selected to be connected to IC2*/
    kTRC /**<TIM Input 1 is selected to be connected to TRC*/
};
enum OCMode {
    kTiming,  // Output compare timing mode (no output on the pin).
    kActive,  // Output compare active mode.
    kInactive,  // Output compare inactive mode.
    kToggle,  // Output compare toggle mode.
    kForced_Inactive,  // Forced inactive mode.
    kForced_Active,  // Forced active mode.
    kPWM1,  // PWM mode 1.
    kPWM2  // PWM mode 2.
};
enum OCPolarity {
    kActiveHigh ,
    kActiveLow 
};
enum OCIdleState {
    kIdleState_Reset,  // Output is reset during idle state
    kIdleState_Set  // Output is set during idle state.
};
enum State {
    kDisable,
    kEnable
};
struct TimeBaseTypeDef { /**< Direction of the timer (up/down) */
    TimerClkDivision ClkDivision;
};
struct TimerOCTypeDef {
    OCMode mode;
    State state;
    OCPolarity polarity;
    uint16_t period;
    OCIdleState idleState = kIdleState_Reset;
};
/**
 * @struct TimerConfig
 * @brief Structure representing the configuration settings for a timer.
 * 
 * This structure holds the configuration details such as timer mode, ID, direction, prescaler, 
 * and the function pointer for the interrupt service routine (ISR).
 */
struct TimerConfig {
    TimerID Timerid;
    TimerDirection Direction; /**< ID of the timer */
    uint16_t Prescaler; /**< Prescaler value for adjusting the timer frequency */
    State interrupt;
    stm32::type::pFunction pfunction = nullptr; /**< Function pointer to the ISR callback */
};
/**
 * @class Timer
 * @brief Class for configuring and controlling timers.
 * 
 * This class provides functions to initialize and control timers, create delays, and retrieve 
 * ISR function pointers.
 */
class Timer {
 public:
    using pFunction = stm32::type::pFunction;
    using timerRegDefPtr = stm32::type::RegType<stm32::registers::timer::timerRegDef>::ptr;

    /**
     * @brief Constructs a Timer object.
     * 
     * @param config A reference to a TimerConfig structure with the timer settings.
     */
    explicit Timer(const TimerConfig & config);
    static timerRegDefPtr GetPtr(TimerID idx);
    /**
     * @brief Creates a delay in milliseconds.
     * 
     * @param value The delay duration in milliseconds.
     */
    void Delay_ms(const TimeBaseTypeDef & counter, uint16_t value);
    void OCMode(const TimerOCTypeDef & OC);
    void SetCompare1(const TimerOCTypeDef & OC, TimerChannels channel, uint16_t pwmvalue);
    void Cmd(State state);
    /**
     * @brief Gets the function pointer to the ISR for the specified timer ID.
     * 
     * @param id The ID of the timer.
     * @return pFunction The function pointer to the ISR callback.
     */
    static pFunction GetFunToISR(TimerID id);

 private:
    /**
     * @brief Initializes the timer with the given configuration settings.
     */
    void Init();
    const TimerConfig& config_;  /**< Reference to the timer configuration structure */
    /**< Pointer to the timer register definition */
    timerRegDefPtr timerReg;
    static constexpr uint32_t kCallBackSiz = 5;
    /**< Global callback functions array for ISRs */
    static pFunction pGlobalCallBackFunction[kCallBackSiz];
    void Helper_TI1Config(TimerPolarity Polarity,
                          TimerSelection Selection, uint16_t Filter);
    void Helper_TI2Config(TimerPolarity Polarity,
                          TimerSelection Selection, uint16_t Filter);
};
}  // namespace timer
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_INC_MCAL_TIMER_H_
