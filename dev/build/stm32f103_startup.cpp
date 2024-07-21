
/**
 * @file stm32f103_startup.cpp
 * @author Mohamed Refat
 * @brief 
 * @version 0.1
 * @date 2024-07-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdint.h>

extern "C"
{



#define SRAM_START (0x20000000)
#define SRAM_SIZE  (20 * 1024)
#define SRAM_END   ((SRAM_START) + (SRAM_SIZE))

/**
 * @brief STACK_START is the end of SRAM because
 *  the stm32f103 uses stack model (Full descending)
 */
#define STACK_START (SRAM_END)

/* Extern Linker Script Symbols */
extern uint32_t _etext;  // marks the end of the text (code) section.
extern uint32_t _sdata;  // marks the start of the initialized data section in SRAM.
extern uint32_t _edata;  // 
extern uint32_t _sbss;
extern uint32_t _ebss;

#define DEFINE_IRQ(name_)  void name_(void) __attribute__((weak, alias("Default_Handler")));


int  main(void);
void Default_Handler(void);
void Reset_Handler(void);

DEFINE_IRQ(NMI_Handler) 
DEFINE_IRQ(HardFault_Handler) 
DEFINE_IRQ(MemManage_Handler) 
DEFINE_IRQ(BusFault_Handler) 
DEFINE_IRQ(UsageFault_Handler) 
DEFINE_IRQ(SVC_Handler) 
DEFINE_IRQ(DebugMon_Handler) 
DEFINE_IRQ(PendSV_Handler) 
DEFINE_IRQ(SysTick_Handler) 
DEFINE_IRQ(WWDG_IRQHandler) 
DEFINE_IRQ(PVD_IRQHandler) 
DEFINE_IRQ(TAMPER_IRQHandler) 
DEFINE_IRQ(RTC_IRQHandler) 
DEFINE_IRQ(FLASH_IRQHandler) 
DEFINE_IRQ(RCC_IRQHandler) 
DEFINE_IRQ(EXTI0_IRQHandler) 
DEFINE_IRQ(EXTI1_IRQHandler) 
DEFINE_IRQ(EXTI2_IRQHandler) 
DEFINE_IRQ(EXTI3_IRQHandler) 
DEFINE_IRQ(EXTI4_IRQHandler) 
DEFINE_IRQ(DMA1_Channel1_IRQHandler) 
DEFINE_IRQ(DMA1_Channel2_IRQHandler) 
DEFINE_IRQ(DMA1_Channel3_IRQHandler) 
DEFINE_IRQ(DMA1_Channel4_IRQHandler) 
DEFINE_IRQ(DMA1_Channel5_IRQHandler) 
DEFINE_IRQ(DMA1_Channel6_IRQHandler) 
DEFINE_IRQ(DMA1_Channel7_IRQHandler) 
DEFINE_IRQ(ADC1_2_IRQHandler) 
DEFINE_IRQ(USB_HP_CAN_TX_IRQHandler) 
DEFINE_IRQ(USB_LP_CAN_RX0_IRQHandler) 
DEFINE_IRQ(CAN_RX1_IRQHandler) 
DEFINE_IRQ(CAN_SCE_IRQHandler) 
DEFINE_IRQ(EXTI9_5_IRQHandler) 
DEFINE_IRQ(TIM1_BRK_IRQHandler) 
DEFINE_IRQ(TIM1_UP_IRQHandler) 
DEFINE_IRQ(TIM1_TRG_COM_IRQHandler) 
DEFINE_IRQ(TIM1_CC_IRQHandler) 
DEFINE_IRQ(TIM2_IRQHandler) 
DEFINE_IRQ(TIM3_IRQHandler) 
DEFINE_IRQ(TIM4_IRQHandler) 
DEFINE_IRQ(I2C1_EV_IRQHandler) 
DEFINE_IRQ(I2C1_ER_IRQHandler) 
DEFINE_IRQ(I2C2_EV_IRQHandler) 
DEFINE_IRQ(I2C2_ER_IRQHandler) 
DEFINE_IRQ(SPI1_IRQHandler) 
DEFINE_IRQ(SPI2_IRQHandler) 
DEFINE_IRQ(USART1_IRQHandler) 
DEFINE_IRQ(USART2_IRQHandler) 
DEFINE_IRQ(USART3_IRQHandler) 
DEFINE_IRQ(EXTI15_10_IRQHandler) 
DEFINE_IRQ(RTCAlarm_IRQHandler) 
DEFINE_IRQ(TIM8_BRK_IRQHandler) 
DEFINE_IRQ(TIM8_UP_IRQHandler) 
DEFINE_IRQ(TIM8_TRG_COM_IRQHandler) 
DEFINE_IRQ(TIM8_CC_IRQHandler) 
DEFINE_IRQ(ADC3_IRQHandler) 
DEFINE_IRQ(FSMC_IRQHandler) 
DEFINE_IRQ(SDIO_IRQHandler) 
DEFINE_IRQ(TIM5_IRQHandler) 
DEFINE_IRQ(SPI3_IRQHandler) 
DEFINE_IRQ(UART4_IRQHandler) 
DEFINE_IRQ(UART5_IRQHandler) 
DEFINE_IRQ(TIM6_IRQHandler) 
DEFINE_IRQ(TIM7_IRQHandler) 
DEFINE_IRQ(DMA2_Channel1_IRQHandler) 
DEFINE_IRQ(DMA2_Channel2_IRQHandler) 
DEFINE_IRQ(DMA2_Channel3_IRQHandler) 
DEFINE_IRQ(DMA2_Channel4_5_IRQHandler) 

