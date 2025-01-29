/**
 * @file Nvic.h
 * @brief
 * @version 0.1
 * @date 2024-04-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef DEV_INC_MCAL_NVIC_H_
#define DEV_INC_MCAL_NVIC_H_

namespace stm32 {
namespace dev   {
namespace mcal  {
namespace nvic   {

/**
 * @brief Enum to define all possible interrupt IDs, including Cortex-M processor exceptions and STM32-specific interrupts.
 */
enum InterruptID : int8_t {
    // Cortex-M Processor Exceptions
    kNonMaskableInt = -14,     /**< Non-Maskable Interrupt */
    kHardFault = -13,          /**< Cortex-M Hard Fault Interrupt */
    kMemoryManagement = -12,   /**< Cortex-M Memory Management Interrupt */
    kBusFault = -11,           /**< Cortex-M Bus Fault Interrupt */
    kUsageFault = -10,         /**< Cortex-M Usage Fault Interrupt */
    kSVCall = -5,              /**< Cortex-M SV Call Interrupt */
    kDebugMonitor = -4,        /**< Cortex-M Debug Monitor Interrupt */
    kPendSV = -2,              /**< Cortex-M Pend SV Interrupt */
    kSysTick = -1,             /**< Cortex-M System Tick Interrupt */

    // STM32F10xxx Device Specific Interrupts
    kWWDG_IRQn = 0,                /**< Window WatchDog Interrupt */
    kPVD_IRQn = 1,                 /**< PVD through EXTI Line detection Interrupt */
    kTAMPER_IRQn = 2,              /**< Tamper Interrupt */
    kRTC_IRQn = 3,                 /**< RTC global Interrupt */
    kFLASH_IRQn = 4,               /**< FLASH global Interrupt */
    kRCC_ID_IRQn = 5,              /**< RCC global Interrupt */
    kEXTI0_IRQn = 6,               /**< EXTI Line0 Interrupt */
    kEXTI1_IRQn = 7,               /**< EXTI Line1 Interrupt */
    kEXTI2_IRQn = 8,               /**< EXTI Line2 Interrupt */
    kEXTI3_IRQn = 9,               /**< EXTI Line3 Interrupt */
    kEXTI4_IRQn = 10,              /**< EXTI Line4 Interrupt */
    kDMA1_Channel1_IRQn = 11,      /**< DMA1 Channel 1 global Interrupt */
    kDMA1_Channel2_IRQn = 12,      /**< DMA1 Channel 2 global Interrupt */
    kDMA1_Channel3_IRQn = 13,      /**< DMA1 Channel 3 global Interrupt */
    kDMA1_Channel4_IRQn = 14,      /**< DMA1 Channel 4 global Interrupt */
    kDMA1_Channel5_IRQn = 15,      /**< DMA1 Channel 5 global Interrupt */
    kDMA1_Channel6_IRQn = 16,      /**< DMA1 Channel 6 global Interrupt */
    kDMA1_Channel7_IRQn = 17,      /**< DMA1 Channel 7 global Interrupt */
    kADC1_2_IRQn = 18,             /**< ADC1 and ADC2 global Interrupt */
    kUSB_HP_CAN1_TX_IRQn = 19,     /**< USB Device High Priority or CAN1 TX Interrupts */ 
    kUSB_LP_CAN1_RX0_IRQn = 20,    /**< USB Device Low Priority or CAN1 RX0 Interrupts */
    kCAN1_RX1_IRQn = 21,           /**< CAN1 RX1 Interrupt */
    kCAN1_SCE_IRQn = 22,           /**< CAN1 SCE Interrupt */
    kEXTI9_5_IRQn = 23,            /**< EXTI Line[9:5] Interrupts */
    kTIM1_BRK_IRQn = 24,           /**< TIM1 Break Interrupt */
    kTIM1_UP_IRQn = 25,            /**< TIM1 Update Interrupt */
    kTIM1_TRG_COM_IRQn = 26,       /**< TIM1 Trigger and Commutation Interrupt */
    kTIM1_CC_IRQn = 27,            /**< TIM1 Capture Compare Interrupt */
    kTIM2_IRQn = 28,               /**< TIM2 global Interrupt */
    kTIM3_IRQn = 29,               /**< TIM3 global Interrupt */
    kTIM4_IRQn = 30,               /**< TIM4 global Interrupt */
    kI2C1_EV_IRQn = 31,            /**< I2C1 Event Interrupt */
    kI2C1_ER_IRQn = 32,            /**< I2C1 Error Interrupt */
    kI2C2_EV_IRQn = 33,            /**< I2C2 Event Interrupt */
    kI2C2_ER_IRQn = 34,            /**< I2C2 Error Interrupt */
    kSPI1_IRQn = 35,               /**< SPI1 global Interrupt */
    kSPI2_IRQn = 36,               /**< SPI2 global Interrupt */
    kUSART1_IRQn = 37,             /**< USART1 global Interrupt */
    kUSART2_IRQn = 38,             /**< USART2 global Interrupt */
    kUSART3_IRQn = 39,             /**< USART3 global Interrupt */
    kEXTI15_10_IRQn = 40,          /**< EXTI Line[15:10] Interrupts */
    kRTCAlarm_IRQn = 41,           /**< RTC Alarm through EXTI Line Interrupt */
    kUSBWakeUp_IRQn = 42,          /**< USB WakeUp from suspend through EXTI Line Interrupt */
};

