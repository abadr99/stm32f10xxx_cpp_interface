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
#ifndef DEV_INC_MCAL_RCC_H_
#define DEV_INC_MCAL_RCC_H_

#include "mcal/stm32f103xx.h"


#define RCC_TIMEOUT    (400)    ///< Timeout value for RCC operations

namespace stm32 {
namespace dev {
namespace mcal {
namespace rcc {

using stm32::peripherals::Peripheral;

/**
 * @enum ClkConfig
 * @brief Enumeration representing the system clock configuration.
 */
enum ClkConfig {
    kHsi,           /**< Internal High-Speed Clock (HSI) */
    kHse,           /**< External High-Speed Clock (HSE) */
    kHseDivBy2,     /**< HSE clock divided by 2 */
    kPll            /**< Phase-Locked Loop (PLL) clock */
};

/**
 * @enum PLL_MulFactor
 * @brief Enumeration representing the PLL multiplier factors.
 */
enum PLL_MulFactor {
    kClock_1x  = 0b11111,  /**< PLL Clock Multiplier 1x */
    kClock_2x  = 0b0000,   /**< PLL Clock Multiplier 2x */
    kClock_3x  = 0b0001,   /**< PLL Clock Multiplier 3x */
    kClock_4x  = 0b0010,   /**< PLL Clock Multiplier 4x */
    kClock_5x  = 0b0011,   /**< PLL Clock Multiplier 5x */
    kClock_6x  = 0b0100,   /**< PLL Clock Multiplier 6x */
    kClock_7x  = 0b0101,   /**< PLL Clock Multiplier 7x */
    kClock_8x  = 0b0110,   /**< PLL Clock Multiplier 8x */
    kClock_9x  = 0b0111,   /**< PLL Clock Multiplier 9x */
    kClock_10x = 0b1000,   /**< PLL Clock Multiplier 10x */
    kClock_11x = 0b1001,   /**< PLL Clock Multiplier 11x */
    kClock_12x = 0b1010,   /**< PLL Clock Multiplier 12x */
    kClock_13x = 0b1011,   /**< PLL Clock Multiplier 13x */
    kClock_14x = 0b1100,   /**< PLL Clock Multiplier 14x */
    kClock_15x = 0b1101,   /**< PLL Clock Multiplier 15x */
    kClock_16x = 0b1110    /**< PLL Clock Multiplier 16x */
};

/**
 * @enum AHP_ClockDivider
 * @brief Enumeration representing the AHB clock divider options.
 */
enum AHP_ClockDivider {
    kAhpNotDivided = 0b0000,    /**< AHB clock not divided */
    kAhpDiv2       = 0b1000,    /**< AHB clock divided by 2 */
    kAhpDiv4       = 0b1001,    /**< AHB clock divided by 4 */
    kAhpDiv8       = 0b1010,    /**< AHB clock divided by 8 */
    kAhpDiv16      = 0b1011,    /**< AHB clock divided by 16 */
    kAhpDiv64      = 0b1100,    /**< AHB clock divided by 64 */
    kAhpDiv128     = 0b1101,    /**< AHB clock divided by 128 */
    kAhpDiv256     = 0b1110,    /**< AHB clock divided by 256 */
    kAhpDiv512     = 0b1111     /**< AHB clock divided by 512 */
};

/**
 * @enum APB_ClockDivider
 * @brief Enumeration representing the APB clock divider options.
 */
enum APB_ClockDivider {
    kApbNotDivided = 0b000,     /**< APB clock not divided */
    kApbDiv2       = 0b100,     /**< APB clock divided by 2 */
    kApbDiv4       = 0b101,     /**< APB clock divided by 4 */
    kApbDiv8       = 0b110,     /**< APB clock divided by 8 */
    kApbDiv16      = 0b111      /**< APB clock divided by 16 */
};

/**
 * @enum McoModes
 * @brief Enumeration representing the MCO (Microcontroller Clock Output) modes.
 */
enum McoModes {
    kMcoNoClock,            /**< No clock output */
    kMcoSystemClock = 4,    /**< System clock output */
    kMcoHsi,                /**< HSI clock output */
    kMcoHse,                /**< HSE clock output */
    kMcoPll                 /**< PLL clock output */
};

/**
 * @brief Enumeration for HSE (High-Speed External) clock types.
 */
enum HSE_Type {
    kHseCrystal,    /**< HSE crystal oscillator */
    kHseRC,         /**< HSE RC oscillator */
};

/**
 * @brief Class providing functions to configure and manage the RCC.
 */
class Rcc {
 public:
    static void Init();
    static volatile stm32::registers::rcc::RccRegDef* GetRccRegisters();




