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

using stm32::type::RegWidth_t;

namespace stm32 {
namespace constant {

using stm32::peripherals::Peripheral;
template <Peripheral peripheralT, RegWidth_t  BaseAddr>
struct AddressBase {
    static constexpr RegWidth_t  kBaseAddr = BaseAddr;
    static RegWidth_t* testAddr;
    static bool test;

    static RegWidth_t* getBaseAddr() {
        return test ? testAddr : reinterpret_cast<RegWidth_t*> (kBaseAddr);
    }

    static void setTestAddr(RegWidth_t* tAddr) {
        testAddr = tAddr;
        test = true;
    }
};
template <Peripheral peripheralT, RegWidth_t  BaseAddr>
RegWidth_t* AddressBase<peripheralT, BaseAddr>:: testAddr = nullptr;
template <Peripheral peripheralT, RegWidth_t  BaseAddr>
bool AddressBase<peripheralT, BaseAddr>::test = false;

template <Peripheral peripheralT>
struct Address;

template <>
struct Address<Peripheral::kRCC > : AddressBase<Peripheral::kRCC,  0x40021000>{ };
template <>
struct Address<Peripheral::kIOPA> : AddressBase<Peripheral::kIOPA, 0x40010800> {};
template <>
struct Address<Peripheral::kIOPB> : AddressBase<Peripheral::kIOPB, 0x40010C00> {};

template <>
struct Address<Peripheral::kIOPC> : AddressBase<Peripheral::kIOPC, 0x40011000> {};
template <>
struct Address<Peripheral::kEXTI> : AddressBase<Peripheral::kEXTI, 0x40010400> {};
template <>
struct Address<Peripheral::kAFIO> : AddressBase<Peripheral::kAFIO, 0x40010000> {};
template <>
struct Address<Peripheral::kNVIC> : AddressBase<Peripheral::kNVIC, 0xE000E100> {};
template <>
struct Address<Peripheral::kSCB> : AddressBase<Peripheral::kSCB, 0xE000ED00> {};
template <>
struct Address<Peripheral::kSYSTICK> : AddressBase<Peripheral::kSYSTICK, 0xE000E010> {};
template <>
struct Address<Peripheral::kSPI1> : AddressBase<Peripheral::kSPI1, 0x40013000> {};

template <>
struct Address<Peripheral::kSPI2> : AddressBase<Peripheral::kSPI2, 0x40003800> {};
template <>
struct Address<Peripheral::kUSART1> : AddressBase<Peripheral::kUSART1, 0x40013800> {};
template <>
struct Address<Peripheral::kUSART2> : AddressBase<Peripheral::kUSART2, 0x40004400> {};
template <>
struct Address<Peripheral::kUSART3> : AddressBase<Peripheral::kUSART3, 0x40004800> {};
template <>
struct Address<Peripheral::kDMA1> : AddressBase<Peripheral::kDMA1, 0x40020000> {};
template <>
struct Address<Peripheral::kRTC> : AddressBase<Peripheral::kRTC, 0x40002800> {};
template <>
struct Address<Peripheral::kADC1> : AddressBase<Peripheral::kADC1, 0x40012400> {};
template <>
struct Address<Peripheral::kADC2> : AddressBase<Peripheral::kADC2, 0x40012800> {};
template <>
struct Address<Peripheral::kI2C1> : AddressBase<Peripheral::kI2C1, 0x40005400> {};
template <>
struct Address<Peripheral::kI2C2> : AddressBase<Peripheral::kI2C2, 0x40005800>{};

template <>
struct Address<Peripheral::kWWDG > : AddressBase<Peripheral::kWWDG, 0x40003000> {};

template <>
struct Address<Peripheral::kIWDG > : AddressBase<Peripheral::kIWDG, 0x40002C00> {};

template <>
struct Address<Peripheral::kPWR > : AddressBase<Peripheral::kPWR, 0x40007000> {};

template <>
struct Address<Peripheral::kTIM1 > : AddressBase<Peripheral::kTIM1, 0x40012C00> {};

template <>
struct Address<Peripheral::kTIM2 > : AddressBase<Peripheral::kTIM2, 0x40000000> {};

template <>
struct Address<Peripheral::kTIM3 > : AddressBase<Peripheral::kTIM3, 0x40000400 >{};


template <>
struct Address<Peripheral::kTIM4 > : AddressBase<Peripheral::kTIM4,  0x40000800> {};

template <>
struct Address<Peripheral::kTIM5 > : AddressBase<Peripheral::kTIM5, 0x40000C00> {};

}  // namespace constant
}  // namespace stm32

#endif  // DEV_INC_MCAL_BASEADDRESS_H_
