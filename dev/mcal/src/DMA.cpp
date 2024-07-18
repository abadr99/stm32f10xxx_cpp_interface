/**
 * @file DMA.cpp
 * @author Noura & MRefat
 * @brief 
 * @version 0.1
 * @date 2024-07-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "mcal/inc/stm32f103xx.h"
#include "Assert.h"
#include "DMA.h"

using namespace stm32::registers::dma;
using namespace stm32::dev::mcal::dma;

void Dma::DMA_Init(const DMAConfig& config) {
    STM32_ASSERT(config.ch >= kCH1 && config.ch <= kCH7);
    STM32_ASSERT(config.dir >= kMEM2MEM && config.dir <= kPER2MEM);
    STM32_ASSERT(config.mode >= kNoCircular && config.mode <= kCircular);
    STM32_ASSERT(config.periInc >= kDisable && config.periInc <= kEnable);
    STM32_ASSERT(config.memInc >= kDisable && config.memInc <= kEnable);
    STM32_ASSERT(config.memSize >= k8bit && config.memSize <= k32bit);
    STM32_ASSERT(config.perSize >= k8bit && config.perSize <= k32bit);
    STM32_ASSERT(config.chPriorty >= kLow && config.chPriorty <= kVeryHigh);
    //  disable DMA
    DMA->CHANNEL[config.ch].CCR.EN = 0;
    //  direction
    switch (config.dir) {
    case kMEM2MEM : DMA->CHANNEL[config.ch].CCR.MEM2MEM = 1; break;
    case kMEM2PER : DMA->CHANNEL[config.ch].CCR.DIR = 1;     break;
    case kPER2MEM : DMA->CHANNEL[config.ch].CCR.DIR = 0;     break; }
    //  Mode
    DMA->CHANNEL[config.ch].CCR.CIRC = config.mode;
    //  PINC
    DMA->CHANNEL[config.ch].CCR.PINC = config.periInc;
    //  MINC
    DMA->CHANNEL[config.ch].CCR.MINC = config.memInc;
    //  Memory Size
    DMA->CHANNEL[config.ch].CCR.MSIZE = config.memSize;
    //  Peripheral Size
    DMA->CHANNEL[config.ch].CCR.PSIZE = config.perSize;
    //  Channel Priority Level
    DMA->CHANNEL[config.ch].CCR.PL = config.chPriorty;
    //  Transfer error interrupt enable
    DMA->CHANNEL[config.ch].CCR.TEIE = config.TransErrInterrup;
    //  Half transfer interrupt enable
    DMA->CHANNEL[config.ch].CCR.HTIE = config.HalfTransInterrup;
    //  Transfer complete interrupt enable
    DMA->CHANNEL[config.ch].CCR.TCIE = config.TransComplInterrup;
}
void Dma::DMA_Transfer(const DMAConfig& config, const uint32_t &srcAdd, const uint32_t &disAdd, uint16_t numOfData) {    //NOLINT
    if (config.dir == kMEM2PER) {
        DMA->CHANNEL[config.ch].CMAR = srcAdd;
        DMA->CHANNEL[config.ch].CPAR = disAdd;
    } else {
        DMA->CHANNEL[config.ch].CPAR = srcAdd;
        DMA->CHANNEL[config.ch].CMAR = disAdd;
    }
    DMA->CHANNEL[config.ch].CNDTR = numOfData;
    DMA->CHANNEL[config.ch].CCR.EN = 0;
}
