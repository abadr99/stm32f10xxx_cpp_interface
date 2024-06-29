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

class Spi {
 public:
    static void SpiMasterInit(const SpiConfig& config);
    static void SpiSlaveInit(const SpiConfig& config);
    static void SpiWrite(uint8_t data);
    static uint8_t SpiRead();
    static void SpiEnable();
 private:
    static void Helper_SetDataFrame(const SpiConfig& config);
    static void Helper_SetClockMode(const SpiConfig& config);
    static void Helper_SetFrameFormat(const SpiConfig& config);
    static void Helper_MasterBaudRate(const SpiConfig& config);
};
}   // namespace spi
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif  // DEV_MCAL_INC_SPI_H_ 
