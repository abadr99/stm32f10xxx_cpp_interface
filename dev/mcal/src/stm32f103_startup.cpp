
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

#define SRAM_START (0x20000000)
#define SRAM_SIZE  (20 * 1024)
#define SRAM_END   ((SRAM_START) + (SRAM_SIZE))

/**
 * @brief STACK_START is the end of SRAM because
 *  the stm32f103 uses stack model (Full descending)
 */
#define STACK_START (SRAM_END)

/* Extern Linker Script Symbols */
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern "C" int  main(void);
extern "C" void Default_Handler(void);
extern "C" void Reset_Handler(void);
extern "C" void NMI_Handler(void)                __attribute__((weak, alias("Default_Handler")));
extern "C" void HardFault_Handler(void)          __attribute__((weak, alias("Default_Handler")));
extern "C" void MemManage_Handler(void)          __attribute__((weak, alias("Default_Handler")));
extern "C" void BusFault_Handler(void)           __attribute__((weak, alias("Default_Handler")));
extern "C" void UsageFault_Handler(void)         __attribute__((weak, alias("Default_Handler")));
extern "C" void SVC_Handler(void)                __attribute__((weak, alias("Default_Handler")));
extern "C" void DebugMon_Handler(void)           __attribute__((weak, alias("Default_Handler")));
extern "C" void PendSV_Handler(void)             __attribute__((weak, alias("Default_Handler")));
extern "C" void SysTick_Handler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void WWDG_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void PVD_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
extern "C" void TAMPER_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
extern "C" void RTC_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
extern "C" void FLASH_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
extern "C" void RCC_IRQHandler(void)             __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI0_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI1_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI2_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI3_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI4_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA1_Channel1_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA1_Channel2_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA1_Channel3_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA1_Channel4_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA1_Channel5_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA1_Channel6_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA1_Channel7_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
extern "C" void ADC1_2_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
extern "C" void USB_HP_CAN_TX_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
extern "C" void USB_LP_CAN_RX0_IRQHandler(void)  __attribute__((weak, alias("Default_Handler")));
extern "C" void CAN_RX1_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
extern "C" void CAN_SCE_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI9_5_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM1_BRK_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM1_UP_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM1_TRG_COM_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM1_CC_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM2_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM3_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM4_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void I2C1_EV_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
extern "C" void I2C1_ER_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
extern "C" void I2C2_EV_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
extern "C" void I2C2_ER_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
extern "C" void SPI1_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void SPI2_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void USART1_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
extern "C" void USART2_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
extern "C" void USART3_IRQHandler(void)          __attribute__((weak, alias("Default_Handler")));
extern "C" void EXTI15_10_IRQHandler(void)       __attribute__((weak, alias("Default_Handler")));
extern "C" void RTCAlarm_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM8_BRK_IRQHandler(void)        __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM8_UP_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM8_TRG_COM_IRQHandler(void)    __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM8_CC_IRQHandler(void)         __attribute__((weak, alias("Default_Handler")));
extern "C" void ADC3_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void FSMC_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void SDIO_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM5_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void SPI3_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void UART4_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
extern "C" void UART5_IRQHandler(void)           __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM6_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void TIM7_IRQHandler(void)            __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA2_Channel1_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA2_Channel2_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA2_Channel3_IRQHandler(void)   __attribute__((weak, alias("Default_Handler")));
extern "C" void DMA2_Channel4_5_IRQHandler(void) __attribute__((weak, alias("Default_Handler")));

__attribute__((section(".isr_vectors"), used))
void (* const vector_table[])(void) = {
    (void (*)(void))((uint32_t)STACK_START),
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
    WWDG_IRQHandler,
    PVD_IRQHandler,
    TAMPER_IRQHandler,
    RTC_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler,
    EXTI0_IRQHandler,
    EXTI1_IRQHandler,
    EXTI2_IRQHandler,
    EXTI3_IRQHandler,
    EXTI4_IRQHandler,
    DMA1_Channel1_IRQHandler,
    DMA1_Channel2_IRQHandler,
    DMA1_Channel3_IRQHandler,
    DMA1_Channel4_IRQHandler,
    DMA1_Channel5_IRQHandler,
    DMA1_Channel6_IRQHandler,
    DMA1_Channel7_IRQHandler,
    ADC1_2_IRQHandler,
    USB_HP_CAN_TX_IRQHandler,
    USB_LP_CAN_RX0_IRQHandler,
    CAN_RX1_IRQHandler,
    CAN_SCE_IRQHandler,
    EXTI9_5_IRQHandler,
    TIM1_BRK_IRQHandler,
    TIM1_UP_IRQHandler,
    TIM1_TRG_COM_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM4_IRQHandler,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    I2C2_EV_IRQHandler,
    I2C2_ER_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    USART3_IRQHandler,
    EXTI15_10_IRQHandler,
    RTCAlarm_IRQHandler,
    0,
    TIM8_BRK_IRQHandler,
    TIM8_UP_IRQHandler,
    TIM8_TRG_COM_IRQHandler,
    TIM8_CC_IRQHandler,
    ADC3_IRQHandler,
    FSMC_IRQHandler,
    SDIO_IRQHandler,
    TIM5_IRQHandler,
    SPI3_IRQHandler,
    UART4_IRQHandler,
    UART5_IRQHandler,
    TIM6_IRQHandler,
    TIM7_IRQHandler,
    DMA2_Channel1_IRQHandler,
    DMA2_Channel2_IRQHandler,
    DMA2_Channel3_IRQHandler,
    DMA2_Channel4_5_IRQHandler
};

extern "C" void Reset_Handler(void) {
    /* 1- Copy .data section FLASH flash to SRAM */
    uint8_t *pSrc  = reinterpret_cast<uint8_t*>(&_etext);
    uint8_t *pDest = reinterpret_cast<uint8_t*>(&_sdata);
    uint32_t data_size = (uint32_t)(&_edata) - (uint32_t)(&_sdata);

    for (uint32_t i=0; i < data_size; i++) {
       pDest[i] = pSrc[i];
    }

    /* 2- Init .bss with zeros */
    pDest = reinterpret_cast<uint8_t*>(&_sbss);
    uint32_t bss_size =  (uint32_t)(&_ebss) - (uint32_t)(&_sbss);

    for (uint32_t i=0; i < bss_size; i++) {
       pDest[i] = 0;
    }

    /* 3- Call Entry point */
    main();

    /* Exit routine */
    while (1) {}
}

extern "C" void Default_Handler(void) {
    while (1) {}
}
