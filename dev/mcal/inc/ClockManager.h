/**
 * @file ClockManager.h
 * @brief
 * @version 0.1
 * @date 2024-03-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef DEV_MCAL_INC_CLOCKMANAGER_H_
#define DEV_MCAL_INC_CLOCKMANAGER_H_

namespace stm32 {
namespace dev {
namespace mcal {
namespace clock_manager {

// Clock manager is just a wrapper class for RCC, as we have multiple
// configurations so in some cases users don't care about all of this
// configurations. In this class we intend to make life easier by reduce number
// of options and make `ClockManger` do all work for us.
class ClockManger {
 public:
    explicit ClockManger(bool isExternalClock = false,
                         uint32_t externalClock = 0);
    void SetSystemClock(uint32_t clk_mhz);
    void Trim(int32_t clk_khz);
    void McoOuput(stm32::dev::mcal::rcc::McoModes output);
 private:
    bool isExternalClock_;
    uint32_t externalClock_;
};

}  // namespace clock_manager
}  // namespace mcal
}  // namespace dev
}  // namespace stm32

#endif  // DEV_MCAL_INC_CLOCKMANAGER_H_
