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
class Register {
 public:
    void setVal(RegWidth_t value) {val = value;}
    const RegWidth_t& getVal() const {return val;}

 private:
    RegWidth_t val;
};
class RegisterFile {
 public:
    RegisterFile() : registers{} {}
    Register& operator[](uint32_t index) {
        return registers[index];
    }
 private:
    static constexpr uint32_t RegistersNum = 32;
    stm32::util::Array<Register, RegistersNum> registers;
};
template <Peripheral peripheralT, bool test>
struct Address {
    static  RegWidth_t kBaseAddr;
    static RegWidth_t kTestAddr;
    static RegWidth_t getBaseAddr() {
        return test ? kTestAddr : kBaseAddr;
    }
    static void setTestAddr(RegWidth_t testAddr) {
        kTestAddr=testAddr;
    }
};
template <Peripheral peripheralT, bool test>
RegWidth_t Address<peripheralT, test>::kBaseAddr=0;
template <Peripheral peripheralT, bool test>
RegWidth_t Address<peripheralT, test>::kTestAddr=0;
template <>
struct Address<Peripheral::kRCC,false> {
    static constexpr RegWidth_t kBaseAddr = 0x40021000;
};

template <>
struct Address<Peripheral::kIOPA, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40010800;
};

template <>
struct Address<Peripheral::kIOPB, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40010C00;
};

template <>
struct Address<Peripheral::kIOPC, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40011000;
};

template <>
struct Address<Peripheral::kEXTI, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40010400;
};

template <>
struct Address<Peripheral::kAFIO, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40010000;
};

template <>
struct Address<Peripheral::kNVIC, false> {
    static constexpr RegWidth_t kBaseAddr = 0xE000E100;
};

template <>
struct Address<Peripheral::kSCB, false> {
    static constexpr RegWidth_t kBaseAddr = 0xE000ED00;
};

template <>
struct Address<Peripheral::kSYSTICK, false> {
    static constexpr RegWidth_t kBaseAddr = 0xE000E010;
};

template <>
struct Address<Peripheral::kSPI1, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40013000;
};

template <>
struct Address<Peripheral::kSPI2, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40003800;
};

template <>
struct Address<Peripheral::kUSART1, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40013800;
};

template <>
struct Address<Peripheral::kUSART2, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40004400;
};

template <>
struct Address<Peripheral::kUSART3, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40004800;
};

template <>
struct Address<Peripheral::kDMA1, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40020000;
};

template <>
struct Address<Peripheral::kRTC, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40002800;
};

template <>
struct Address<Peripheral::kADC1, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40012400;
};

template <>
struct Address<Peripheral::kADC2,  false> {
    static constexpr RegWidth_t kBaseAddr = 0x40012800;
};

template <>
struct Address<Peripheral::kI2C1, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40005400;
};

template <>
struct Address<Peripheral::kI2C2, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40005800;
};

template <>
struct Address<Peripheral::kWWDG, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40003000;
};

template <>
struct Address<Peripheral::kIWDG, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40002C00;
};

template <>
struct Address<Peripheral::kPWR, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40007000;
};

template <>
struct Address<Peripheral::kTIM1, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40012C00;
};

template <>
struct Address<Peripheral::kTIM2, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40000000;
};

template <>
struct Address<Peripheral::kTIM3, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40000400;
};

template <>
struct Address<Peripheral::kTIM4, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40000800;
};

template <>
struct Address<Peripheral::kTIM5, false> {
    static constexpr RegWidth_t kBaseAddr = 0x40000C00;
};
}  // namespace constant
}  // namespace stm32

#endif  // DEV_INC_MCAL_BASEADDRESS_H_
