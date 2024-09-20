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
#ifndef DEV_MCAL_INC_POWER_H_
#define DEV_MCAL_INC_POWER_H_
namespace stm32 {
namespace dev   {
namespace mcal  {
namespace pwr {

enum class SleepType {
    kSleepNow,
    kSleepOnExit
};
enum class PwrRegulator {
    kOn,
    kLowPower
};

enum class PwrEntry {
    kWFI,  //  wait for interrupt
    kWFE   //  wait for event
};
enum class State {
    kDisable,
    kEnable
};
enum class PwrFlag {
    kWU,  //  wakeup flag
    kSB   //  standby flag
};

class Pwr {
 public:
    static void EnterSleepMode(PwrEntry sleepEntry, SleepType type);
    static void EnterStopMode(PwrEntry stopEntry, PwrRegulator regulator);
    static void EnterStandbyMode(PwrEntry standbyEntry);
/**
 * @note this is used for wakeup from Standby mode and forced in input pull down
            configuration (rising edge on pin wakes-up the system from Standby mode)
 */
    static void WakeupPinState(State state);
    static void ClearFlag(PwrFlag flag);
 private:
    static void EnterLowPowerMode(PwrEntry entry);
};
}   // namespace pwr
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  //  DEV_MCAL_INC_POWER_H_
