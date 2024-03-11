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
#ifndef DEV_MCAL_INC_RCC_H_
#define DEV_MCAL_INC_RCC_H_

namespace stm32 {
namespace dev {
namespace mcal {
namespace rcc {

enum ClkConfig {
    kHsi,
    kHse,
    kHseDivBy2
};
enum ClkMultFactor{
    Clkx1  = 0b11111,
    Clkx2  = 0b0000,
    Clkx3  = 0b0001,
    Clkx4  = 0b0010,
    Clkx5  = 0b0011,
    Clkx6  = 0b0100,
    Clkx7  = 0b0101,
    Clkx8  = 0b0110,
    Clkx9  = 0b0111,
    Clkx10 = 0b1000,
    Clkx11 = 0b1001,
    Clkx12 = 0b1010,
    Clkx13 = 0b1011,
    Clkx14 = 0b1100,
    Clkx15 = 0b1101,
    Clkx16 = 0b1110
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
    kMcoSystemClock,
    kMcoHsi,
    kMcoHse,
    kMcoPll
};

class RCC {
 public:
    static void InitSysClock(ClkConfig config, ClkMultFactor multFactor);
    static void SetAHBPrescaler(AHP_ClockDivider prescaler);
    static void SetAPB1Prescaler(APB_ClockDivider prescaler);
    static void SetAPB2Prescaler(APB_ClockDivider prescaler);
    static void SetMCOPinClk(McoModes mode);
};

}  // namespace rcc
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_MCAL_INC_RCC_H_
