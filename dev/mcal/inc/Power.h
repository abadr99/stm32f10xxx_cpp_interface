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
enum PwrRegulater {
    kOn,
    kLowPower,
};
enum PwrEntry {
    kWFI,
    kWFE,
};
class Pwr {
 public:
    void EnterSleepMode(PwrEntry sleepEntry);
    void EnterStopMode(PwrRegulater regulater, PwrEntry stopEntry);
    void EnterStandbyMode(PwrEntry standbyEntry);
};
}   // namespace pwr
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  //  DEV_MCAL_INC_POWER_H_
