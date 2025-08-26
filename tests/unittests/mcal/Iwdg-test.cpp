/**
 * @file Iwdg-test.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-27
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#if 0
#include <gtest/gtest.h>
#include "utils/Types.h"
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Iwdg.h"

using namespace stm32::util;
using namespace stm32::dev::mcal::iwdg;
using namespace stm32::registers::iwdg;

class IwdgTest : public testing::Test {
 protected:
    void SetUp() override {
        using Iwdg_addr = Addr<Peripheral::kIWDG>;
        Iwdg_addr::Set(&IwdgReg[0]);
        Iwdg::Init();
        IWDG = Iwdg::GetPtr<IWDGRegDef>();
    }
    
    RegWidth_t IwdgReg[4]  = {};
    volatile IWDGRegDef* IWDG;
};

TEST_F(IwdgTest, Refresh) {
    uint16_t reload = 0x0ABC;
    Prescaler prescaler = Prescaler::kDiv32;

    Iwdg iwdg(prescaler, reload);
    EXPECT_EQ(static_cast<uint32_t>(prescaler), IWDG->PR);
    EXPECT_EQ(reload, IWDG->RLR);
    EXPECT_EQ(0xCCCC, IWDG->KR);
    iwdg.Refresh();
    EXPECT_EQ(0xAAAA, IWDG->KR);
}
#endif
