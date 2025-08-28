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
#if 0
#include <gtest/gtest.h> 
#include "utils/Types.h"
#include "utils/BitManipulation.h" 
#include "mcal/stm32f103xx.h" 
#include "mcal/Nvic.h"
#include "mcal/Wwdg.h" 
 
using namespace stm32::util; 
using namespace stm32::dev::mcal::nvic;
using namespace stm32::dev::mcal::wwdg; 
using namespace stm32::registers::wwdg;
using namespace stm32::registers::nvic;

class WwdgTest : public testing::Test {
 protected:
    void SetUp() override {
        using Wwdg_addr = Addr<Peripheral::kWWDG>;
        using Nvic_addr = Addr<Peripheral::kNVIC>; 
        using Scb_addr = Addr<Peripheral::kSCB>;
        Nvic_addr::Set(&NvicReg[0]); 
        Scb_addr::Set(&ScbReg[0]);
        Wwdg_addr::Set(&WwdgReg[0]);
        Wwdg::Init();
        Nvic::Init();
        WWDG = Wwdg::GetPtr<WWDGRegDef>();
        NVIC = Nvic::GetPtr<NvicRegDef>();
        SCB = Nvic::GetPtr<SCBRegDef>();
    }
    
    RegWidth_t WwdgReg[3]  = {};
    RegWidth_t NvicReg[905];
    RegWidth_t ScbReg[18];
    volatile NvicRegDef* NVIC; 
    volatile SCBRegDef*  SCB;
    volatile WWDGRegDef* WWDG;
};
TEST_F(WwdgTest, EnableInterrupt) {
    Config config;
    config.windowValue  = 0x5F;     // Example window value
    config.counterValue = 0x7F;     // Example counter value
    config.prescaler    = Prescaler::kDiv8;
    Wwdg::ApplyConfig(config);
    Wwdg::EnableInterrupt();
    EXPECT_EQ(0x1, (ExtractBits<uint32_t, 9>(WWDG->CFR.registerVal)));
}
TEST_F(WwdgTest, DisableInterrupt) {
    Config config;
    config.windowValue  = 0x5F;     // Example window value
    config.counterValue = 0x7F;     // Example counter value
    config.prescaler    = Prescaler::kDiv8;
    Wwdg::ApplyConfig(config);
    Wwdg::DisableInterrupt();
    EXPECT_EQ(0x0, (ExtractBits<uint32_t, 9>(WWDG->CFR.registerVal)));
}
TEST_F(WwdgTest, EarlyWakeupFlag) {
    // Simulate flag set
    WWDG->SR.registerVal = 0x1;
    EXPECT_TRUE(Wwdg::IsEarlyWakeupFlagSet());

    // Clear flag
    Wwdg::ClearEarlyWakeupFlag();
    EXPECT_FALSE(Wwdg::IsEarlyWakeupFlagSet());
}
#endif
