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

#include "stm32f103xx.h"

namespace stm32 {
namespace dev {
namespace mcal {
namespace rcc {

using stm32::peripherals::Peripheral;

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
    kMcoSystemClock = 4,
    kMcoHsi,
    kMcoHse,
    kMcoPll
};

enum HSE_Type {
    kHseCrystal,
    kHseRC,
};

class Rcc {
 public:
    static void SetExternalClock(const HSE_Type HseType);
    static void InitSysClock(const ClkConfig& config = kHse, const PLL_MulFactor& mulFactor = kClock_1x);   // NOLINT
    static void SetAHBPrescaler(const AHP_ClockDivider& divFactor);
    static void SetAPB1Prescaler(const APB_ClockDivider& divFactor);
    static void SetAPB2Prescaler(const APB_ClockDivider& divFactor);
    static void SetMCOPinClk(const McoModes& mode);
    static void AdjustInternalClock(uint8_t CalibrationValue);
    static void Enable(Peripheral p);
    static void Disable(Peripheral p);
 private:
    enum Flags { kHSIRDY, kHSERDY, kPLLRDY, };
    enum PllSource {
        kPllSource_Unkown,
        kPllSource_Hsi     = ClkConfig::kHsi ,
        kPllSource_Hse     = ClkConfig::kHse ,
        kPllSource_HseDiv2 = ClkConfig::kHseDivBy2,
    };
    static void WaitToReady(Flags flag);
    static void SetInternalHighSpeedClk();
    static void SetExternalHighSpeedClk();
    static void SetPllFactor(PLL_MulFactor factor);
    static void SetPllSource(PllSource src);
};

}  // namespace rcc
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_MCAL_INC_RCC_H_
