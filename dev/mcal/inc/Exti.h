/**
 * @file Exti.h
 * @author
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
using namespace stm32::type;
namespace stm32 {
namespace dev {
namespace mcal {
namespace exti {
    
enum Line {
    kExti0,
    kExti1,
    kExti2,
    kExti3,    
    kExti4,
    kExti5,
    kExti6,
    kExti7,
    kExti8,
    kExti9,
    kExti10,
    kExti11,
    kExti12,
    kExti13,
    kExti14,
    kExti15,
    kExti16,
    kExti17,
    kExti18,
    kExti19
};

enum Trigger {
    kRising,
    kFalling,
    kBoth
};

struct EXTI_Config {
    Port port;
    Line line;
    Trigger trigger;
};
/**
 * @brief : Manage EXTIx.
 * @note  : Don't forget to Enable NVIC Befor Using EXTIx.
 */
class Exti {
 public:
    static void Enable(const EXTI_Config& config);
    static void Disable(const EXTI_Config& config);
    static void SetPendingFlag(const EXTI_Config& config);
    static void ClearPendingFlag(const EXTI_Config& config);
    uint8_t GetPendingFlag(const EXTI_Config& config);
    static void SetpCallBackFunction(Line line , void (*pCallBackFun)(void));
    static pFunction GetpCallBackFunction(Line line);
 private:
    static pFunction pGlobalCallBackFunctions[7];
    static void InitAFIOReg(Line line, Port port);
    static void SetTrigger(Line line, Trigger trigger);
    static void ClrTrigger(Line line, Trigger trigger);
    static uint8_t GetPendingBit(Line line);
};

}  // namespace exti
}  // namespace mcal
}  // namespace dev
}  // namespace stm32
#endif  //  DEV_MCAL_INC_EXTI_H_