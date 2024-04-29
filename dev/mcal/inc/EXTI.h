/**
 * @file EXTI.h
 * @author Manar
 * @brief 
 * @version 0.1
 * @date 2024-04-28
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_MCAL_INC_EXTI_H_
#define DEV_MCAL_INC_EXTI_H_

using namespace stm32::dev::mcal::pin;

namespace stm32 {
namespace dev {
namespace mcal {
namespace exti {


enum class Line {
    EXTI0,
    EXTI1,
    EXTI2,
    EXTI3,    
    EXTI4,
    EXTI5,
    EXTI6,
    EXTI7,
    EXTI8,
    EXTI9,
    EXTI10,
    EXTI11,
    EXTI12,
    EXTI13,
    EXTI14,
    EXTI15,
    EXTI16,
    EXTI17,
    EXTI18,
    EXTI19
};

enum class Trigger {
    Rising,
    Falling,
    Both
};

struct EXTI_Config {
    Port port;
    Line line;
    Trigger trigger;
};

class Exti {
 public:
    static void Enable(const EXTI_Config& config);
    static void Disable(const EXTI_Config& config);
    static void SetPendingFlag(const EXTI_Config& config);
    static void ClearPendingFlag(const EXTI_Config& config);
    uint8_t GetPendingFlag(const EXTI_Config& config);
 private:
    static void Helper_InitAFIOReg(const EXTI_Config& config);
};

}  // namespace exti
}  // namespace mcal
}  // namespace dev
}  // namespace stm32
#endif  //  DEV_MCAL_INC_EXTI_H_