/**
 * @brief Enum representing the priority grouping options for interrupt priority levels.
 */
enum PriorityGroup {
    kSCB_4GROUP_0SUBGROUP = 0x05FA0300,   /**< 4 priority levels, 0 subpriority levels */
    kSCB_3GROUP_1SUBGROUP = 0x05FA0400,   /**< 3 priority levels, 1 subpriority level */
    kSCB_2GROUP_2SUBGROUP = 0x05FA0500,   /**< 2 priority levels, 2 subpriority levels */
    kSCB_1GROUP_3SUBGROUP = 0x05FA0600,   /**< 1 priority level, 3 subpriority levels */
    kSCB_0GROUP_4SUBGROUP = 0x05FA0700    /**< 0 priority levels, 4 subpriority levels */
};

/**
 * @brief Wrapper data structure used to perform operations on Interrupt IDs.
 * 
 * Provides methods to extract bit positions and register index for an interrupt.
 */
struct Id {
 public:
    /**
     * @brief Constructor to initialize the ID with a given interrupt ID.
     * 
     * @param id The interrupt ID to associate with this object.
     */
    Id(InterruptID id);     // NOLINT 
    
    /**
     * @brief Get the bit position associated with the interrupt.
     * 
     * @return The bit position of the interrupt.
     */
    uint8_t Pos();
    
    /**
     * @brief Get the register index associated with the interrupt.
     * 
     * @return The register index of the interrupt.
     */
    uint8_t Idx();
    
    /**
     * @brief Get the value of the interrupt ID.
     * 
     * @return The interrupt ID value.
     */
    InterruptID Val();

 private:
    InterruptID id_;   /**< Internal interrupt ID */
};

/**
 * @brief NVIC (Nested Vectored Interrupt Controller) management class.
 * 
 * This class provides static methods to enable, disable, and manage interrupts 
 * on the STM32 platform.
 */
class Nvic {
 public:
    using bit = stm32::type::bit;
    using NvicRegDef = stm32::registers::nvic::NvicRegDef;
    using SCBRegDef = stm32::registers::nvic::SCBRegDef;
    static void Init();
    template<typename T>
    static volatile T* GetPtr();

    /**
     * @brief Enable the specified interrupt.
     * 
     * @param id The interrupt ID to enable.
     */
    static void EnableInterrupt(Id id);

    /**
     * @brief Disable the specified interrupt.
     * 
     * @param id The interrupt ID to disable.
     */
    static void DisableInterrupt(Id id);

    /**
     * @brief Set the pending flag for the specified interrupt.
     * 
     * @param id The interrupt ID for which to set the pending flag.
     */
    static void SetPendingFlag(Id id);

    /**
     * @brief Clear the pending flag for the specified interrupt.
     * 
     * @param id The interrupt ID for which to clear the pending flag.
     */
    static void ClearPendingFlag(Id id);

    /**
     * @brief Get the active flag for the specified interrupt.
     * 
     * @param id The interrupt ID for which to get the active flag.
     * @return The active flag status (true if active, false otherwise).
     */
    static bit GetActiveFlag(Id id);

    /**
     * @brief Set the priority for the specified interrupt.
     * 
     * @param id The interrupt ID for which to set the priority.
     * @param priority The priority level to set.
     */
    static void SetPriority(Id id, uint8_t priority);

    /**
     * @brief Set the priority grouping for the NVIC.
     * 
     * @param group The priority group configuration to set.
     */
    static void SetPriorityGroup(PriorityGroup group);

    /**
     * @brief Reset the NVIC configuration to default.
     */
    static void Reset();
 private:
    static volatile NvicRegDef* NVIC;
    static volatile SCBRegDef*  SCB;
};
}   // namespace nvic
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif   // DEV_INC_MCAL_NVIC_H_