uint32_t vectors[] __attribute__((section (".isr_vectors"))) = {
    STACK_START,
    (uint32_t) Reset_Handler,
    (uint32_t) NMI_Handler,
    (uint32_t) HardFault_Handler,
    (uint32_t) MemManage_Handler,
    (uint32_t) BusFault_Handler,
    (uint32_t) UsageFault_Handler,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) 0,
    (uint32_t) SVC_Handler,
    (uint32_t) DebugMon_Handler,
    (uint32_t) 0,
    (uint32_t) PendSV_Handler,
    (uint32_t) SysTick_Handler,
    (uint32_t) WWDG_IRQHandler,
    (uint32_t) PVD_IRQHandler,
    (uint32_t) TAMPER_IRQHandler,
    (uint32_t) RTC_IRQHandler,
    (uint32_t) FLASH_IRQHandler,
    (uint32_t) RCC_IRQHandler,
    (uint32_t) EXTI0_IRQHandler,
    (uint32_t) EXTI1_IRQHandler,
    (uint32_t) EXTI2_IRQHandler,
    (uint32_t) EXTI3_IRQHandler,
    (uint32_t) EXTI4_IRQHandler,
    (uint32_t) DMA1_Channel1_IRQHandler,
    (uint32_t) DMA1_Channel2_IRQHandler,
    (uint32_t) DMA1_Channel3_IRQHandler,
    (uint32_t) DMA1_Channel4_IRQHandler,
    (uint32_t) DMA1_Channel5_IRQHandler,
    (uint32_t) DMA1_Channel6_IRQHandler,
    (uint32_t) DMA1_Channel7_IRQHandler,
    (uint32_t) ADC1_2_IRQHandler,
    (uint32_t) USB_HP_CAN_TX_IRQHandler,
    (uint32_t) USB_LP_CAN_RX0_IRQHandler,
    (uint32_t) CAN_RX1_IRQHandler,
    (uint32_t) CAN_SCE_IRQHandler,
    (uint32_t) EXTI9_5_IRQHandler,
    (uint32_t) TIM1_BRK_IRQHandler,
    (uint32_t) TIM1_UP_IRQHandler,
    (uint32_t) TIM1_TRG_COM_IRQHandler,
    (uint32_t) TIM1_CC_IRQHandler,
    (uint32_t) TIM2_IRQHandler,
    (uint32_t) TIM3_IRQHandler,
    (uint32_t) TIM4_IRQHandler,
    (uint32_t) I2C1_EV_IRQHandler,
    (uint32_t) I2C1_ER_IRQHandler,
    (uint32_t) I2C2_EV_IRQHandler,
    (uint32_t) I2C2_ER_IRQHandler,
    (uint32_t) SPI1_IRQHandler,
    (uint32_t) SPI2_IRQHandler,
    (uint32_t) USART1_IRQHandler,
    (uint32_t) USART2_IRQHandler,
    (uint32_t) USART3_IRQHandler,
    (uint32_t) EXTI15_10_IRQHandler,
    (uint32_t) RTCAlarm_IRQHandler,
    (uint32_t) 0,
    (uint32_t) TIM8_BRK_IRQHandler,
    (uint32_t) TIM8_UP_IRQHandler,
    (uint32_t) TIM8_TRG_COM_IRQHandler,
    (uint32_t) TIM8_CC_IRQHandler,
    (uint32_t) ADC3_IRQHandler,
    (uint32_t) FSMC_IRQHandler,
    (uint32_t) SDIO_IRQHandler,
    (uint32_t) TIM5_IRQHandler,
    (uint32_t) SPI3_IRQHandler,
    (uint32_t) UART4_IRQHandler,
    (uint32_t) UART5_IRQHandler,
    (uint32_t) TIM6_IRQHandler,
    (uint32_t) TIM7_IRQHandler,
    (uint32_t) DMA2_Channel1_IRQHandler,
    (uint32_t) DMA2_Channel2_IRQHandler,
    (uint32_t) DMA2_Channel3_IRQHandler,
    (uint32_t) DMA2_Channel4_5_IRQHandler
};

void Reset_Handler(void) {
    // -- 1] COPY .DATA SECTION FROM FLASH TO SRAM
    // 1.a) setting a pointer to the end of the text section (_etext). 
    // i.e. to the initialized data (e.g. initialized global and static variables.) 
    // is stored in FLASH.
    uint8_t *pSrc = reinterpret_cast<uint8_t*>(&_etext);
    
    // 1.b) setting a pointer to the start of the data section in SRAM (_sdata)
    uint8_t *pDest = reinterpret_cast<uint8_t*>(&_sdata);
    
    // 1.c) calculating the datasize i.e. size of initialized data section
    uint32_t data_size = static_cast<uint32_t>(&_edata - &_sdata);

    for (uint32_t i = 0; i < data_size; i++) {
       pDest[i] = pSrc[i];
    }

    // -- 2] INITIATE.BSS WITH ZEROS
    pDest = reinterpret_cast<uint8_t*>(&_sbss);
    uint32_t bss_size =  (uint32_t)(&_ebss) - (uint32_t)(&_sbss);

    for (uint32_t i = 0; i < bss_size; i++) {
       pDest[i] = 0;
    }

    // -- 3] CALL ENTRY POINT
    main();

    // -- 4] EXIT ROUTINE
    while (1) {}
}

void Default_Handler(void) {
    while (1) {}
}

} // extern "C"
