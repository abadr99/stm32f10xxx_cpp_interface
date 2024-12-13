/**
 * @file Systick.h
 * @brief 
 * @version 0.1
 * @date 2024-03-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_INC_MCAL_SYSTICK_H_
#define DEV_INC_MCAL_SYSTICK_H_

#include "utils/Types.h"

namespace stm32 {
namespace dev {
namespace mcal {
namespace systick {

/**
 * @enum CLKSource
 * @brief Specifies the clock source for the SysTick timer.
 * 
 * This enum defines the available clock sources: AHB divided by 8 or AHB directly.
 */
enum CLKSource {
    kAHB_Div_8,  /**< AHB clock divided by 8 */
    kAHB         /**< AHB clock */
};

/**
 * @class Systick
 * @brief Class for configuring and managing the SysTick timer.
 * 
 * The SysTick timer can be used to generate delays, trigger periodic interrupts,
 * and measure elapsed time. This class provides methods to enable the timer,
 * set the counter value, and configure interrupt service routines.
 */
class Systick {
 public:
    /**
     * @brief Function pointer type for callback functions (interrupt service routines).
     */
    using pFunction = stm32::type::pFunction;

    /**
     * @brief Defines the type for time values (in milliseconds or microseconds).
     */
    using time_t = uint32_t;

    /**
     * @brief Enables the SysTick timer with the specified clock source.
     * 
     * @param clksource The clock source for SysTick (either kAHB or kAHB_Div_8).
     */
    static void Enable(CLKSource clksource);

    /**
     * @brief Sets the SysTick counter value.
     * 
     * @param value The counter value to set.
     */
    static void SetCounterValue(uint32_t value);

    /**
     * @brief Creates a delay in milliseconds.
     * 
     * This method causes the program to wait for the specified time in milliseconds.
     * 
     * @param time_ms The delay time in milliseconds.
     */
    static void Delay_ms(uint32_t time_ms);

    /**
     * @brief Creates a delay in microseconds.
     * 
     * This method causes the program to wait for the specified time in microseconds.
     * 
     * @param time_us The delay time in microseconds.
     */
    static void Delay_us(uint32_t time_us);

    /**
     * @brief Creates a delay and calls an exception function.
     * 
     * This method creates a delay for the specified time, and during the delay, 
     * it triggers the provided exception function.
     * 
     * @param value The delay value.
     * @param func The function to call during the delay.
     */
    static void Delay_By_Exception(uint32_t value, pFunction func);

    /**
     * @brief Returns the elapsed time since the last counter reset.
     * 
     * @return time_t The elapsed time in milliseconds.
     */
    time_t GetElapsedTime();

    /**
     * @brief Disables the SysTick timer.
     */
    static void Disable();

    /**
     * @brief Gets the pointer to the interrupt service routine (ISR).
     * 
     * @return pFunction Pointer to the ISR.
     */
    static pFunction GetPointerToISR();

 private:
    using SystickRegDef = stm32::registers::systick::SystickRegDef;
    static stm32::type::RegType<SystickRegDef>::ptr SYSTICK;
    /**
     * @brief Sets the pointer to the interrupt service routine (ISR).
     * 
     * @param func The function to set as the ISR.
     */
    static void SetPointerToISR(pFunction func);

    /**
     * @brief Pointer to the current ISR.
     */
    static pFunction PointerToISR;
};


}  // namespace systick
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_INC_MCAL_SYSTICK_H_

