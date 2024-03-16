/**
 * @file stm32f103xx.h
 * @author
 * @brief
 * @version 0.1
 * @date 2024-03-09
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef DEV_MCAL_INC_STM32F103XX_H_
#define DEV_MCAL_INC_STM32F103XX_H_

#ifdef UNIT_TEST
#include "../../../tests/unittests/mcal/BaseAddress-test.h"
#else
#include "mcal/inc/BaseAddress.h"
#endif

#include "utils/inc/Types.h"

using RegWidth_t = stm32::utils::types::RegWidth_t;
namespace stm32 {
namespace registers {
namespace rcc {

/********************** RCC Register Definition  **********************/

struct RccRegDef{
    union CR {
        struct {
            RegWidth_t HSION   :1; /* High-speed internal oscillator enable */
            RegWidth_t HSIRDY  :1; /* High-speed internal oscillator ready */
            RegWidth_t         :1; /* Reserved */
            RegWidth_t HSITRIM :5; /* High-speed internal oscillator trimming */
            RegWidth_t HSICAL  :8; /* High-speed internal oscillator calibration*/  // NOLINT
            RegWidth_t HSEON   :1; /* High-speed external oscillator enable */
            RegWidth_t HSERDY  :1; /* High-speed external oscillator ready */
            RegWidth_t HSEBYP  :1; /* High-speed external oscillator bypass */
            RegWidth_t CSSON   :1; /* Clock security system enable */
            RegWidth_t         :4; /* Reserved */
            RegWidth_t PLLON   :1; /* Phase-locked loop enable */
            RegWidth_t PLLRDY  :1; /* Phase-locked loop ready */
            RegWidth_t         :6; /* Reserved */
        };
        RegWidth_t registerVal;   /** RCC control register  */
    }CR;

    union CFGR {
        struct {
            RegWidth_t SW        :2; /* System clock switch */
            RegWidth_t SWS       :2; /* System clock switch status */
            RegWidth_t HPRE      :4; /* AHB prescaler */
            RegWidth_t PPRE1     :3; /* APB low-speed prescaler (APB1) */
            RegWidth_t PPRE2     :3; /* APB high-speed prescaler (APB2) */
            RegWidth_t ADCPRE    :2; /* ADC prescaler */
            RegWidth_t PLLSRC    :1; /* PLL entry clock source */
            RegWidth_t PLLXTPRE  :1; /* HSE divider for PLL entry */
            RegWidth_t PLLMUL    :4; /* PLL multiplication factor */
            RegWidth_t USBPRE    :1; /* USB prescaler */
            RegWidth_t           :1; /* Reserved */
            RegWidth_t MCO       :3; /* MicroController clock output */
            RegWidth_t           :5; /* Reserved  */
        };
        RegWidth_t registerVal; /* Clock configuration register */
    }CFGR; /* Clock configuration register */

    RegWidth_t CIR;
    RegWidth_t APB2RSTR;
    RegWidth_t APB1RSTR;
    RegWidth_t AHBENR;
    RegWidth_t APB2ENR;
    RegWidth_t APB1ENR;
    RegWidth_t BDCR;
    RegWidth_t CSR;
};

/**
 * @brief Clock configuration register
 */
#define RCC  (reinterpret_cast<volatile RccRegDef*>(RCC_BASE_ADDRESS))

}  // namespace rcc

namespace gpio {
struct GpioRegDef {
    union CRL {
        struct {
            RegWidth_t MODE0    :2;   // Port x mode bits
            RegWidth_t CNF0     :2;   // Port x configuration bits
            RegWidth_t MODE1    :2;
            RegWidth_t CNF1     :2;
            RegWidth_t MODE2    :2;
            RegWidth_t CNF2     :2;
            RegWidth_t MODE3    :2;
            RegWidth_t CNF3     :2;
            RegWidth_t MODE4    :2;
            RegWidth_t CNF4     :2;
            RegWidth_t MODE5    :2;
            RegWidth_t CNF5     :2;
            RegWidth_t MODE6    :2;
            RegWidth_t CNF6     :2;
            RegWidth_t MODE7    :2;
            RegWidth_t CNF7     :2;
        };
        RegWidth_t registerVal;   // Port configuration register low
    }CRL;   // Port configuration register low

    union CRH {
        struct {
            RegWidth_t MODE8     :2;   // Port x mode bits
            RegWidth_t CNF8      :2;   // Port x configuration bits
            RegWidth_t MODE9     :2;
            RegWidth_t CNF9      :2;
            RegWidth_t MODE10    :2;
            RegWidth_t CNF10     :2;
            RegWidth_t MODE11    :2;
            RegWidth_t CNF11     :2;
            RegWidth_t MODE12    :2;
            RegWidth_t CNF12     :2;
            RegWidth_t MODE13    :2;
            RegWidth_t CNF13     :2;
            RegWidth_t MODE14    :2;
            RegWidth_t CNF14     :2;
            RegWidth_t MODE15    :2;
            RegWidth_t CNF15     :2;
        };
        RegWidth_t registerVal;   // Port configuration register High
    }CRH;   // Port configuration register High

    RegWidth_t IDR;
    RegWidth_t ODR;
    RegWidth_t BSRR;
    RegWidth_t BRR;
    RegWidth_t LCKR;
};

#define GPIOA  (reinterpret_cast<volatile GpioRegDef*>(GPIOA_BASE_ADDRESS))
#define GPIOB  (reinterpret_cast<volatile GpioRegDef*>(GPIOB_BASE_ADDRESS))
#define GPIOC  (reinterpret_cast<volatile GpioRegDef*>(GPIOC_BASE_ADDRESS))
#define GPIOD  (reinterpret_cast<volatile GpioRegDef*>(GPIOD_BASE_ADDRESS))
#define GPIOE  (reinterpret_cast<volatile GpioRegDef*>(GPIOE_BASE_ADDRESS))
#define GPIOF  (reinterpret_cast<volatile GpioRegDef*>(GPIOF_BASE_ADDRESS))
#define GPIOG  (reinterpret_cast<volatile GpioRegDef*>(GPIOG_BASE_ADDRESS))

}  // namespace gpio
}  // namespace registers
}  // namespace stm32

#endif  // DEV_MCAL_INC_STM32F103XX_H_
