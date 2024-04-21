/**
 * @file Nvic.h
 * @brief
 * @version 0.1
 * @date 2024-04-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef DEV_MCAL_INC_NVIC_H_
#define DEV_MCAL_INC_NVIC_H_
namespace stm32 {
namespace dev   {
namespace mcal  {
namespace nvic   {
enum interruptID {
    // Cortex-M Processor Exceptions
    NonMaskableInt = -14,    /*!< 2 Non Maskable Interrupt */
    HardFault = -13,         /*!< 3 Cortex-M0 Hard Fault Interrupt */
    MemoryManagement = -12,  /*!< 4 Cortex-M0 Memory Management Interrupt */
    BusFault = -11,          /*!< 5 Cortex-M0 Bus Fault Interrupt */
    UsageFault = -10,        /*!< 6 Cortex-M0 Usage Fault Interrupt */
    SVCall = -5,             /*!< 11 Cortex-M0 SV Call Interrupt */
    DebugMonitor = -4,       /*!< 12 Cortex-M0 Debug Monitor Interrupt */
    PendSV = -2,             /*!< 14 Cortex-M0 Pend SV Interrupt */
    SysTick = -1,            /*!< 15 Cortex-M0 System Tick Interrupt */

    // STM32F10xxx Device Specific Interrupts
    WWDG = 0,                /*!< Window WatchDog Interrupt */
    PVD = 1,                 /*!< PVD through EXTI Line detection Interrupt */
    TAMPER = 2,              /*!< Tamper Interrupt */
    RTC = 3,                 /*!< RTC global Interrupt */
    FLASH = 4,               /*!< FLASH global Interrupt */
    RCC_ID = 5,                 /*!< RCC global Interrupt */
    EXTI0 = 6,               /*!< EXTI Line0 Interrupt */
    EXTI1 = 7,               /*!< EXTI Line1 Interrupt */
    EXTI2 = 8,               /*!< EXTI Line2 Interrupt */
    EXTI3 = 9,               /*!< EXTI Line3 Interrupt */
    EXTI4 = 10,              /*!< EXTI Line4 Interrupt */
    DMA1_Channel1 = 11,      /*!< DMA1 Channel 1 global Interrupt */
    DMA1_Channel2 = 12,      /*!< DMA1 Channel 2 global Interrupt */
    DMA1_Channel3 = 13,      /*!< DMA1 Channel 3 global Interrupt */
    DMA1_Channel4 = 14,      /*!< DMA1 Channel 4 global Interrupt */
    DMA1_Channel5 = 15,      /*!< DMA1 Channel 5 global Interrupt */
    DMA1_Channel6 = 16,      /*!< DMA1 Channel 6 global Interrupt */
    DMA1_Channel7 = 17,      /*!< DMA1 Channel 7 global Interrupt */
    ADC1_2 = 18,             /*!< ADC1 and ADC2 global Interrupt */
    USB_HP_CAN1_TX = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts */ // NOLINT
    USB_LP_CAN1_RX0 = 20,    /*!< USB Device Low Priority or CAN1 RX0 Interrupts */ // NOLINT
    CAN1_RX1 = 21,           /*!< CAN1 RX1 Interrupt */
    CAN1_SCE = 22,           /*!< CAN1 SCE Interrupt */
    EXTI9_5 = 23,            /*!< EXTI Line[9:5] Interrupts */
    TIM1_BRK = 24,           /*!< TIM1 Break Interrupt */
    TIM1_UP = 25,            /*!< TIM1 Update Interrupt */
    TIM1_TRG_COM = 26,       /*!< TIM1 Trigger and Commutation Interrupt */
    TIM1_CC = 27,            /*!< TIM1 Capture Compare Interrupt */
    TIM2 = 28,               /*!< TIM2 global Interrupt */
    TIM3 = 29,               /*!< TIM3 global Interrupt */
    TIM4 = 30,               /*!< TIM4 global Interrupt */
    I2C1_EV = 31,            /*!< I2C1 Event Interrupt */
    I2C1_ER = 32,            /*!< I2C1 Error Interrupt */
    I2C2_EV = 33,            /*!< I2C2 Event Interrupt */
    I2C2_ER = 34,            /*!< I2C2 Error Interrupt */
    SPI1 = 35,               /*!< SPI1 global Interrupt */
    SPI2 = 36,               /*!< SPI2 global Interrupt */
    USART1 = 37,             /*!< USART1 global Interrupt */
    USART2 = 38,             /*!< USART2 global Interrupt */
    USART3 = 39,             /*!< USART3 global Interrupt */
    EXTI15_10 = 40,          /*!< EXTI Line[15:10] Interrupts */
    RTCAlarm = 41,           /*!< RTC Alarm through EXTI Line Interrupt */
    USBWakeUp = 42,          /*!< USB WakeUp from suspend through EXTI Line Interrupt */ // NOLINT
};

enum PriorityGroup {
    SCB_4GROUP_0SUBGROUP = 0x05FA0300,
    SCB_3GROUP_1SUBGROUP = 0x05FA0400,
    SCB_2GROUP_2SUBGROUP = 0x05FA0500,
    SCB_1GROUP_3SUBGROUP = 0x05FA0600,
    SCB_0GROUP_4SUBGROUP = 0x05FA0700,
};
class Nvic {
 public:
    static void EnableInterrupt(interruptID id);
    static void DisableInterrupt(interruptID id);
    static void SetPendingFlag(interruptID id);
    static void ClearPendingFlag(interruptID id);
    static uint8_t GetActiveFlag(interruptID id);
    static void SetPriority(interruptID id, uint8_t priority);
    static void SetPriorityGroup(PriorityGroup group);
};
}   // namespace nvic
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif   // DEV_MCAL_INC_NVIC_H_
