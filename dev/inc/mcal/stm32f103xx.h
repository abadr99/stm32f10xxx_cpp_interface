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

#ifndef DEV_INC_MCAL_STM32F103XX_H_
#define DEV_INC_MCAL_STM32F103XX_H_


#include "mcal/BaseAddress.h"

#include "mcal/Peripherals.h"
#include "utils/Types.h"

template<stm32::peripherals::Peripheral peripheralT>
using Addr = stm32::constant::Address<peripheralT>;

using Peripheral = stm32::peripherals::Peripheral;
using stm32::type::RegWidth_t;

namespace stm32 {
namespace registers {

namespace rcc {

/********************** RCC Register Definition  **********************/

struct RccRegDef {
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
    union APB2RSTR {
        struct {
            RegWidth_t AFIORST   :1; /* Alternative function clock enable  */
            RegWidth_t           :1; /* Reserved  */
            RegWidth_t IOPARST   :1; /* Port A clock enable  */
            RegWidth_t IOPBRST   :1; /* Port B clock enable  */
            RegWidth_t IOPCRST   :1; /* Port C clock enable  */
            RegWidth_t IOPDRST   :1; /* Port D clock enable  */
            RegWidth_t IOPERST   :1; /* Port E clock enable  */
            RegWidth_t           :2; /* Reserved  */
            RegWidth_t ADC1RST   :1; /* ADC 1 clock enable  */
            RegWidth_t ADC2RST   :1; /* ADC 2 clock enable  */
            RegWidth_t TIM1RST   :1; /* TIM1 clock enable  */
            RegWidth_t SPI1RST   :1; /* SPI1 clock enable  */
            RegWidth_t           :1; /* Reserved  */
            RegWidth_t USART1RST :1; /* USART1 clock enable  */
            RegWidth_t           :17; /* Reserved  */
        };
        RegWidth_t registerVal; /* APB1 peripheral Clock enable register */
    }APB2RSTR;

    union APB1RSTR {
        struct {
            RegWidth_t TIM2RST   :1; 
            RegWidth_t TIM3RST   :1; 
            RegWidth_t TIM4RST   :1; 
            RegWidth_t TIM5RST   :1; 
            RegWidth_t TIM6RST   :1; 
            RegWidth_t TIM7RST   :1; 
            RegWidth_t TIM12RST  :1; 
            RegWidth_t TIM13RST  :1; 
            RegWidth_t TIM14RST  :1;
            RegWidth_t WWDGRST   :1;
            RegWidth_t           :2;
            RegWidth_t SPI2RST   :1;
            RegWidth_t SPI3RST   :1;
            RegWidth_t USART2RST :1;
            RegWidth_t USART3RST :1;
            RegWidth_t USART4RST :1;
            RegWidth_t USART5RST :1; 
            RegWidth_t I2C1RST   :1; 
            RegWidth_t I2C2RST   :1; 
            RegWidth_t USBRST    :1; 
            RegWidth_t           :1; 
            RegWidth_t CANRST    :1; 
            RegWidth_t           :1; 
            RegWidth_t BKPRST    :1; 
            RegWidth_t PWRRST    :1; 
            RegWidth_t DACRST    :1; 
            RegWidth_t           :2; 
        };
        RegWidth_t registerVal; /* APB1 peripheral Clock enable register */
    }APB1RSTR;
    union AHBENR {
        struct {
            RegWidth_t DMA1EN     :1; 
            RegWidth_t DMA2EN     :1; 
            RegWidth_t SRAMEN     :1; 
            RegWidth_t            :1; 
            RegWidth_t FLITFEN    :1; 
            RegWidth_t            :1; 
            RegWidth_t CRCEN      :1; 
            RegWidth_t            :5; 
            RegWidth_t OTGFSEN    :1;
            RegWidth_t            :1;
            RegWidth_t ETHMACEN   :1;
            RegWidth_t ETHMACTXEN :1;
            RegWidth_t ETHMACRXEN :1;
        };
        RegWidth_t registerVal; /* APB1 peripheral Clock enable register */
    }AHBENR;
    union APB2ENR {
        struct {
            RegWidth_t AFIOEN   :1; /* Alternative function clock enable  */
            RegWidth_t          :1; /* Reserved  */
            RegWidth_t IOPAEN   :1; /* Port A clock enable  */
            RegWidth_t IOPBEN   :1; /* Port B clock enable  */
            RegWidth_t IOPCEN   :1; /* Port C clock enable  */
            RegWidth_t IOPDEN   :1; /* Port D clock enable  */
            RegWidth_t IOPEEN   :1; /* Port E clock enable  */
            RegWidth_t          :2; /* Reserved  */
            RegWidth_t ADC1EN   :1; /* ADC 1 clock enable  */
            RegWidth_t ADC2EN   :1; /* ADC 2 clock enable  */
            RegWidth_t TIM1EN   :1; /* TIM1 clock enable  */
            RegWidth_t SPI1EN   :1; /* SPI1 clock enable  */
            RegWidth_t          :1; /* Reserved  */
            RegWidth_t USART1EN :1; /* USART1 clock enable  */
            RegWidth_t          :17; /* Reserved  */
        };
        RegWidth_t registerVal; /* APB2 peripheral Clock enable register */
    }APB2ENR; /* APB2 peripheral Clock enable register */
    
    union APB1ENR {
        struct {
            RegWidth_t TIM2EN   :1; 
            RegWidth_t TIM3EN   :1; 
            RegWidth_t TIM4EN   :1; 
            RegWidth_t TIM5EN   :1; 
            RegWidth_t TIM6EN   :1; 
            RegWidth_t TIM7EN   :1; 
            RegWidth_t TIM12EN  :1; 
            RegWidth_t TIM13EN  :1; 
            RegWidth_t TIM14EN  :1;
            RegWidth_t WWDGEN   :1;
            RegWidth_t          :2;
            RegWidth_t SPI2EN   :1;
            RegWidth_t SPI3EN   :1;
            RegWidth_t USART2EN :1;
            RegWidth_t USART3EN :1;
            RegWidth_t USART4EN :1;
            RegWidth_t USART5EN :1; 
            RegWidth_t I2C1EN   :1; 
            RegWidth_t I2C2EN   :1; 
            RegWidth_t USBEN    :1; 
            RegWidth_t          :1; 
            RegWidth_t CANEN    :1; 
            RegWidth_t          :1; 
            RegWidth_t BKPEN    :1; 
            RegWidth_t PWREN    :1; 
            RegWidth_t DACEN    :1; 
            RegWidth_t          :2; 
        };
        RegWidth_t registerVal; /* APB1 peripheral Clock enable register */
    }APB1ENR;

