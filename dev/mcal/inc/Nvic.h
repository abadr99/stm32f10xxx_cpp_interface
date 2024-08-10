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
enum InterruptID {
    // Cortex-M Processor Exceptions
    kNonMaskableInt = -14,    /*!< 2 Non Maskable Interrupt */
    kHardFault = -13,         /*!< 3 Cortex-M0 Hard Fault Interrupt */
    kMemoryManagement = -12,  /*!< 4 Cortex-M0 Memory Management Interrupt */
    kBusFault = -11,          /*!< 5 Cortex-M0 Bus Fault Interrupt */
    kUsageFault = -10,        /*!< 6 Cortex-M0 Usage Fault Interrupt */
    kSVCall = -5,             /*!< 11 Cortex-M0 SV Call Interrupt */
    kDebugMonitor = -4,       /*!< 12 Cortex-M0 Debug Monitor Interrupt */
    kPendSV = -2,             /*!< 14 Cortex-M0 Pend SV Interrupt */
    kSysTick = -1,            /*!< 15 Cortex-M0 System Tick Interrupt */

    // STM32F10xxx Device Specific Interrupts
    kWWDG_IRQn = 0,                /*!< Window WatchDog Interrupt */
    kPVD_IRQn = 1,                 /*!< PVD through EXTI Line detection Interrupt */
    kTAMPER_IRQn = 2,              /*!< Tamper Interrupt */
    kRTC_IRQn = 3,                 /*!< RTC global Interrupt */
    kFLASH_IRQn = 4,               /*!< FLASH global Interrupt */
    kRCC_ID_IRQn = 5,                 /*!< RCC global Interrupt */
    kEXTI0_IRQn = 6,               /*!< EXTI Line0 Interrupt */
    kEXTI1_IRQn = 7,               /*!< EXTI Line1 Interrupt */
    kEXTI2_IRQn = 8,               /*!< EXTI Line2 Interrupt */
    kEXTI3_IRQn = 9,               /*!< EXTI Line3 Interrupt */
    kEXTI4_IRQn = 10,              /*!< EXTI Line4 Interrupt */
    kDMA1_Channel1_IRQn = 11,      /*!< DMA1 Channel 1 global Interrupt */
    kDMA1_Channel2_IRQn = 12,      /*!< DMA1 Channel 2 global Interrupt */
    kDMA1_Channel3_IRQn = 13,      /*!< DMA1 Channel 3 global Interrupt */
    kDMA1_Channel4_IRQn = 14,      /*!< DMA1 Channel 4 global Interrupt */
    kDMA1_Channel5_IRQn = 15,      /*!< DMA1 Channel 5 global Interrupt */
    kDMA1_Channel6_IRQn = 16,      /*!< DMA1 Channel 6 global Interrupt */
    kDMA1_Channel7_IRQn = 17,      /*!< DMA1 Channel 7 global Interrupt */
    kADC1_2_IRQn = 18,             /*!< ADC1 and ADC2 global Interrupt */
    kUSB_HP_CAN1_TX_IRQn = 19,     /*!< USB Device High Priority or CAN1 TX Interrupts */ // NOLINT
    kUSB_LP_CAN1_RX0_IRQn = 20,    /*!< USB Device Low Priority or CAN1 RX0 Interrupts */ // NOLINT
    kCAN1_RX1_IRQn = 21,           /*!< CAN1 RX1 Interrupt */
    kCAN1_SCE_IRQn = 22,           /*!< CAN1 SCE Interrupt */
    kEXTI9_5_IRQn = 23,            /*!< EXTI Line[9:5] Interrupts */
    kTIM1_BRK_IRQn = 24,           /*!< TIM1 Break Interrupt */
    kTIM1_UP_IRQn = 25,            /*!< TIM1 Update Interrupt */
    kTIM1_TRG_COM_IRQn = 26,       /*!< TIM1 Trigger and Commutation Interrupt */
    kTIM1_CC_IRQn = 27,            /*!< TIM1 Capture Compare Interrupt */
    kTIM2_IRQn = 28,               /*!< TIM2 global Interrupt */
    kTIM3_IRQn = 29,               /*!< TIM3 global Interrupt */
    kTIM4_IRQn = 30,               /*!< TIM4 global Interrupt */
    kI2C1_EV_IRQn = 31,            /*!< I2C1 Event Interrupt */
    kI2C1_ER_IRQn = 32,            /*!< I2C1 Error Interrupt */
    kI2C2_EV_IRQn = 33,            /*!< I2C2 Event Interrupt */
    kI2C2_ER_IRQn = 34,            /*!< I2C2 Error Interrupt */
    kSPI1_IRQn = 35,               /*!< SPI1 global Interrupt */
    kSPI2_IRQn = 36,               /*!< SPI2 global Interrupt */
    kUSART1_IRQn = 37,             /*!< USART1 global Interrupt */
    kUSART2_IRQn = 38,             /*!< USART2 global Interrupt */
    kUSART3_IRQn = 39,             /*!< USART3 global Interrupt */
    kEXTI15_10_IRQn = 40,          /*!< EXTI Line[15:10] Interrupts */
    kRTCAlarm_IRQn = 41,           /*!< RTC Alarm through EXTI Line Interrupt */
    kUSBWakeUp_IRQn = 42,          /*!< USB WakeUp from suspend through EXTI Line Interrupt */ // NOLINT
};

enum PriorityGroup {
    kSCB_4GROUP_0SUBGROUP = 0x05FA0300,
    kSCB_3GROUP_1SUBGROUP = 0x05FA0400,
    kSCB_2GROUP_2SUBGROUP = 0x05FA0500,
    kSCB_1GROUP_3SUBGROUP = 0x05FA0600,
    kSCB_0GROUP_4SUBGROUP = 0x05FA0700,
};
class Nvic {
 public:
    static void EnableInterrupt(InterruptID id);
    static void DisableInterrupt(InterruptID id);
    static void SetPendingFlag(InterruptID id);
    static void ClearPendingFlag(InterruptID id);
    static bool GetActiveFlag(InterruptID id);
    static void SetPriority(InterruptID id, uint8_t priority);
    static void SetPriorityGroup(PriorityGroup group);
};
}   // namespace nvic
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif   // DEV_MCAL_INC_NVIC_H_
