/**
 * @file BitManipulation.h
 * @author 
 * @brief
 * @version 0.1
 * @date 2024-02-22
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef DEV_UTILS_INC_REGISTER_H_
#define DEV_UTILS_INC_REGISTER_H_

namespace stm32 {
namespace dev {
namespace utils {
namespace register {

template<typename TRegWidth>
class Register {
 public:
    using namespace stm32::dev::utils::bit_manipulation;    // NOLINT [build/namespaces]
    explicit Register(const TRegWidth address)
    : pReg_(reinterpret_cast<volatile TRegWidth *>(address))
    { /* EMPTY */}

    template<TRegWidth address>
    inline constexpr Register& SetAddress() {
        pReg_ = reinterpret_cast<volatile TRegWidth *>(address);
        return *this;
    }

    template<uint8_t TBitNumber>
    inline constexpr Register& SetBit() {
        *pReg_ |=  (1 << TBitNumber);
        return *this;
    }

    template<uint8_t TBitNumber>
    inline constexpr Register& ClearBit() {
        *pReg_  &= ~(1 << TBitNumber);
        return *this;
    }

    inline constexpr Register& SetBit(uint8_t bitNumber) {
        *pReg_ |=  (1 << bitNumber);
        return *this;
    }

    inline constexpr Register& ClearBit(uint8_t bitNumber) {
        *pReg_  &= ~(1 << bitNumber);
        return *this;
    }

    template<uint8_t TBitNumber>
    inline constexpr uint8_t ReadBit() {
        return ((*pReg_ & (1 << TBitNumber)) >> TBitNumber);
    }

    inline constexpr uint8_t ReadBit(uint8_t bitNumber) {
        return ((*pReg_ & (1 << bitNumber)) >> bitNumber);
    }

    template<uint8_t TBitNumber>
    inline constexpr Register& ToggleBit() {
        *pReg_ ^=  (1 << TBitNumber);
        return *this;
    }

    template<TRegWidth TVal, uint8_t TStart, uint8_t TEnd = TStart>
    inline constexpr Register& WriteBits() {
        static_assert(TStart <= TEnd, "Calling WriteBits with startBit first");
        static_assert(sizeof(TRegWidth)*8 > TStart, "large integer implicitly truncated to unsigned type");     // NOLINT [whitespace/line_length]
        TRegWidth ones = utils::GetOnes<TRegWidth>(static_cast<TRegWidth>(TEnd - TStart) + 1);                  // NOLINT [whitespace/line_length]
        TRegWidth mask = ~(ones << TStart);
        *pReg_ = (*pReg_ & mask) | (TVal << TStart);
        return *this;
    }

    template<uint8_t TStart, uint8_t TEnd = TStart>
    inline constexpr Register& WriteBits(TRegWidth val) {
        static_assert(TStart <= TEnd, "Calling WriteBits with startBit first");
        static_assert(sizeof(TRegWidth)*8 > TStart, "Large integer implicitly truncated to unsigned type");     // NOLINT [whitespace/line_length]
        TRegWidth ones = utils::GetOnes<TRegWidth>(static_cast<TRegWidth>(TEnd - TStart) + 1);                  // NOLINT [whitespace/line_length]
        TRegWidth mask = ~(ones << TStart);
        *pReg_ = (*pReg_ & mask) | (val << TStart);
        return *this;
    }

    template<uint8_t TStart, uint8_t TEnd = TStart>
    inline constexpr TRegWidth ReadBits() {
        static_assert(TStart <= TEnd, "Calling ReadBits with startBit first");
        uint8_t numberOfBits = TEnd - TStart + 1;
        return (*pReg_ >> TStart) & (utils::GetOnes<TRegWidth>(numberOfBits));
    }

    Register& WriteRegister(TRegWidth reg) {
        *pReg_ = reg;
        return *this;
    }

    TRegWidth ReadRegister() {
        return *pReg_;
    }

 private:
    volatile TRegWidth* pReg_;
};
}  // namespace register
}  // namespace utils
}  // namespace dev
}  // namespace stm32
#endif  // DEV_UTILS_INC_REGISTER_H_
