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

namespace afio {
/**
 * @brief Structure defining AFIO (Alternate Function I/O) Register Definitions
 *
 * This structure defines the layout of AFIO registers used for configuring
 * alternate functions of GPIO pins on a microcontroller.
 */
struct AfioRegDef {
    union EVCR {
        struct {
            RegWidth_t PIN      :4;    // Event Output Pin
            RegWidth_t PORT     :3;    // Event Output Port
            RegWidth_t EVOE     :1;    // Event Output Enable
            RegWidth_t          :24;   // Reserved
        };
        RegWidth_t registerVal;  //  Register value
    } EVCR;                     //  Event Output Configuration Register

    union MAPR {
        struct {
            RegWidth_t SPI1_REMAP           :1;  // SPI1 remapping
            RegWidth_t I2C1_REMAP           :1;  // I2C1 remapping
            RegWidth_t USART1_REMAP         :1;  // USART1 remapping
            RegWidth_t USART2_REMAP         :1;  // USART2 remapping
            RegWidth_t USART3_REMAP         :2;  // USART3 remapping
            RegWidth_t TIM1_REMAP           :2;  // TIM1 remapping
            RegWidth_t TIM2_REMAP           :2;  // TIM2 remapping
            RegWidth_t TIM3_REMAP           :2;  // TIM3 remapping
            RegWidth_t TIM4_REMAP           :1;  // TIM4 remapping
            RegWidth_t CAN_REMAP            :2;  // CAN remapping
            RegWidth_t PD01_REMAP           :1;  // Port D0/Port D1 remapping   // NOLINT
            RegWidth_t TIM5CH4_IREMAP       :1;  // TIM5 Channel4 Input Capture 4 remapping     // NOLINT
            RegWidth_t ADC1_ETRGINJ_REMAP   :1;  // ADC1 External Trigger Injected Conversion remapping     // NOLINT
            RegWidth_t ADC1_ETRGREG_REMAP   :1;  // ADC1 External Trigger Regular Conversion remapping      // NOLINT
            RegWidth_t ADC2_ETRGINJ_REMAP   :1;  // ADC2 External Trigger Injected Conversion remapping     // NOLINT
            RegWidth_t ADC2_ETRGREG_REMAP   :1;  // ADC2 External Trigger Regular Conversion remapping      // NOLINT
            RegWidth_t                      :3;  // Reserved
            RegWidth_t SWJ_CFG              :3;  // Serial Wire JTAG configuration   // NOLINT
            RegWidth_t                      :5;  // Reserved
        };
        RegWidth_t registerVal;  // Register value
    } MAPR;  // AF remap and debug I/O configuration register

    RegWidth_t EXTICR1;  // External interrupt configuration register 1
    RegWidth_t EXTICR2;  // External interrupt configuration register 2
    RegWidth_t EXTICR3;  // External interrupt configuration register 3
    RegWidth_t EXTICR4;  // External interrupt configuration register 4

    union MAPR2 {
        struct {
            RegWidth_t                      :5;  // Reserved
            RegWidth_t TIM9_REMAP           :1;  // TIM9 remapping
            RegWidth_t TIM10_REMAP          :1;  // TIM10 remapping
            RegWidth_t TIM11_REMAP          :1;  // TIM11 remapping
            RegWidth_t TIM13_REMAP          :1;  // TIM13 remapping
            RegWidth_t TIM14_REMAP          :1;  // TIM14 remapping
            RegWidth_t FSMC_NADV            :1;  // FSMC NADV signal
            RegWidth_t                      :20;  // Reserved
        };
        RegWidth_t registerVal;  // Register value
    } MAPR2;  // AF remap and debug I/O configuration register 2
};

}  // namespace afio
}  // namespace registers
}  // namespace stm32

#endif  // DEV_MCAL_INC_STM32F103XX_H_