    RegWidth_t BDCR;
    RegWidth_t CSR;
    union AHBRSTR {
        struct {
            RegWidth_t DMA1RST     :1; 
            RegWidth_t DMA2RST     :1; 
            RegWidth_t SRAMRST     :1; 
            RegWidth_t             :1; 
            RegWidth_t FLITFRST    :1; 
            RegWidth_t             :1; 
            RegWidth_t CRCRST      :1; 
            RegWidth_t             :5; 
            RegWidth_t OTGFSRST    :1;
            RegWidth_t             :1;
            RegWidth_t ETHMACRST   :1;
            RegWidth_t ETHMACTXRST :1;
            RegWidth_t ETHMACRXRST :1;
        };
        RegWidth_t registerVal; /* APB1 peripheral Clock enable register */
    }AHBRSTR;

    RegWidth_t CFGR2;
};

/**
 * @brief Clock configuration register
 */


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
}  // namespace gpio

namespace nvic {
/**
 * @brief Structure defining NVIC Register Definitions
 *
 * This structure defines the layout of NVIC registers for controlling
 */
struct NvicRegDef {
    RegWidth_t ISER[3];    // Interrupt Set Enable Registers
    RegWidth_t RES0[29];   // Reserved
    RegWidth_t ICER[3];    // Interrupt Clear Enable Registers
    RegWidth_t RES1[29];   // Reserved
    RegWidth_t ISPR[3];    // Interrupt Set Pending Registers
    RegWidth_t RES2[29];   // Reserved
    RegWidth_t ICPR[3];    // Interrupt Clear Pending Registers
    RegWidth_t RES3[29];   // Reserved
    RegWidth_t IABR[3];    // Interrupt Active Bit Registers
    RegWidth_t RES4[61];   // Reserved
    uint8_t    IPR[240];   // Interrupt Priority Registers
    RegWidth_t RES5[644];  // Reserved
    RegWidth_t STIR;       // Software Trigger Interrupt Register
};
struct  SCBRegDef {
    RegWidth_t CPUID;      // CPUID Base Register
    RegWidth_t ICSR;       // Interrupt Control and State Register
    RegWidth_t VTOR;       // Vector Table Offset Register
    RegWidth_t AIRCR;      // Application Interrupt and Reset Control Register
    union SCR {
        struct {
            RegWidth_t              :1;     // Reserved
            RegWidth_t SLEEPONEXIT  :1;
            RegWidth_t SLEEPDEEP    :1;
            RegWidth_t              :1;     // Reserved
            RegWidth_t SEVONPEND    :1;
            RegWidth_t              :27;     // Reserved
        };
        RegWidth_t registerVal;  //  Register value
    }SCR;   // System Control Register
    RegWidth_t CCR;        // Configuration and Control Register
    RegWidth_t SHP[12];    // System Handlers Priority Registers
    RegWidth_t SHCSR;      // System Handler Control and State Register
    RegWidth_t CFSR;       // Configurable Fault Status Register
    RegWidth_t HFSR;       // HardFault Status Register
    RegWidth_t MMFAR;      // MemManage Fault Address Register
    RegWidth_t BFAR;       // BusFault Address Register
};
}  // namespace nvic

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

    RegWidth_t EXTICRx[4];  // External interrupt configuration register x

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

// define AFIO (reinterpret_cast<volatile AfioRegDef*>(Addr<Peripheral::kAFIO >::kBaseAddr))

}  // namespace afio
namespace systick {
struct SystickRegDef {
    union CTRL {
        struct {
            RegWidth_t ENABLE   :1;   // Counter enable
            RegWidth_t TICKINT  :1;   // SysTick exception request enable
            RegWidth_t CLKSOURCE:1;   // Clock source selection
            RegWidth_t          :13;  // Reserved
            RegWidth_t COUNTFLAG:1;   // Counter flag
            RegWidth_t          :15;  // Reserved
        };
        RegWidth_t registerVal;  // CTRL
    }CTRL;

    RegWidth_t LOAD;  // Reload value
    RegWidth_t VAL;   // Current value
};

}  // namespace systick
namespace spi {
struct SpiRegDef {
    union CR1 {
        struct {
            RegWidth_t CPHA      : 1;   //  Clock Phase
            RegWidth_t CPOL      : 1;   //  Clock Polarity
            RegWidth_t MSTR      : 1;   //  Master Selection
            RegWidth_t BR        : 3;   //  Baud Rate Control
            RegWidth_t SPE       : 1;   //  SPI Enable
            RegWidth_t LSBFIRST  : 1;   //  Frame Format
            RegWidth_t SSI       : 1;   //  Internal Slave Select
            RegWidth_t SSM       : 1;   //  Software Slave Management
            RegWidth_t RXONLY    : 1;   //  Receive Only
            RegWidth_t DFF       : 1;   //  Data Frame Format
            RegWidth_t CRCNEXT   : 1;   //  Transmit CRC Next
            RegWidth_t CRCEN     : 1;   //  Hardware CRC Calculation Enable
            RegWidth_t BIDIOE    : 1;   //  Output Enable in Bidirectional Mode
            RegWidth_t BIDIMODE  : 1;   //  Bidirectional Data Mode Enable
            RegWidth_t           : 16;  //  Reserved
        };
        RegWidth_t registerVal;  //  CR1
    }CR1;
    union CR2 {
        struct {
            RegWidth_t RXDMAEN    :1;   //  Rx buffer DMA enable
            RegWidth_t TXDMAEN    :1;   //  Tx buffer DMA enable
            RegWidth_t SSOE       :1;   //  SS output enable
            RegWidth_t            :2;   //  Reserved
            RegWidth_t ERRIE      :1;   //  Error interrupt enable
            RegWidth_t RXNEIE     :1;   //  RX buffer not empty interrupt enable
            RegWidth_t TXEIE      :1;   //  TX buffer empty interrupt enable
            RegWidth_t            :24;   //  Reserved bits 15:8
        };
        RegWidth_t registerVal;  //  CR2
    }CR2;
    union SR {
        struct {
            RegWidth_t RXNE       :1;   //  Receive buffer not empty
            RegWidth_t TXE        :1;   //  Transmit buffer empty
            RegWidth_t CHSIDE     :1;   //  Channel side
            RegWidth_t UDR        :1;   //  Underrun flag
            RegWidth_t CRCERR     :1;   //  CRC error flag
            RegWidth_t MODF       :1;   //  Mode fault
            RegWidth_t OVR        :1;   //  Overrun flag
            RegWidth_t BSY        :1;   //  Busy flag
            RegWidth_t            :24;   //  Reserved bits 15:8
        };
        RegWidth_t registerVal;  // SR
    }SR;
    RegWidth_t DR;
    RegWidth_t CRC;
    RegWidth_t RXCRCR;
    RegWidth_t TXCRCR;
};
}  // namespace spi
namespace usart {

struct UsartRegDef {
    union SR {
        struct {
            RegWidth_t PE   : 1;
            RegWidth_t FE   : 1;
            RegWidth_t NE   : 1;
            RegWidth_t ORE  : 1;
            RegWidth_t IDEL : 1;
            RegWidth_t RXNE : 1;
            RegWidth_t TC   : 1;
            RegWidth_t TXE  : 1;
            RegWidth_t LBD  : 1;
            RegWidth_t CTS  : 1;
            RegWidth_t      : 22;
        };
        RegWidth_t registerVal;
    }SR;

