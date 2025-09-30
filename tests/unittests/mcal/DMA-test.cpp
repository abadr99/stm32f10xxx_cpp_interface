/**
 * @file DMA.cpp
 * @author 
 * @brief 
 * @version 0.1
 * @date 2024-07-21
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#if 0
#include <gtest/gtest.h>
#include "utils/Types.h"
#include "utils/BitManipulation.h"
#include "mcal/stm32f103xx.h"
#include "mcal/Pin.h"
#include "mcal/Dma.h"

using namespace stm32::util;
using namespace stm32::dev::mcal::pin;
using namespace stm32::dev::mcal::dma;
using namespace stm32::registers::dma;
using namespace stm32::registers::gpio;

class DmaTest : public testing::Test {
 protected:
    void SetUp() override {
        using Dma_addr = Addr<Peripheral::kDMA1>;
        Dma_addr::Set(&DmaReg[0]);
        Dma::Init(config);
        DMA = Dma::GetPtr();
    }

    uint32_t DmaReg[30] = {};
    DMAConfig config = {
        .channel = kChannel1,
        .dir = kMem2Mem,
        .mode = kNoCircular,
        .sourceBaseAddr = 0x20000000,
        .destinationBaseAddr = 0x40020000,
        .bufferSize = 128,
        .peripheralIncrementState = kEnable,
        .memIncrementState = kEnable,
        .peripheralDataSize = k32bit,
        .memoryDataSize = k32bit,
        .channelPriority = kHigh,
        .transErrorInterrupt = kEnable,
        .transCompleteInterrupt = kEnable,
    };
    volatile DMARegDef* DMA;
};
TEST_F(DmaTest, EnableDisableChannel) {
    Dma::Enable(config.channel);
    EXPECT_EQ(1, (ExtractBits<uint32_t, 0> (DMA->CHANNEL[config.channel].CCR.registerVal)));
    Dma::Disable(config.channel);
    EXPECT_EQ(0, (ExtractBits<uint32_t, 0> (DMA->CHANNEL[config.channel].CCR.registerVal)));
}
TEST_F(DmaTest, SetPointerToTransferCompleteISR) {
    auto dummyISR = [](){};
    Dma::SetPointerToTransferCompleteISR(config.channel, dummyISR);
    EXPECT_EQ(dummyISR, Dma::GetPointerToTransferCompleteISR(config.channel));
}
TEST_F(DmaTest, SetPointerToTransferErrorISR) {
    auto dummyISR = [](){};
    Dma::SetPointerToTransferErrorISR(config.channel, dummyISR);
    EXPECT_EQ(dummyISR, Dma::GetPointerToTransferErrorISR(config.channel));
}
#endif
