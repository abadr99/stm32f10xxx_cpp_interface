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

#define RCC_TIMEOUT    (400)
namespace stm32 {
namespace dev {
namespace mcal {
namespace rcc {

enum ClkConfig {
    kHsi,
    kHse,
    kHseDivBy2,
    kPll
};
enum PLL_MulFactor{
    kClock_1x  = 0b11111,
    kClock_2x  = 0b0000,
    kClock_3x  = 0b0001,
    kClock_4x  = 0b0010,
    kClock_5x  = 0b0011,
    kClock_6x  = 0b0100,
    kClock_7x  = 0b0101,
    kClock_8x  = 0b0110,
    kClock_9x  = 0b0111,
    kClock_10x = 0b1000,
    kClock_11x = 0b1001,
    kClock_12x = 0b1010,
    kClock_13x = 0b1011,
    kClock_14x = 0b1100,
    kClock_15x = 0b1101,
    kClock_16x = 0b1110
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
    kMcoNoClock,
    kMcoSystemClock=4,
    kMcoHsi,
    kMcoHse,
    kMcoPll
};

class Rcc {
 public:
    static void InitSysClock(ClkConfig config, PLL_MulFactor mulFactor);
    static void SetAHBPrescaler(AHP_ClockDivider divFactor);
    static void SetAPB1Prescaler(APB_ClockDivider divFactor);
    static void SetAPB2Prescaler(APB_ClockDivider divFactor);
    static void SetMCOPinClk(McoModes mode);
};

}  // namespace rcc
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_MCAL_INC_RCC_H_
