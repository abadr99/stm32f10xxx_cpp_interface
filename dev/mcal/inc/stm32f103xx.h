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
    RegWidth_t ISER[8];        // Interrupt Set Enable Register
    RegWidth_t RESERVED0[24];
    RegWidth_t ICER[8];        // Interrupt Clear Enable Register
    RegWidth_t RESERVED1[24];
    RegWidth_t ISPR[8];        // Interrupt Set Pending Register
    RegWidth_t RESERVED2[24];
    RegWidth_t ICPR[8];        // Interrupt Clear Pending Register
    RegWidth_t RESERVED3[24];
    RegWidth_t IABR[8];        // Interrupt Active Bit Register
    RegWidth_t RESERVED4[56];
    uint8_t IPR[240];          // Interrupt Priority Register
    RegWidth_t RESERVED5[644];
    RegWidth_t STIR;           // Software Trigger Interrupt Register
};
struct  SCBRegDef {
    RegWidth_t CPUID;   // CPUID Base Register
    RegWidth_t ICSR;    // Interrupt Control and State Register
    RegWidth_t VTOR;    // Vector Table Offset Register
    RegWidth_t AIRCR;   // Application Interrupt and Reset Control Register
    RegWidth_t SCR;     // System Control Register
    RegWidth_t CCR;     // Configuration and Control Register
    RegWidth_t SHPR1;   // System Handler Priority Register 1
    RegWidth_t SHPR2;   // System Handler Priority Register 2
    RegWidth_t SHPR3;   // System Handler Priority Register 3
    RegWidth_t SHCRS;   // System Handler Control and State Register
    RegWidth_t CFSR;    // Configurable Fault Status Register
    RegWidth_t MMSR;    // MemManage Fault Status Register
    RegWidth_t BFSR;    // BusFault Status Register
    RegWidth_t UFSR;    // UsageFault Status Register
    RegWidth_t HFSR;    // HardFault Status Register
    RegWidth_t MMAR;    // MemManage Fault Address Register
    RegWidth_t BFAR;    // BusFault Address Register
    RegWidth_t AFSR;    // Auxiliary Fault Status Register
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


#define USART1 (USART1_BASE_ADDRESS)
#define USART2 (USART2_BASE_ADDRESS)
#define USART3 (USART3_BASE_ADDRESS)

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

}  // namespace registers
}  // namespace stm32

#endif  // DEV_MCAL_INC_STM32F103XX_H_
