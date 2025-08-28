/** 
 * @file Wwdg-test.cpp 
 * @author noura36
 * @brief  
 * @version 0.1 
 * @date 2025-08-27 
 *  
 * @copyright Copyright (c) 2024 
 *  
 */
/*TEST_F(WwdgTest, EnableInterrupt) {
    Config config;
    config.windowValue  = 0x5F;     // Example window value
    config.counterValue = 0x7F;     // Example counter value
    config.prescaler    = Prescaler::kDiv8;
    Wwdg::ApplyConfig(config);
    Wwdg::EnableInterrupt();
    Wwdg::DisableInterrupt();
    EXPECT_EQ(0x0, (ExtractBits<uint32_t, 9>(WWDG->CFR.registerVal)));
}*/
#if 0
#include <gtest/gtest.h> 
#include "utils/Types.h"
#include "utils/BitManipulation.h" 
#include "mcal/stm32f103xx.h" 
#include "mcal/Wwdg.h" 
 
using namespace stm32::util; 
using namespace stm32::dev::mcal::wwdg; 
using namespace stm32::registers::wwdg;

class WwdgTest : public testing::Test {
 protected:
    void SetUp() override {
        using Wwdg_addr = Addr<Peripheral::kWWDG>;
        Wwdg_addr::Set(&WwdgReg[0]);
        Wwdg::Init();
        WWDG = Wwdg::GetPtr<WWDGRegDef>();
    }
    
    RegWidth_t WwdgReg[3]  = {};
    volatile WWDGRegDef* WWDG;
};
TEST_F(WwdgTest, EarlyWakeupFlag) {
    // Simulate flag set
    WWDG->SR.registerVal = 0x1;
    EXPECT_TRUE(Wwdg::IsEarlyWakeupFlagSet());

    // Clear flag
    Wwdg::ClearEarlyWakeupFlag();
    EXPECT_FALSE(Wwdg::IsEarlyWakeupFlagSet());
}
#endif
