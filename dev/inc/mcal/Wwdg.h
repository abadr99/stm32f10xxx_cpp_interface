/**
 * @file Wwdg.h
 * @brief 
 * @version 0.1
 * @date 2024-05-1
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_MCAL_INC_WWDG_H_
#define DEV_MCAL_INC_WWDG_H_

namespace stm32 {
namespace dev   {
namespace mcal  {
namespace wwdg  {
enum Prescaler { 
    kDiv2,
    kDiv4,
    kDiv6,
    kDiv8
};
struct Config {
    uint8_t windowValue;
    uint8_t counterValue;
    Prescaler prescaler;
};
class Wwdg {
 public:
    explicit Wwdg(const Config& config);
    void EnableInterrupt();
    void DisableInterrupt();
    bool IsEarlyWakeupFlagSet();
    void ClearEarlyWakeupFlag();
 private:
    Config config_;
    void Init();
};
}   // namespace wwdg
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif  // DEV_MCAL_INC_WWDG_H_ 
