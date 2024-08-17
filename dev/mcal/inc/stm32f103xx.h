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
#include "BaseAddress.h"
#endif

#include "../../utils/inc/Types.h"

using RegWidth_t = stm32::utils::types::RegWidth_t;
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
    uint32_t ISER[3];    // Interrupt Set Enable Registers
    uint32_t RES0[29];   // Reserved
    uint32_t ICER[3];    // Interrupt Clear Enable Registers
    uint32_t RES1[29];   // Reserved
    uint32_t ISPR[3];    // Interrupt Set Pending Registers
    uint32_t RES2[29];   // Reserved
    uint32_t ICPR[3];    // Interrupt Clear Pending Registers
    uint32_t RES3[29];   // Reserved
    uint32_t IABR[3];    // Interrupt Active Bit Registers
    uint32_t RES4[61];   // Reserved
    uint8_t  IPR[240];   // Interrupt Priority Registers
    uint32_t RES5[644];  // Reserved
    uint32_t STIR;       // Software Trigger Interrupt Register
};
struct  SCBRegDef {
    uint32_t CPUID;      // CPUID Base Register
    uint32_t ICSR;       // Interrupt Control and State Register
    uint32_t VTOR;       // Vector Table Offset Register
    uint32_t AIRCR;      // Application Interrupt and Reset Control Register
    uint32_t SCR;        // System Control Register
    uint32_t CCR;        // Configuration and Control Register
    uint8_t  SHP[12];    // System Handlers Priority Registers
    uint32_t SHCSR;      // System Handler Control and State Register
    uint32_t CFSR;       // Configurable Fault Status Register
    uint32_t HFSR;       // HardFault Status Register
    uint32_t MMFAR;      // MemManage Fault Address Register
    uint32_t BFAR;       // BusFault Address Register
};


#define NVIC   (reinterpret_cast<volatile NvicRegDef*>(NVIC_BASE_ADDRESS))
#define SCB    (reinterpret_cast<volatile SCBRegDef*>(SCB_BASE_ADDRESS))

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

#define AFIO (reinterpret_cast<volatile AfioRegDef*>(AFIO_BASE_ADDRESS))

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

#define SYSTICK (reinterpret_cast<volatile SystickRegDef*>(SYSTICK_BASE_ADDRESS))  // NOLINT

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
            RegWidth_t            :8;   //  Reserved bits 15:8
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
            RegWidth_t            :8;   //  Reserved bits 15:8
        };
        RegWidth_t registerVal;  // SR
    }SR;
    RegWidth_t DR;
    RegWidth_t CRC;
    RegWidth_t RXCRCR;
    RegWidth_t TXCRCR;
};
#define SPI1 (reinterpret_cast<volatile SpiRegDef*>(SPI1_BASE_ADDRESS))
#define SPI2 (reinterpret_cast<volatile SpiRegDef*>(SPI2_BASE_ADDRESS))
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

#define USART1 (reinterpret_cast<volatile UsartRegDef*>(USART1_BASE_ADDRESS))
#define USART2 (reinterpret_cast<volatile UsartRegDef*>(USART2_BASE_ADDRESS))
#define USART3 (reinterpret_cast<volatile UsartRegDef*>(USART3_BASE_ADDRESS))

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

#define EXTI (reinterpret_cast<volatile EXTIRegDef*>(EXTI_BASE_ADDRESS))

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

#define WWDG (reinterpret_cast<volatile WWDGRegDef*>(WWDG_BASE_ADDRESS))
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
#define RTC (reinterpret_cast<volatile RtcRegDef*>(RTC_BASE_ADDRESS))
}  // namespace rtc

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
    #define I2C1 (reinterpret_cast<volatile I2CRegDef*>(I2C1_BASE_ADDRESS))
    #define I2C2 (reinterpret_cast<volatile I2CRegDef*>(I2C2_BASE_ADDRESS))
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

#define DMA (reinterpret_cast<volatile DMARegDef*>(DMA_BASE_ADDRESS))

}  // namespace dma

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
#define IWDG (reinterpret_cast<volatile IWDGRegDef*>(IWDG_BASE_ADDRESS))
}  // namespace iwdg

}  // namespace registers
}  // namespace stm32

#endif  // DEV_MCAL_INC_STM32F103XX_H_
