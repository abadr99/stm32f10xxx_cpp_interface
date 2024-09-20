/**
 * @file SPi.h
 * @brief 
 * @version 0.1
 * @date 2024-05-1
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_INC_MCAL_SPI_H_
#define DEV_INC_MCAL_SPI_H_

namespace stm32 {
namespace dev   {
namespace mcal  {
namespace spi   {

enum DataFrame {
    kSpi_8bit,
    kSpi_16bt,
};
enum FrameFormat {
    kMSB,
    kLSB,
};
enum ClkMode {
    kMode0,
    kMode1,
    kMode2,
    kMode3,
};
enum SlaveManage {
    kHW,
    kSW,
};
enum  Spinum {
    kSPI1,
    kSPI2
};
enum BaudRate {
    kF_DIV_2,
    kF_DIV_4,
    kF_DIV_8,
    kF_DIV_16,
    kF_DIV_32,
    kF_DIV_64,
    kF_DIV_128,
    kF_DIV_256,
};

struct SpiConfig {
    Spinum number;
    DataFrame data;
    FrameFormat frame;
    ClkMode clk;
    SlaveManage slave;
    BaudRate br;
};

class Spi {
 public:
    explicit Spi(const SpiConfig& config);
    void MasterInit();
    void SlaveInit();
    void Write(uint8_t data);
    uint8_t Read();
    Spinum GetSpiNum();
 private:
    void SetDataFrame();
    void SetClockMode();
    void SetFrameFormat();
    void MasterBaudRate();
    const SpiConfig& config_;
    volatile stm32::registers::spi::SpiRegDef* spi_reg;
}; 
}   // namespace spi
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif  // DEV_INC_MCAL_SPI_H_ 
