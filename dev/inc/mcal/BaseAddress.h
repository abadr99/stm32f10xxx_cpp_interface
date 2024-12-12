/**
 * @file baseAddress.h
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-03-09
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#ifndef DEV_INC_MCAL_BASEADDRESS_H_
#define DEV_INC_MCAL_BASEADDRESS_H_

#include "utils/Types.h"
#include "utils/Array.h"
#include "mcal/Peripherals.h"
#include "mcal/stm32f103xx.h"

// --- IMPORTS 
// TODO(@abadr99): Check if using 'using ...' in headers 
// cause a problems
using stm32::type::RegWidth_t;
using stm32::peripherals::Peripheral;

namespace stm32 {
namespace constant {

// Wrapper class to get specific address either in 
// develop mode or test mode
// NOTE: For testing purpose we are simulating peripheral 
// registers using some data structure. In this case we will
// have dynamic address. This class is responsible for returning
// correct address according to mode
template <Peripheral peripheralT, RegWidth_t BaseAddr>
class BaseAddress {
 public:
    #if UNIT_TEST
    static volatile RegWidth_t* Get() {
        return testAddr;
    }
    #else 
    static volatile RegWidth_t* Get() {
        return reinterpret_cast<volatile RegWidth_t*>(BaseAddr);
    }
    #endif  // UNIT_TEST
    #if UNIT_TEST
    static void Set(volatile RegWidth_t* tAddr) {
        testAddr = tAddr;
    }
    #endif
 private:
    #if UNIT_TEST
    static volatile RegWidth_t* testAddr;
    #else
    // static constexpr RegWidth_t kBaseAddr = BaseAddr;
    #endif  // UNIT_TEST
};

#if UNIT_TEST
template <Peripheral peripheralT, RegWidth_t  BaseAddr>
volatile RegWidth_t* BaseAddress<peripheralT, BaseAddr>::testAddr = nullptr;
#endif  // UNIT_TEST


template <Peripheral peripheralT>
struct Address;

// Address Table
// Peripheral-name   Address
// FIXME: combine with macro @Peripherals.h
#define ADDRESS_TABLE                         \
    PA(RCC,        0x40021000)                \
    PA(IOPA,       0x40010800)                \
    PA(IOPB,       0x40010C00)                \
    PA(IOPC,       0x40011000)                \
    PA(EXTI,       0x40010400)                \
    PA(AFIO,       0x40010000)                \
    PA(NVIC,       0xE000E100)                \
    PA(SCB,        0xE000ED00)                \
    PA(SYSTICK,    0xE000E010)                \
    PA(SPI1,       0x40013000)                \
    PA(SPI2,       0x40003800)                \
    PA(USART1,     0x40013800)                \
    PA(USART2,     0x40004400)                \
    PA(USART3,     0x40004800)                \
    PA(DMA1,       0x40020000)                \
    PA(RTC,        0x40002800)                \
    PA(ADC1,       0x40012400)                \
    PA(ADC2,       0x40012800)                \
    PA(I2C1,       0x40005400)                \
    PA(I2C2,       0x40005800)                \
    PA(WWDG,       0x40003000)                \
    PA(IWDG,       0x40002C00)                \
    PA(PWR,        0x40007000)                \
    PA(TIM1,       0x40012C00)                \
    PA(TIM2,       0x40000000)                \
    PA(TIM3,       0x40000400)                \
    PA(TIM4,       0x40000800)                \
    PA(TIM5,       0x40000C00)

#define PA(name, addr) \
    template<> struct Address<Peripheral::k##name> : BaseAddress<Peripheral::k##name, addr> {};    
    ADDRESS_TABLE
#undef PA
#undef ADDRESS_TABLE
}  // namespace constant
}  // namespace stm32

#endif  // DEV_INC_MCAL_BASEADDRESS_H_
