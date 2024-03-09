/**
 * @file RCC.h
 * @author 
 * @brief
 * @version 0.1
 * @date 2024-03-8
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_MCAL_RCC_RCC_H_
#define DEV_MCAL_RCC_RCC_H_

namespace stm32 {
namespace dev {
namespace mcal {
namespace rcc {

enum ClkConfig {

};

enum AHP_ClockDivider {
    kAhpNotDivided = 0b0000,
    kAhpDiv2       = 0b1000,
    kAhpDiv4       = 0b1001,
    kAhpDiv8       = 0b1010,
    kAhpDiv16      = 0b1011,
    kAhpDiv64      = 0b1100,
    kAhpDiv128     = 0b1101,
    kAhpDiv256     = 0b1110,
    kAhpDiv512     = 0b1111
};

enum APB_ClockDivider  {
    kApbNotDivided = 0b000,
    kApbDiv2       = 0b100,
    kApbDiv4       = 0b101,
    kApbDiv8       = 0b110,
    kApbDiv16      = 0b111
};

enum McoModes { 
    kSystemClock,
    kHsi,
    kHse,
    kPll
};

class RCC {
 public:
    static void InitSysClock(ClkConfig systemClk);
    static void SetAHBPrescaler(AHP_ClockDivider prescaler);
    static void SetAPB1Prescaler(APB_ClockDivider prescaler);
    static void SetAPB2Prescaler(APB_ClockDivider prescaler);
    static void SetMCOPinClk(McoModes mode);
};

}  // namespace rcc
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_MCAL_RCC_RCC_H_