    RegWidth_t DR;

    union BRR {
        struct {
            RegWidth_t DIV_Fraction : 4;
            RegWidth_t DIV_Mantissa : 12;
            RegWidth_t              : 16;
        };
        RegWidth_t registerVal;
    }BRR;

    union CR1 {
        struct {
            RegWidth_t SBK    : 1;
            RegWidth_t RWU    : 1;
            RegWidth_t RE_TE  : 2;
            RegWidth_t IDELIE : 1;
            RegWidth_t RXNEIE : 1;
            RegWidth_t TCIE   : 1;
            RegWidth_t TXEIE  : 1;
            RegWidth_t PEIE   : 1;
            RegWidth_t PS_PCE : 2;
            RegWidth_t WAKE   : 1;
            RegWidth_t M      : 1;
            RegWidth_t UE     : 1;
            RegWidth_t        : 18;
        };
        RegWidth_t registerVal;
    }CR1;

    union CR2 {
        struct {
            RegWidth_t ADD    : 4;
            RegWidth_t        : 1;
            RegWidth_t LBDL   : 1;
            RegWidth_t LBDLIE : 1;
            RegWidth_t        : 1;
            RegWidth_t LBCL   : 1;
            RegWidth_t CPHA   : 1;
            RegWidth_t CPOL   : 1;
            RegWidth_t CLKEN  : 1;
            RegWidth_t STOP   : 2;
            RegWidth_t LINEN  : 1;
            RegWidth_t        : 17;
        };
        RegWidth_t registerVal;
    }CR2;

    union CR3 {
        struct {
            RegWidth_t EIE        : 1;
            RegWidth_t IREN       : 1;
            RegWidth_t IRLP       : 1;
            RegWidth_t HDSEL      : 1;
            RegWidth_t NACK       : 1;
            RegWidth_t SCEN       : 1;
            RegWidth_t DMAR       : 1;
            RegWidth_t DMAT       : 1;
            RegWidth_t RTSE_CTSE  : 2;
            RegWidth_t CTSIE      : 1;
            RegWidth_t            : 21;
        };
        RegWidth_t registerVal;
    }CR3;
    RegWidth_t GTPR;
};
}  // namespace usart

/**
 * @brief Structure defining EXTI Register Definitions
 * 
 */
namespace exti {
struct EXTIRegDef {
    RegWidth_t IMR;    // Interrupt mask register
    RegWidth_t EMR;    // Event mask register
    RegWidth_t RTSR;   // Rising trigger selection register
    RegWidth_t FTSR;   // Falling trigger selection register
    RegWidth_t SWIER;  // Software interrupt event register
    RegWidth_t PR;     // Pending register
};
}  // namespace exti
namespace wwdg {
struct WWDGRegDef {
    union CR {
        struct {
            RegWidth_t T     : 7;   // 7-bit counter (MSB to LSB)
            RegWidth_t WDGA  : 1;   // Activation bit
            RegWidth_t       : 24;  // Reserved
        };
        RegWidth_t registerVal;
    } CR;

    union CFR {
        struct {
            RegWidth_t W     : 7;   // 7-bit window value
            RegWidth_t WDGTB : 2;   // Timer Base
            RegWidth_t EWI   : 1;   // Early Wakeup Interrupt
            RegWidth_t       : 22;  // Reserved
        };
        RegWidth_t registerVal;
    } CFR;

    union SR {
        struct {
            RegWidth_t EWIF  : 1;   // Early Wakeup Interrupt Flag
            RegWidth_t       : 31;  // Reserved
        };
        RegWidth_t registerVal;
    } SR;
};
}  // namespace wwdg

namespace rtc {

struct RtcRegDef {
    union CRL {
        struct {
            RegWidth_t SECF     : 1;    // Second flag
            RegWidth_t ALRF     : 1;    // Alarm flag
            RegWidth_t OWF      : 1;    // Overflow flag
            RegWidth_t RSF      : 1;    // Registers synchronized flag
            RegWidth_t CNF      : 1;    // Configuration flag
            RegWidth_t RTOFF    : 1;    // RTC operation OFF flag
            RegWidth_t reserved : 26;   // Reserved bits
        };
        RegWidth_t registerVal;
    } CRL;
    
    union CRH {
        struct {
            RegWidth_t SECIE    : 1;   // Second interrupt enable
            RegWidth_t ALRIE    : 1;   // Alarm interrupt enable
            RegWidth_t OWIE     : 1;   // Overflow interrupt enable
            RegWidth_t reserved : 29;  // Reserved bits
        };
        RegWidth_t registerVal;
    } CRH;
    
    union PRLH {
        struct {
            RegWidth_t PRL      : 4;    // RTC Prescaler Load Register High
            RegWidth_t reserved : 28;   // Reserved bits
        };
        RegWidth_t registerVal;
    } PRLH;
    
    union PRLL {
        struct {
            RegWidth_t PRL      : 16;   // RTC Prescaler Load Register Low
            RegWidth_t reserved : 16;   // Reserved bits
        };
        RegWidth_t registerVal;
    } PRLL;
    
    union DIVH {
        struct {
            RegWidth_t DIV      :  4;   // RTC Clock Divider High
            RegWidth_t reserved : 28;   // Reserved bits
        };
        RegWidth_t registerVal;
    } DIVH;
    
    union DIVL {
        struct {
            RegWidth_t DIV      : 16;   // RTC Clock Divider Low
            RegWidth_t reserved : 16;   // Reserved bits
        };
        RegWidth_t registerVal;
    } DIVL;
    
    union CNTH {
        struct {
            RegWidth_t CNT      : 16;    // RTC Counter Register High
            RegWidth_t reserved : 16;    // Reserved bits
        };
        RegWidth_t registerVal;
    } CNTH;
    
