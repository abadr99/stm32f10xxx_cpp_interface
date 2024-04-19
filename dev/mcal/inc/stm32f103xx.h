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
/**
 * @brief Structure defining GPIO Register Definitions
 *
 * This structure defines the layout of GPIO registers for controlling
 * the behavior and state of GPIO pins on a microcontroller.
 */
struct GpioRegDef {
    RegWidth_t CRL;     // Port configuration register low
    RegWidth_t CRH;     // Port configuration register high
    RegWidth_t IDR;     // Input data register
    RegWidth_t ODR;     // Output data register
    RegWidth_t BSRR;    // Bit set/reset register
    RegWidth_t BRR;     // Bit reset register
    RegWidth_t LCKR;    // Lock register
};

#define GPIOA  (reinterpret_cast<volatile GpioRegDef*>(GPIOA_BASE_ADDRESS))
#define GPIOB  (reinterpret_cast<volatile GpioRegDef*>(GPIOB_BASE_ADDRESS))
#define GPIOC  (reinterpret_cast<volatile GpioRegDef*>(GPIOC_BASE_ADDRESS))

}  // namespace gpio
namespace nvic {
/**
 * @brief Structure defining NVIC Register Definitions
 *
 * This structure defines the layout of NVIC registers for controlling
 */
struct NvicRegDef {
    RegWidth_t ISER[8];
    RegWidth_t RESERVED0[24];
    RegWidth_t ICER[8];
    RegWidth_t RESERVED1[24];
    RegWidth_t ISPR[8];
    RegWidth_t RESERVED2[24];
    RegWidth_t ICPR[8];
    RegWidth_t RESERVED3[24];
    RegWidth_t IABR[8];
    RegWidth_t RESERVED4[56];
    // TO DO THE REST
};

#define NVIC   (reinterpret_cast<volatile NvicRegDef*>(NVIC_BASE_ADDRESS))

}  // namespace nvic
}  // namespace registers
}  // namespace stm32

#endif  // DEV_MCAL_INC_STM32F103XX_H_
