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

#if UNIT_TEST == 1
    #include "baseAddress-test.h"
#elif UNIT_TEST == 0
    #include "baseAddress.h"
#endif  // UNIT TEST

namespace stm32 {
namespace registers {
namespace rcc {

/********************** RCC Register Definition  **********************/

struct RccRegDef{
    union CR {
        struct {
            uint8_t HSION   :1; /* High-speed internal oscillator enable */
            uint8_t HSIRDY  :1; /* High-speed internal oscillator ready */
            uint8_t         :1; /* Reserved */
            uint8_t HSITRIM :5; /* High-speed internal oscillator trimming */
            uint8_t HSICAL  :8; /* High-speed internal oscillator calibration*/
            uint8_t HSEON   :1; /* High-speed external oscillator enable */
            uint8_t HSERDY  :1; /* High-speed external oscillator ready */
            uint8_t HSEBYP  :1; /* High-speed external oscillator bypass */
            uint8_t CSSON   :1; /* Clock security system enable */
            uint8_t         :4; /* Reserved */
            uint8_t PLLON   :1; /* Phase-locked loop enable */
            uint8_t PLLRDY  :1; /* Phase-locked loop ready */
        };
        uint32_t registerVal;   /** RCC control register  */
    }CR;

    union CFGR{
        struct {
            uint8_t SW        :2; /* System clock switch */
            uint8_t SWS       :2; /* System clock switch status */
            uint8_t HPRE      :4; /* AHB prescaler */
            uint8_t PPRE1     :3; /* APB low-speed prescaler (APB1) */
            uint8_t PPRE2     :3; /* APB high-speed prescaler (APB2) */
            uint8_t ADCPRE    :2; /* ADC prescaler */
            uint8_t PLLSRC    :1; /* PLL entry clock source */
            uint8_t PLLXTPRE  :1; /* HSE divider for PLL entry */
            uint8_t PLLMUL    :4; /* PLL multiplication factor */
            uint8_t USBPRE    :1; /* USB prescaler */
            uint8_t MCO       :3; /* MicroController clock output */
            uint8_t           :5; /* Reserved  */
        };
        uint32_t registerVal; /* Clock configuration register */
    }CFGR; /* Clock configuration register */

    uint32_t RCC_CIR;
    uint32_t RCC_APB2RSTR;
    uint32_t RCC_APB1RSTR;
    uint32_t RCC_AHBENR;
    uint32_t RCC_APB2ENR;
    uint32_t RCC_APB1ENR;
    uint32_t RCC_BDCR;
    uint32_t RCC_CSR;
};

/**
 * @brief Clock configuration register
 */
#define RCC  (reinterpret_cast<volatile RccRegDef*>RCC_BASE_ADDRESS)

}  // namespace rcc
}  // namespace registers
}  // namespace stm32

#endif  // DEV_MCAL_INC_STM32F103XX_H_
