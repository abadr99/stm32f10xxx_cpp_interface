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

template <typename T>
class Register {
public:
    Register(uint32_t addr = 0) : baseAddr(reinterpret_cast<T*>(addr)) {}

    void SetAddr(uint32_t addr) {
        baseAddr = reinterpret_cast<T*>(addr);
    }

    T* GetAddr() const {
        return baseAddr;
    }

private:
    T* baseAddr; 
};

template <Peripheral peripheralT>
struct Address;


template <>
struct Address<Peripheral::kRCC> {
    static constexpr uint32_t GetBaseAddr() { return 0x40021000; }
};

template <>
struct Address<Peripheral::kIOPA> {
    static constexpr uint32_t GetBaseAddr() { return 0x40010800; }
};

template <>
struct Address<Peripheral::kIOPB> {
    static constexpr uint32_t GetBaseAddr() { return 0x40010C00; }
};
template <>
struct Address<Peripheral::kIOPC> {
    static constexpr uint32_t GetBaseAddr() { return 0x40011000; } 
};

template <>
struct Address<Peripheral::kEXTI> {
    static constexpr uint32_t GetBaseAddr() { return 0x40010400; }
};

template <>
struct Address<Peripheral::kAFIO> {
    static constexpr uint32_t GetBaseAddr() { return 0x40010000; }
};

template <>
struct Address<Peripheral::kNVIC> {
    static constexpr uint32_t GetBaseAddr() { return 0xE000E100; }
};

template <>
struct Address<Peripheral::kSCB> {
    static constexpr uint32_t GetBaseAddr() { return 0xE000ED00; }
};

template <>
struct Address<Peripheral::kSYSTICK> {
    static constexpr uint32_t GetBaseAddr() { return 0xE000E010; }
};

template <>
struct Address<Peripheral::kSPI1> {
    static constexpr uint32_t GetBaseAddr() { return 0x40013000; }
};

template <>
struct Address<Peripheral::kSPI2> {
    static constexpr uint32_t GetBaseAddr() { return 0x40003800; }
};

template <>
struct Address<Peripheral::kUSART1> {
    static constexpr uint32_t GetBaseAddr() { return 0x40013800; }
};

template <>
struct Address<Peripheral::kUSART2> {
    static constexpr uint32_t GetBaseAddr() { return 0x40004400; }
};

template <>
struct Address<Peripheral::kUSART3> {
    static constexpr uint32_t GetBaseAddr() { return 0x40004800; }
};

template <>
struct Address<Peripheral::kDMA1> {
    static constexpr uint32_t GetBaseAddr() { return 0x40020000; }
};

template <>
struct Address<Peripheral::kRTC> {
    static constexpr uint32_t GetBaseAddr() { return 0x40002800; }
};

template <>
struct Address<Peripheral::kADC1> {
    static constexpr uint32_t GetBaseAddr() { return 0x40012400; }
};

template <>
struct Address<Peripheral::kADC2> {
    static constexpr uint32_t GetBaseAddr() { return 0x40012800; }
};

template <>
struct Address<Peripheral::kI2C1> {
    static constexpr uint32_t GetBaseAddr() { return 0x40005400; }
};

template <>
struct Address<Peripheral::kI2C2> {
    static constexpr uint32_t GetBaseAddr() { return 0x40005800; }
};

template <>
struct Address<Peripheral::kWWDG> {
    static constexpr uint32_t GetBaseAddr() { return 0x40003000; }
};

template <>
struct Address<Peripheral::kIWDG> {
    static constexpr uint32_t GetBaseAddr() { return 0x40002C00; }
};

template <>
struct Address<Peripheral::kPWR> {
    static constexpr uint32_t GetBaseAddr() { return 0x40007000; }
};

template <>
struct Address<Peripheral::kTIM1> {
    static constexpr uint32_t GetBaseAddr() { return 0x40012C00; }
};

template <>
struct Address<Peripheral::kTIM2> {
    static constexpr uint32_t GetBaseAddr() { return 0x40000000; }
};

template <>
struct Address<Peripheral::kTIM3> {
    static constexpr uint32_t GetBaseAddr() { return 0x40000400; }
};

template <>
struct Address<Peripheral::kTIM4> {
    static constexpr uint32_t GetBaseAddr() { return 0x40000800; }
};

template <>
struct Address<Peripheral::kTIM5> {
    static constexpr uint32_t GetBaseAddr() { return 0x40000C00; }
};


}  // namespace constant
}  // namespace stm32

#endif  // DEV_INC_MCAL_BASEADDRESS_H_