    union CNTL {
        struct {
            RegWidth_t CNT      : 16;    // RTC Counter Register Low
            RegWidth_t reserved : 16;    // Reserved bits
        };
        RegWidth_t registerVal;
    } CNTL;
    
    union ALRH {
        struct {
            RegWidth_t ALR      : 16;    // RTC Alarm Register High
            RegWidth_t reserved : 16;    // Reserved bits
        };
        RegWidth_t registerVal;
    } ALRH;
    
    union ALRL {
        struct {
            RegWidth_t ALR      : 16;    // RTC Alarm Register Low
            RegWidth_t reserved : 16;    // Reserved bits
        };
        RegWidth_t registerVal;
    } ALRL;
};

}  // namespace rtc

namespace adc {

struct ADCRegDef {
        union SR {
        struct {
            RegWidth_t AWD   : 1;
            RegWidth_t EOC   : 1;
            RegWidth_t JEOC  : 1;
            RegWidth_t JSTRT : 1;
            RegWidth_t STRT  : 1;
            RegWidth_t       : 27;
        };
        RegWidth_t registerVal;
    } SR;

    union CR1 {
        struct {
            RegWidth_t AWDCH  : 5;
            RegWidth_t EOCIE  : 1;
            RegWidth_t AWDIE  : 1;
            RegWidth_t JEOCIE : 1;
            RegWidth_t SCAN   : 1;
            RegWidth_t AWDSGL : 1;
            RegWidth_t JAUTO  : 1;
            RegWidth_t DISCEN : 1;
            RegWidth_t JDISCEN: 1;
            RegWidth_t DISCNUM: 3;
            RegWidth_t DUALMOD: 4;
            RegWidth_t        : 2;
            RegWidth_t JAWDEN : 1;
            RegWidth_t AWDEN  : 1;
            RegWidth_t        : 8;
        };
        RegWidth_t registerVal;
    }CR1;

    union CR2 {
        struct {
            RegWidth_t ADON   : 1;
            RegWidth_t CONT   : 1;
            RegWidth_t CAL    : 1;
            RegWidth_t RSTCAL : 1;
            RegWidth_t        : 4;
            RegWidth_t DMA    : 1;
            RegWidth_t        : 2;
            RegWidth_t ALIGN  : 1;
            RegWidth_t JEXTSEL: 3;
            RegWidth_t JEXTTRIG: 1;
            RegWidth_t        : 1;
            RegWidth_t EXTSEL : 3;
            RegWidth_t EXTTRIG: 1;
            RegWidth_t JSWSTART: 1;
            RegWidth_t SWSTART: 1;
            RegWidth_t TSVREFE: 1;
            RegWidth_t        : 8;
        };
        RegWidth_t registerVal;
    }CR2;
    union SMPR1 {
        struct {
            RegWidth_t SMP10 : 3;
            RegWidth_t SMP11 : 3;
            RegWidth_t SMP12 : 3;
            RegWidth_t SMP13 : 3;
            RegWidth_t SMP14 : 3;
            RegWidth_t SMP15 : 3;
            RegWidth_t SMP16 : 3;
            RegWidth_t SMP17 : 3;
            RegWidth_t       : 8;
        };
        RegWidth_t registerVal;
    }SMPR1;

    union SMPR2 {
        struct {
            RegWidth_t SMP0  : 3;
            RegWidth_t SMP1  : 3;
            RegWidth_t SMP2  : 3;
            RegWidth_t SMP3  : 3;
            RegWidth_t SMP4  : 3;
            RegWidth_t SMP5  : 3;
            RegWidth_t SMP6  : 3;
            RegWidth_t SMP7  : 3;
            RegWidth_t SMP8  : 3;
            RegWidth_t SMP9  : 3;
            RegWidth_t       : 2;
        };
        RegWidth_t registerVal;
    }SMPR2;
    RegWidth_t JOFR1;   // Injected Channel Data Offset Register 1
    RegWidth_t JOFR2;   // Injected Channel Data Offset Register 2
    RegWidth_t JOFR3;   // Injected Channel Data Offset Register 3
    RegWidth_t JOFR4;   // Injected Channel Data Offset Register 4
    RegWidth_t HTR;     // Watchdog Higher Threshold Register
    RegWidth_t LTR;     // Watchdog Lower Threshold Register
    union SQR1 {
        struct {
            RegWidth_t SQ13 : 5;
            RegWidth_t SQ14 : 5;
            RegWidth_t SQ15 : 5;
            RegWidth_t SQ16 : 5;
            RegWidth_t L    : 4;
            RegWidth_t      : 8;
        };
        RegWidth_t registerVal;
    }SQR1;
    RegWidth_t SQR2;    // Regular Sequence Register 2
    RegWidth_t SQR3;    // Regular Sequence Register 3
    union JSQR {
        struct {
            RegWidth_t JSQ1 : 5;
            RegWidth_t JSQ2 : 5;
            RegWidth_t JSQ3 : 5;
            RegWidth_t JSQ4 : 5;
            RegWidth_t JL   : 2;
            RegWidth_t      : 10;
        };
        RegWidth_t registerVal;
    }JSQR;
    union JDR1 {
        struct {
            RegWidth_t JDATA : 16;
            RegWidth_t       : 16;
        };
        RegWidth_t registerVal;
    }JDR1;
    RegWidth_t JDR2;    // Injected Data Register 2
    RegWidth_t JDR3;    // Injected Data Register 3
    RegWidth_t JDR4;    // Injected Data Register 4
    union DR {
        struct {
            RegWidth_t DATA : 16;
            RegWidth_t      : 16;
        };
        RegWidth_t registerVal;
    }DR;
};
}  // namespace adc

namespace i2c {
struct I2CRegDef {
        union CR1 {
            struct {
                RegWidth_t PE          : 1;   // Peripheral enable
                RegWidth_t SMBUS       : 1;   // SMBus mode
                RegWidth_t             : 1;   // Reserved
                RegWidth_t SMBTYPE     : 1;   // SMBus type
                RegWidth_t ENARP       : 1;   // ARP enable
                RegWidth_t ENPEC       : 1;   // PEC enable
                RegWidth_t ENGC        : 1;   // General call enable
                RegWidth_t NOSTRETCH   : 1;   // Clock stretching disable
                RegWidth_t START       : 1;   // Start generation
                RegWidth_t STOP        : 1;   // Stop generation
                RegWidth_t ACK         : 1;   // Acknowledge enable
                RegWidth_t POS         : 1;   // Acknowledge/PEC position (for data reception)
                RegWidth_t PEC         : 1;   // Packet error checking
                RegWidth_t ALERT       : 1;   // SMBus alert
                RegWidth_t             : 1;   // Reserved
                RegWidth_t SWRST       : 1;   // Software reset
                RegWidth_t             : 16;  // Reserved
            };
            RegWidth_t registerVal;
        }CR1;
        union CR2 {
            struct {
                RegWidth_t FREQ        : 6;   // Peripheral clock frequency
                RegWidth_t RESERVED    : 2;   // Reserved
                RegWidth_t ITERREN     : 1;   // Error interrupt enable
                RegWidth_t ITEVTEN     : 1;   // Event interrupt enable
                RegWidth_t ITBUFEN     : 1;   // Buffer interrupt enable
                RegWidth_t DMAEN       : 1;   // DMA requests enable
                RegWidth_t LAST        : 1;   // DMA last transfer
                RegWidth_t             : 19;  // Reserved
            };
            RegWidth_t registerVal;
        }CR2;
        union OAR1 {
            struct {
                RegWidth_t ADD0        : 1;   // Interface address
                RegWidth_t ADD         : 9;   // Interface address
                RegWidth_t             : 5;   // Reserved
                RegWidth_t ADDMODE     : 1;   // Addressing mode (7-bit/10-bit)
                RegWidth_t             : 16;  // Reserved
            };
            RegWidth_t registerVal;
        }OAR1;
        union OAR2 {
            struct {
                RegWidth_t ENDUAL      : 1;  // Dual addressing mode enable
                RegWidth_t ADD2        : 7;  // Interface address
                RegWidth_t             : 24;  // Reserved
            };
            RegWidth_t registerVal;
        }OAR2;

