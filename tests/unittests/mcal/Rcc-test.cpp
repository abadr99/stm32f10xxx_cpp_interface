#include <gtest/gtest.h>
#include "mcal/inc/stm32f103xx.h"
#include "mcal/inc/Rcc.h"


TEST(RCC, SetAHBPrescaler)
{
 //not div
 SetAHBPrescaler(kAhpNotDivided);
 EXPECT_EQ(0b0000,       (ExtractBits<RegWidth_t, 4, 7>( RCC->CFGR)));
 //2
 SetAHBPrescaler(kAhpDiv2);
 EXPECT_EQ(0b1000,       (ExtractBits<RegWidth_t, 4, 7>( RCC->CFGR)));
 //4
 SetAHBPrescaler(kAhpDiv4);
 EXPECT_EQ(0b1001,       (ExtractBits<RegWidth_t, 4, 7>( RCC->CFGR)));
 //8
 SetAHBPrescaler(kAhpDiv8);
 EXPECT_EQ(0b1010,       (ExtractBits<RegWidth_t, 4, 7>( RCC->CFGR)));
 //16
 SetAHBPrescaler(kAhpDiv16);
 EXPECT_EQ(0b1011,       (ExtractBits<RegWidth_t, 4, 7>( RCC->CFGR)));
 //64
 SetAHBPrescaler(kAhpDiv64);
 EXPECT_EQ(0b1100,       (ExtractBits<RegWidth_t, 4, 7>( RCC->CFGR)));
 //128
 SetAHBPrescaler(kAhpDiv128);
 EXPECT_EQ(0b1101,       (ExtractBits<RegWidth_t, 4, 7>( RCC->CFGR)));
 //256
 SetAHBPrescaler(kAhpDiv256);
 EXPECT_EQ(0b1110,       (ExtractBits<RegWidth_t, 4, 7>( RCC->CFGR)));
 //512
 SetAHBPrescaler(kAhpDiv512);
 EXPECT_EQ(0b1111,       (ExtractBits<RegWidth_t, 4, 7>( RCC->CFGR)));
}