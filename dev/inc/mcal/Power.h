/**
 * @file Power.h
 * @author noura36
 * @brief 
 * @version 0.1
 * @date 2024-08-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_INC_MCAL_POWER_H_
#define DEV_INC_MCAL_POWER_H_
namespace stm32 {
namespace dev   {
namespace mcal  {
namespace pwr {

/**
 * @enum SleepType
 * @brief Specifies different sleep mode types.
 * 
 * This enum defines the sleep behavior, whether the system sleeps immediately
 * or waits until after an interrupt.
 */
enum class SleepType {
    kSleepNow,     /**< Enter sleep mode immediately. */
    kSleepOnExit   /**< Enter sleep mode after interrupt service routines. */
};

/**
 * @enum PwrRegulator
 * @brief Specifies the power regulator state in low-power modes.
 * 
 * This enum defines whether the system should use the regular power supply or
 * switch to low-power mode.
 */
enum class PwrRegulator {
    kOn,          /**< Main power regulator on. */
    kLowPower     /**< Low-power regulator mode. */
};

/**
 * @enum PwrEntry
 * @brief Specifies the entry type for low-power modes.
 * 
 * This enum defines how the system should enter low-power modes, either
 * waiting for an interrupt or an event.
 */
enum class PwrEntry {
    kWFI,   /**< Wait for interrupt to enter low-power mode. */
    kWFE    /**< Wait for event to enter low-power mode. */
};

/**
 * @enum State
 * @brief Specifies the state of a power-related feature.
 * 
 * This enum defines whether a feature (such as the wakeup pin) is enabled
 * or disabled.
 */
enum class State {
    kDisable,   /**< Feature is disabled. */
    kEnable     /**< Feature is enabled. */
};

/**
 * @enum PwrFlag
 * @brief Power flags used for status checking.
 * 
 * This enum defines flags related to power management, such as the wakeup
 * flag and the standby flag.
 */
enum class PwrFlag {
    kWU,    /**< Wakeup flag. */
    kSB     /**< Standby flag. */
};

/**
 * @class Pwr
 * @brief Provides power management functions.
 * 
 * The Pwr class provides static methods to manage the low-power modes of
 * the STM32 microcontroller, including entering sleep, stop, and standby
 * modes, and controlling wakeup pin and flag status.
 */
class Pwr {
 public:
    using PwrRegDef = stm32::registers::pwr::PwrRegDef;
    /**
     * @brief Gets a pointer to the PWR register definition.
     */
    template<typename T>
    static volatile T* GetPtr();
    /**
     * @brief Initializes the PWR peripheral.
     * 
     * This function sets up the PWR peripheral by assigning the base address
     * of the PWR registers to the internal pointer.
     */
    static void Init();
    /**
     * @brief Enter sleep mode.
     * 
     * @param sleepEntry Specifies how the system enters sleep (wait for interrupt/event).
     * @param type Specifies the sleep behavior (immediate or on exit).
     */
    static void EnterSleepMode(PwrEntry sleepEntry, SleepType type);

    /**
     * @brief Enter stop mode.
     * 
     * @param stopEntry Specifies how the system enters stop mode (wait for interrupt/event).
     * @param regulator Specifies the power regulator mode (on or low-power).
     */
    static void EnterStopMode(PwrEntry stopEntry, PwrRegulator regulator);

    /**
     * @brief Enter standby mode.
     * 
     * @param standbyEntry Specifies how the system enters standby mode (wait for interrupt/event).
     */
    static void EnterStandbyMode(PwrEntry standbyEntry);

    /**
     * @brief Configure the state of the wakeup pin.
     * 
     * @note This function is used to configure the wakeup pin in standby mode. The pin is forced
     * into input pull-down configuration, and a rising edge on the pin will wake up the system.
     * 
     * @param state Specifies whether to enable or disable the wakeup pin.
     */
    static void WakeupPinState(State state);

    /**
     * @brief Clear the specified power flag.
     * 
     * @param flag The power flag to be cleared (e.g., wakeup flag or standby flag).
     */
    static void ClearFlag(PwrFlag flag);

 private:
    static  stm32::type::RegType<PwrRegDef>::ptr PWR;
    static void EnterLowPowerMode(PwrEntry entry);
};

}   // namespace pwr
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  //  DEV_INC_MCAL_POWER_H_
