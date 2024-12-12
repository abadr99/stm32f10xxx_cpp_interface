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
 * @enum TimerMode
 * @brief Enumeration representing the mode of the timer.
 */
enum TimerMode {
    kTimeBase,  /**< Time base mode */
};

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

/**
 * @struct TimerConfig
 * @brief Structure representing the configuration settings for a timer.
 * 
 * This structure holds the configuration details such as timer mode, ID, direction, prescaler, 
 * and the function pointer for the interrupt service routine (ISR).
 */
struct TimerConfig {
    TimerMode mode;           /**< Mode of the timer */
    TimerID Timerid;          /**< ID of the timer */
    TimerDirection Direction; /**< Direction of the timer (up/down) */
    uint32_t Prescaler;       /**< Prescaler value for adjusting the timer frequency */
    stm32::type::pFunction pfunction;  /**< Function pointer to the ISR callback */
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
    void Delay_ms(uint16_t value);

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
    static pFunction pGlobalCallBackFunction[kCallBackSiz];  /**< Global callback functions array for ISRs */
};
}  // namespace timer
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_INC_MCAL_TIMER_H_
