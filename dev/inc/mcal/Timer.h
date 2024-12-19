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
enum InterruptState {
    kDisable,
    kEnable
};
struct TimeBaseTypeDef {
    TimerDirection Direction; /**< Direction of the timer (up/down) */
    TimerClkDivision ClkDivision;
};
struct IcTypeDef {
    TimerChannels channel;
    TimerSelection Selection; /**<specifies the input to be used */
    TimerPolarity Polarity; /**< Polarity of the timer (falling/rising edge) */
    uint8_t Filter; /**<Specifies the Input Capture Filter */ 
};
/**
 * @struct TimerConfig
 * @brief Structure representing the configuration settings for a timer.
 * 
 * This structure holds the configuration details such as timer mode, ID, direction, prescaler, 
 * and the function pointer for the interrupt service routine (ISR).
 */
struct TimerConfig {
    TimerID Timerid; /**< ID of the timer */
    uint16_t Prescaler; /**< Prescaler value for adjusting the timer frequency */
    InterruptState interrupt;
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
    void ICMode(const IcTypeDef & IC);

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
};
}  // namespace timer
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_INC_MCAL_TIMER_H_