        RegWidth_t DR;  // 8-bit data register

        union SR1 {
            struct {
                RegWidth_t SB          : 1;   // Start bit (Master mode)
                RegWidth_t ADDR        : 1;   // Address sent (master mode)/matched (slave mode)
                RegWidth_t BTF         : 1;   // Byte transfer finished
                RegWidth_t ADD10       : 1;   // 10-bit header sent (Master mode)
                RegWidth_t STOPF       : 1;   // Stop detection (Slave mode)
                RegWidth_t             : 1;   // Reserved
                RegWidth_t RxNE        : 1;   // Data register not empty (receivers)
                RegWidth_t TxE         : 1;   // Data register empty (transmitters)
                RegWidth_t BERR        : 1;   // Bus error
                RegWidth_t ARLO        : 1;   // Arbitration lost (master mode)
                RegWidth_t AF          : 1;   // Acknowledge failure
                RegWidth_t OVR         : 1;   // Overrun/underrun
                RegWidth_t PECERR      : 1;   // PEC error in reception
                RegWidth_t             : 1;   // Reserved
                RegWidth_t TIMEOUT     : 1;   // Timeout or Tlow detection flag
                RegWidth_t SMBALERT    : 1;   // SMBus alert
                RegWidth_t             : 16;   // Reserved
            };
            RegWidth_t registerVal;
        }SR1;
        union SR2 {
            struct {
                RegWidth_t MSL         : 1;   // Master/slave
                RegWidth_t BUSY        : 1;   // Bus busy
                RegWidth_t TRA         : 1;   // Transmitter/receiver
                RegWidth_t             : 1;   // Reserved bits
                RegWidth_t GENCALL     : 1;   // General call address (Slave mode)
                RegWidth_t SMBDEFAULT  : 1;   // SMBus device default address (Slave mode)
                RegWidth_t SMBHOST     : 1;   // SMBus host header (Slave mode)
                RegWidth_t DUALF       : 1;   // Dual flag (Slave mode)
                RegWidth_t PEC         : 8;   // Packet error checking
                RegWidth_t             : 16;  // Reserved
            };
            RegWidth_t registerVal;
        }SR2;
        union CCR {
            struct {
                RegWidth_t CcR         : 12;  // Clock control register in Fast/Standard mode
                RegWidth_t             : 2;   // Reserved 
                RegWidth_t DUTY        : 1;   // Fm mode duty cycle
                RegWidth_t F_S         : 1;   // I2C master mode selection
                RegWidth_t             : 16;  // Reserved
            };
            RegWidth_t registerVal;
        }CCR;
        
        RegWidth_t TRISE;
};
}  // namespace i2c

/**
 * @brief Structure defining DMA Register Definitions
 * 
 */
namespace dma {
struct DmaChannel {
    union CCR {
        struct {
            RegWidth_t EN           : 1;  // Channel enable
            RegWidth_t TCIE         : 1;  // Transfer complete interrupt enable
            RegWidth_t HTIE         : 1;  // Half transfer interrupt enable
            RegWidth_t TEIE         : 1;  // Transfer error interrupt enable
            RegWidth_t DIR          : 1;  // Data transfer direction
            RegWidth_t CIRC         : 1;  // Circular mode
            RegWidth_t PINC         : 1;  // Peripheral increment mode
            RegWidth_t MINC         : 1;  // Memory increment mode
            RegWidth_t PSIZE        : 2;  // Peripheral size
            RegWidth_t MSIZE        : 2;  // Memory size
            RegWidth_t PL           : 2;  // Channel priority level
            RegWidth_t MEM2MEM      : 1;  // Memory-to-memory mode
            RegWidth_t RESERVED     : 17;  // Reserved, must be kept at reset value
        };
        RegWidth_t registerVal;
    }CCR;       // DMA channel x configuration register

