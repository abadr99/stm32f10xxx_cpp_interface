/**
 * @file SPi.h
 * @brief 
 * @version 0.1
 * @date 2024-05-1
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef DEV_MCAL_INC_SPI_H_
#define DEV_MCAL_INC_SPI_H_
using namespace stm32::registers::spi;
namespace stm32 {
namespace dev   {
namespace mcal  {
namespace spi   {

enum DataFrame {
    kSPI_8bit,
    kSPI_16bt,
};
enum FrameFormat {
    kMSB,
    kLSB,
};
enum ClkMode {
    kMODE0,
    kMODE1,
    kMODE2,
    kMODE3,
};
enum SlaveManage {
    kHW,
    kSW,
};
enum  SpiPeripheral {
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
    DataFrame data;
    FrameFormat frame;
    ClkMode clk;
    SlaveManage slave;
    BaudRate br;
};
template<SpiPeripheral  SPI_NUM>
class Spi {
 public:
    Spi();
    void MasterInit(const SpiConfig& config);
    void SlaveInit(const SpiConfig& config);
    void Write(uint8_t data);
    uint8_t Read();
 private:
    void Helper_SetDataFrame(const SpiConfig& config);
    void Helper_SetClockMode(const SpiConfig& config);
    void Helper_SetFrameFormat(const SpiConfig& config);
    void Helper_MasterBaudRate(const SpiConfig& config);
    volatile SpiRegDef* spi_reg;
}; 
}   // namespace spi
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif  // DEV_MCAL_INC_SPI_H_ 