    /**
     * @brief Set the external clock source (HSE).
     * @param HseType Type of HSE (crystal or RC).
     */
    static void SetExternalClock(const HSE_Type HseType);

    /**
     * @brief Initialize the system clock.
     * @param config System clock configuration (default: HSE).
     * @param mulFactor PLL multiplier factor (default: kClock_1x).
     */
    static void InitSysClock(const ClkConfig& config = kHse, const PLL_MulFactor& mulFactor = kClock_1x); // NOLINT

    /**
     * @brief Set the AHB clock prescaler.
     * @param divFactor Prescaler division factor.
     */
    static void SetAHBPrescaler(const AHP_ClockDivider& divFactor);

    /**
     * @brief Set the APB1 clock prescaler.
     * @param divFactor Prescaler division factor.
     */
    static void SetAPB1Prescaler(const APB_ClockDivider& divFactor);

    /**
     * @brief Set the APB2 clock prescaler.
     * @param divFactor Prescaler division factor.
     */
    static void SetAPB2Prescaler(const APB_ClockDivider& divFactor);

    /**
     * @brief Set the MCO pin clock output mode.
     * @param mode MCO mode.
     */
    static void SetMCOPinClk(const McoModes& mode);

    /**
     * @brief Adjust the internal clock calibration value.
     * @param CalibrationValue Clock calibration value.
     */
    static void AdjustInternalClock(uint8_t CalibrationValue);

    /**
     * @brief Enable the clock for a specific peripheral.
     * @param p Peripheral to enable.
     */
    static void Enable(Peripheral p);

    /**
     * @brief Disable the clock for a specific peripheral.
     * @param p Peripheral to disable.
     */
    static void Disable(Peripheral p);

 private:
    /**
     * @brief Enumeration for clock readiness flags.
     */
    enum Flags { kHSIRDY, kHSERDY, kPLLRDY };

    /**
     * @brief Enumeration for PLL source selection.
     */
    enum PllSource {
        kPllSource_Unkown,
        kPllSource_Hsi     = ClkConfig::kHsi,       /**< HSI as PLL source */
        kPllSource_Hse     = ClkConfig::kHse,       /**< HSE as PLL source */
        kPllSource_HseDiv2 = ClkConfig::kHseDivBy2  /**< HSE divided by 2 as PLL source */
    };

    static volatile stm32::registers::rcc:: RccRegDef* RCC;


    /**
     * @brief Wait for a specific clock flag to be ready.
     * @param flag Clock readiness flag.
     */
    static void WaitToReady(Flags flag);

    /**
     * @brief Set the internal high-speed clock (HSI).
     */
    static void SetInternalHighSpeedClk();

    /**
     * @brief Set the external high-speed clock (HSE).
     */
    static void SetExternalHighSpeedClk();

    /**
     * @brief Set the PLL multiplier factor.
     * @param factor PLL multiplier factor.
     */
    static void SetPllFactor(PLL_MulFactor factor);

    /**
     * @brief Set the PLL source.
     * @param src PLL source.
     */
    static void SetPllSource(PllSource src);
};

}  // namespace rcc
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_INC_MCAL_RCC_H_
