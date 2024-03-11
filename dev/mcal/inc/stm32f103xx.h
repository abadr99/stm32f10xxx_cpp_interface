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
            uint32_t HSION   :1; /* High-speed internal oscillator enable */
            uint32_t HSIRDY  :1; /* High-speed internal oscillator ready */
            uint32_t         :1; /* Reserved */
            uint32_t HSITRIM :5; /* High-speed internal oscillator trimming */
            uint32_t HSICAL  :8; /* High-speed internal oscillator calibration*/
            uint32_t HSEON   :1; /* High-speed external oscillator enable */
            uint32_t HSERDY  :1; /* High-speed external oscillator ready */
            uint32_t HSEBYP  :1; /* High-speed external oscillator bypass */
            uint32_t CSSON   :1; /* Clock security system enable */
            uint32_t         :4; /* Reserved */
            uint32_t PLLON   :1; /* Phase-locked loop enable */
            uint32_t PLLRDY  :1; /* Phase-locked loop ready */
        };
        uint32_t registerVal;   /** RCC control register  */
    }CR;

    union CFGR{
        struct {
            uint32_t SW        :2; /* System clock switch */
            uint32_t SWS       :2; /* System clock switch status */
            uint32_t HPRE      :4; /* AHB prescaler */
            uint32_t PPRE1     :3; /* APB low-speed prescaler (APB1) */
            uint32_t PPRE2     :3; /* APB high-speed prescaler (APB2) */
            uint32_t ADCPRE    :2; /* ADC prescaler */
            uint32_t PLLSRC    :1; /* PLL entry clock source */
            uint32_t PLLXTPRE  :1; /* HSE divider for PLL entry */
            uint32_t PLLMUL    :4; /* PLL multiplication factor */
            uint32_t USBPRE    :1; /* USB prescaler */
            uint32_t MCO       :3; /* MicroController clock output */
            uint32_t           :5; /* Reserved  */
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