    RegWidth_t CNDTR;    // DMA channel x number of data register
    RegWidth_t CPAR;    // DMA channel x peripheral address register
    RegWidth_t CMAR;    // DMA channel x memory address register
};
struct DMARegDef {
    union ISR {
        struct  {
            RegWidth_t GIF1   : 1;   //  Global interrupt flag for channel 1
            RegWidth_t TCIF1  : 1;   //  Transfer complete flag for channel 1
            RegWidth_t HTIF1  : 1;   //  Half transfer flag for channel 1
            RegWidth_t TEIF1  : 1;   //  Transfer error flag for channel 1
            RegWidth_t GIF2   : 1;   //  Global interrupt flag for channel 2
            RegWidth_t TCIF2  : 1;   //  Transfer complete flag for channel 2
            RegWidth_t HTIF2  : 1;   //  Half transfer flag for channel 2
            RegWidth_t TEIF2  : 1;   //  Transfer error flag for channel 2
            RegWidth_t GIF3   : 1;   //  Global interrupt flag for channel 3
            RegWidth_t TCIF3  : 1;   //  Transfer complete flag for channel 3
            RegWidth_t HTIF3  : 1;   //  Half transfer flag for channel 3
            RegWidth_t TEIF3  : 1;   //  Transfer error flag for channel 3
            RegWidth_t GIF4   : 1;   //  Global interrupt flag for channel 4
            RegWidth_t TCIF4  : 1;   //  Transfer complete flag for channel 4
            RegWidth_t HTIF4  : 1;   //  Half transfer flag for channel 4
            RegWidth_t TEIF4  : 1;   //  Transfer error flag for channel 4
            RegWidth_t GIF5   : 1;   //  Global interrupt flag for channel 5
            RegWidth_t TCIF5  : 1;   //  Transfer complete flag for channel 5
            RegWidth_t HTIF5  : 1;   //  Half transfer flag for channel 5
            RegWidth_t TEIF5  : 1;   //  Transfer error flag for channel 5
            RegWidth_t GIF6   : 1;   //  Global interrupt flag for channel 6
            RegWidth_t TCIF6  : 1;   //  Transfer complete flag for channel 6
            RegWidth_t HTIF6  : 1;   //  Half transfer flag for channel 6
            RegWidth_t TEIF6  : 1;   //  Transfer error flag for channel 6
            RegWidth_t GIF7   : 1;   //  Global interrupt flag for channel 7
            RegWidth_t TCIF7  : 1;   //  Transfer complete flag for channel 7
            RegWidth_t HTIF7  : 1;   //  Half transfer flag for channel 7
            RegWidth_t TEIF7  : 1;   //  Transfer error flag for channel 7
            RegWidth_t RESERVED : 4;  //  Reserved, must be kept at reset value
        };
        RegWidth_t registerVal;
    }ISR;   // DMA interrupt status register
    
    
    union IFCR {
        struct {
            RegWidth_t CGIF1  : 1;   //  Clear global interrupt flag for channel 1
            RegWidth_t CTCIF1 : 1;   //  Clear transfer complete flag for channel 1
            RegWidth_t CHTIF1 : 1;   //  Clear half transfer flag for channel 1
            RegWidth_t CTEIF1 : 1;   //  Clear transfer error flag for channel 1
            RegWidth_t CGIF2  : 1;   //  Clear global interrupt flag for channel 2
            RegWidth_t CTCIF2 : 1;   //  Clear transfer complete flag for channel 2
            RegWidth_t CHTIF2 : 1;   //  Clear half transfer flag for channel 2
            RegWidth_t CTEIF2 : 1;   //  Clear transfer error flag for channel 2
            RegWidth_t CGIF3  : 1;   //  Clear global interrupt flag for channel 3
            RegWidth_t CTCIF3 : 1;   //  Clear transfer complete flag for channel 3
            RegWidth_t CHTIF3 : 1;   //  Clear half transfer flag for channel 3
            RegWidth_t CTEIF3 : 1;   //  Clear transfer error flag for channel 3
            RegWidth_t CGIF4  : 1;   //  Clear global interrupt flag for channel 4
            RegWidth_t CTCIF4 : 1;   //  Clear transfer complete flag for channel 4
            RegWidth_t CHTIF4 : 1;   //  Clear half transfer flag for channel 4
            RegWidth_t CTEIF4 : 1;   //  Clear transfer error flag for channel 4
            RegWidth_t CGIF5  : 1;   //  Clear global interrupt flag for channel 5
            RegWidth_t CTCIF5 : 1;   //  Clear transfer complete flag for channel 5
            RegWidth_t CHTIF5 : 1;   //  Clear half transfer flag for channel 5
            RegWidth_t CTEIF5 : 1;   //  Clear transfer error flag for channel 5
            RegWidth_t CGIF6  : 1;   //  Clear global interrupt flag for channel 6
            RegWidth_t CTCIF6 : 1;   //  Clear transfer complete flag for channel 6
            RegWidth_t CHTIF6 : 1;   //  Clear half transfer flag for channel 6
            RegWidth_t CTEIF6 : 1;   //  Clear transfer error flag for channel 6
            RegWidth_t CGIF7  : 1;   //  Clear global interrupt flag for channel 7
            RegWidth_t CTCIF7 : 1;   //  Clear transfer complete flag for channel 7
            RegWidth_t CHTIF7 : 1;   //  Clear half transfer flag for channel 7
            RegWidth_t CTEIF7 : 1;   //  Clear transfer error flag for channel 7
            RegWidth_t RESERVED : 4;  //  Reserved, must be kept at reset value
        }; 
        RegWidth_t registerVal;
    }IFCR;  // DMA interrupt flag clear register
    DmaChannel CHANNEL[7];  // DMA channels 1-7
};
}  // namespace dma

namespace timer {
struct timerRegDef {
    union CR1 {
        struct {
            RegWidth_t CEN  : 1;    // Counter Enable
            RegWidth_t UDIS : 1;   // Update Disable
            RegWidth_t URS  : 1;    // Update Request Source
            RegWidth_t OPM  : 1;    // One Pulse Mode
            RegWidth_t DIR  : 1;    // Direction
            RegWidth_t CMS  : 2;    // Center-aligned Mode Selection
            RegWidth_t ARPE : 1;   // Auto-Reload Preload Enable
            RegWidth_t CKD  : 2;    // Clock Division
            RegWidth_t Reserved : 22;  // Reserved bits
        };
        RegWidth_t registerVal;
    }CR1;
    union CR2 {
    struct {
        RegWidth_t CCPC : 1;  // Capture/Compare Preloaded Control
        RegWidth_t      : 1;  // Reserved
        RegWidth_t CCUS : 1;  // Capture/Compare Control Update Selection
        RegWidth_t CCDS : 1;  // Capture/Compare DMA Selection
        RegWidth_t MMS  : 3;  // Master Mode Selection
        RegWidth_t TI1S : 1;  // TI1 Selection
        RegWidth_t OIS1 : 1;  // Output Idle State 1 (OC1 output)
        RegWidth_t OIS1N: 1;  // Output Idle State 1 (OC1N output)
        RegWidth_t OIS2 : 1;  // Output Idle State 2 (OC2 output)
        RegWidth_t OIS2N: 1;  // Output Idle State 2 (OC2N output)
        RegWidth_t OIS3 : 1;  // Output Idle State 3 (OC3 output)
        RegWidth_t OIS3N: 1;  // Output Idle State 3 (OC3N output)
        RegWidth_t OIS4 : 1;  // Output Idle State 4 (OC4 output)
        RegWidth_t Reserved : 17;  // Reserved bits
    };
    RegWidth_t registerVal;
    } CR2;
    union SMCR {
    struct {
        RegWidth_t SMS  : 3;   // Slave Mode Selection
        RegWidth_t      : 1;  // Reserved
        RegWidth_t OCCS : 1;   // OCREF Clear Selection
        RegWidth_t TS   : 3;   // Trigger Selection
        RegWidth_t MSM  : 1;   // Master/Slave Mode
        RegWidth_t ETF  : 4;   // External Trigger Filter
        RegWidth_t ETPS : 2;   // External Trigger Prescaler
        RegWidth_t ECE  : 1;   // External Clock Enable
        RegWidth_t Reserved : 16;  // Reserved bits
    };
    RegWidth_t registerVal;
    } SMCR;
    union DIER {
    struct {
        RegWidth_t UIE  : 1;   // Update Interrupt Enable
        RegWidth_t CC1IE: 1;   // Capture/Compare 1 Interrupt Enable
        RegWidth_t CC2IE: 1;   // Capture/Compare 2 Interrupt Enable
        RegWidth_t CC3IE: 1;   // Capture/Compare 3 Interrupt Enable
        RegWidth_t CC4IE: 1;   // Capture/Compare 4 Interrupt Enable
        RegWidth_t TIE  : 1;   // Trigger Interrupt Enable
        RegWidth_t BIE  : 1;   // Break Interrupt Enable
        RegWidth_t Reserved : 25;  // Reserved bits
    };
    RegWidth_t registerVal;
    } DIER;
    union SR {
    struct {
        RegWidth_t UIF  : 1;   // Update Interrupt Flag
        RegWidth_t CC1IF: 1;   // Capture/Compare 1 Interrupt Flag
        RegWidth_t CC2IF: 1;   // Capture/Compare 2 Interrupt Flag
        RegWidth_t CC3IF: 1;   // Capture/Compare 3 Interrupt Flag
        RegWidth_t CC4IF: 1;   // Capture/Compare 4 Interrupt Flag
        RegWidth_t COMIF: 1;   // Reserved bit
        RegWidth_t TIF  : 1;   // Trigger Interrupt Flag
        RegWidth_t BIF  : 1;   // Break Interrupt Flag
        RegWidth_t      : 1;   // Reserved bits
        RegWidth_t CC1OF: 1;   // Capture/Compare 1 Overcapture Flag
        RegWidth_t CC2OF: 1;   // Capture/Compare 2 Overcapture Flag
        RegWidth_t CC3OF: 1;   // Capture/Compare 3 Overcapture Flag
        RegWidth_t CC4OF: 1;   // Capture/Compare 4 Overcapture Flag
        RegWidth_t Reserved3 : 19;  // Reserved bits
    };
    RegWidth_t registerVal;
    } SR;
    union EGR {
    struct {
        RegWidth_t UG   : 1;   // Update Generation
        RegWidth_t CC1G : 1;   // Capture/Compare 1 Generation
        RegWidth_t CC2G : 1;   // Capture/Compare 2 Generation
        RegWidth_t CC3G : 1;   // Capture/Compare 3 Generation
        RegWidth_t CC4G : 1;   // Capture/Compare 4 Generation
        RegWidth_t TG   : 1;   // Trigger Generation
        RegWidth_t BG   : 1;   // Break Generation
        RegWidth_t Reserved : 25;  // Reserved bits
    };
    RegWidth_t registerVal;
    } EGR;
    union CCMR1 {
    struct {
        RegWidth_t CC1S  : 2;  // Capture/Compare 1 Selection
        RegWidth_t IC1PSC: 2;  // Input Capture 1 Prescaler
        RegWidth_t IC1F  : 4;  // Input Capture 1 Filter
        RegWidth_t CC2S  : 2;  // Capture/Compare 2 Selection
        RegWidth_t IC2PSC: 2;  // Input Capture 2 Prescaler
        RegWidth_t IC2F  : 4;  // Input Capture 2 Filter
        RegWidth_t Reserved : 16;  // Reserved bits
    };
    RegWidth_t registerVal;
    } CCMR1;
    union CCMR2 {
    struct {
        RegWidth_t CC3S  : 2;  // Capture/Compare 3 Selection
        RegWidth_t IC3PSC: 2;  // Input Capture 3 Prescaler
        RegWidth_t IC3F  : 4;  // Input Capture 3 Filter
        RegWidth_t CC4S  : 2;  // Capture/Compare 4 Selection
        RegWidth_t IC4PSC: 2;  // Input Capture 4 Prescaler
        RegWidth_t IC4F  : 4;  // Input Capture 4 Filter
        RegWidth_t Reserved : 16;  // Reserved bits
    };
    RegWidth_t registerVal;
    } CCMR2;
    union CCER {
    struct {
        RegWidth_t CC1E : 1;  // Capture/Compare 1 Output Enable
        RegWidth_t CC1P : 1;  // Capture/Compare 1 Output Polarity
        RegWidth_t CC1NE: 1;  // Capture/Compare 1N Output Enable
        RegWidth_t CC1NP: 1;  // Capture/Compare 1N Output Polarity
        RegWidth_t CC2E : 1;  // Capture/Compare 2 Output Enable
        RegWidth_t CC2P : 1;  // Capture/Compare 2 Output Polarity
        RegWidth_t CC2NE: 1;  // Capture/Compare 2N Output Enable
        RegWidth_t CC2NP: 1;  // Capture/Compare 2N Output Polarity
        RegWidth_t CC3E : 1;  // Capture/Compare 3 Output Enable
        RegWidth_t CC3P : 1;  // Capture/Compare 3 Output Polarity
        RegWidth_t CC3NE: 1;  // Capture/Compare 3N Output Enable
        RegWidth_t CC3NP: 1;  // Capture/Compare 3N Output Polarity
        RegWidth_t CC4E : 1;  // Capture/Compare 4 Output Enable
        RegWidth_t CC4P : 1;  // Capture/Compare 4 Output Polarity
        RegWidth_t      : 1;  // Reserved  
        RegWidth_t CC4NP : 1;  // Capture/Compare 4 Output Polarity
        RegWidth_t Reserved : 16;  // Reserved bits
    };
    RegWidth_t registerVal;
    } CCER;
    RegWidth_t CNT;
    RegWidth_t PSC;
    RegWidth_t ARR;
    RegWidth_t RCR;
    RegWidth_t CCR1;
    RegWidth_t CCR2;
    RegWidth_t CCR3;
    RegWidth_t CCR4;
    union BDTR {
    struct {
        RegWidth_t DTG   : 8;  // Dead-Time Generator Set-up
        RegWidth_t LOCK  : 2;  // Lock Configuration
        RegWidth_t OSSI  : 1;  // Off-State Selection for Idle mode
        RegWidth_t OSSR  : 1;  // Off-State Selection for Run mode
        RegWidth_t BKE   : 1;  // Break Enable
        RegWidth_t BKP   : 1;  // Break Polarity
        RegWidth_t AOE   : 1;  // Automatic Output Enable
        RegWidth_t MOE   : 1;  // Main Output Enable
        RegWidth_t Reserved : 16;  // Reserved bits
    };
    RegWidth_t registerVal;
    } BDTR;
    union DCR {
    struct {
        RegWidth_t DBA   : 5;  // DMA Base Address
        RegWidth_t       : 3;  // Reserved
        RegWidth_t DBL   : 5;  // DMA Buffer Size
        RegWidth_t Reserved : 19;  // Reserved bits
    };
    RegWidth_t registerVal;
    } DCR;
    RegWidth_t DMAR;
};
}  // namespace timer

namespace pwr {
struct PwrRegDef {
    union CR {
        struct {
            RegWidth_t LPDS      : 1;   //  Low-power deep sleep
            RegWidth_t PDDS      : 1;   //  Power down deepsleep
            RegWidth_t CWUF      : 1;   //  Clear wakeup flag
            RegWidth_t CSBF      : 1;   //  Clear standby flag
            RegWidth_t PVDE      : 1;   //  Power voltage detector enable
            RegWidth_t PLS       : 3;   //  PVD level selection
            RegWidth_t DBP       : 1;   //  Disable backup domain write protection
            RegWidth_t RESERVED  : 23;  //  Reserved, must be kept at reset value
        };
        RegWidth_t registerVal;
    }CR;    //  Power control register
    union CSR {
        struct {
            RegWidth_t WUF       : 1;   // Wakeup flag
            RegWidth_t SBF       : 1;   // Standby flag
            RegWidth_t PVDO      : 1;   // PVD output
            RegWidth_t RESERVED  : 5;   // Reserved, must be kept at reset value
            RegWidth_t EWUP      : 1;   // Enable wakeup pin
            RegWidth_t RESERVED2 : 23;  // Reserved, must be kept at reset value
        };
        RegWidth_t registerVal;
    }CSR;   //  Power control/status register
};
}   // namespace pwr

namespace iwdg {
struct IWDGRegDef {
    RegWidth_t KR;
    RegWidth_t PR;
    RegWidth_t RLD;
    union SR {
        struct {
            RegWidth_t PVU : 1;
            RegWidth_t RVU : 1;
            RegWidth_t     : 30;  //  Reserved
        };
        RegWidth_t registerVal;
    }SR;
};
}  // namespace iwdg
namespace can {
struct CANRegDef {
    union MCR {
        struct {
            RegWidth_t INRQ     : 1;        // Initialization request
            RegWidth_t SLEEP    : 1;        // Sleep mode request
            RegWidth_t TXFP     : 1;        // Transmit FIFO priority
            RegWidth_t RFLM     : 1;        // Receive FIFO locked mode
            RegWidth_t NART     : 1;        // No automatic retransmission
            RegWidth_t AWUM     : 1;        // Automatic wakeup mode
            RegWidth_t ABOM     : 1;        // Automatic bus-off management
            RegWidth_t TTCM     : 1;        // Time triggered communication mode
            RegWidth_t          : 7;        // Reserved (must be kept at reset value)
            RegWidth_t RESET    : 1;        // bxCAN software master reset
            RegWidth_t DBF      : 1;        // Debug freeze
            RegWidth_t          : 15;       // Reserved
        };
        RegWidth_t registerVal;     // 32-bit register value (for direct access)
    }MCR;   // Master Control Register
    union MSR {
        struct {
            RegWidth_t INAK     : 1;        // Initialization acknowledge
            RegWidth_t SLAK     : 1;        // Sleep acknowledge
            RegWidth_t WKUI     : 1;        // Wakeup interrupt
            RegWidth_t SLAKI    : 1;        // Sleep acknowledge interrupt
            RegWidth_t TXM      : 1;        // Transmit mode
            RegWidth_t RXM      : 1;        // Receive mode
            RegWidth_t SAMP     : 1;        // Last sample point
            RegWidth_t RX       : 1;        // CAN Rx signal
            RegWidth_t          : 7;        // Reserved (must be kept at reset value)
            RegWidth_t ERRI     : 1;        // Error interrupt
            RegWidth_t          : 20;       // Reserved
        };
        RegWidth_t registerVal;     // 32-bit register value (for direct access)
    }MSR;   // Master Status Register
    RegWidth_t TSR;         // Transmit Status Register
    RegWidth_t RF0R;        // Receive FIFO 0 Register
    RegWidth_t RF1R;        // Receive FIFO 1 Register
    RegWidth_t IER;         // Interrupt Enable Register
    RegWidth_t ESR;         // Error Status Register
    RegWidth_t BTR;         // Bit Timing Register
    RegWidth_t RESERVED0[88];   // Reserved memory space

    // Transmit Mailboxes
    struct TxMailBox_t {
        RegWidth_t TIR;     // Transmit Identifier Register
        RegWidth_t TDTR;    // Transmit Data Length Control and Time Register
        RegWidth_t TDLR;    // Transmit Data Low Register
        RegWidth_t TDHR;    // Transmit Data High Register
    };
    TxMailBox_t TxMailBox[3];   // 3 Transmit Mailboxes

    // Receive FIFO Mailboxes
    struct RxMailBox_t {
        RegWidth_t RIR;     // Receive Identifier Register
        RegWidth_t RDTR;    // Receive Data Length Control and Time Register
        RegWidth_t RDLR;    // Receive Data Low Register
        RegWidth_t RDHR;    // Receive Data High Register
    };
    RxMailBox_t RxFIFO[2];  // 2 Receive FIFOs (FIFO 0 and FIFO 1)

    // Filter Registers
    RegWidth_t FMR;             // Filter Master Register
    RegWidth_t FM1R;            // Filter Mode Register
    RegWidth_t RESERVED1;       // Reserved memory space
    RegWidth_t FS1R;            // Filter Scale Register
    RegWidth_t RESERVED2;       // Reserved memory space
    RegWidth_t FFA1R;           // Filter FIFO Assignment Register
    RegWidth_t RESERVED3;       // Reserved memory space
    RegWidth_t FA1R;            // Filter Activation Register
    RegWidth_t RESERVED4[8];    // Reserved memory space

    // Filter Banks
    struct FilterBank {
        RegWidth_t FR1;         // Filter Bank Register 1
        RegWidth_t FR2;         // Filter Bank Register 2
    };
    FilterBank sFilterRegister[14];     // STM32F103 has 14 filter banks
};
}  // namespace can
}  // namespace registers
}  // namespace stm32

#endif  // DEV_INC_MCAL_STM32F103XX_H_
