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
    SPI_8bit,
    SPI_16bt,
};
enum FrameFormat {
    MSB,
    LSB,
};
enum ClkMode {
    MODE0,
    MODE1,
    MODE2,
    MODE3,
};
enum SlaveManage {
    HW,
    SW,
};
enum BaudRate {
    F_DIV_2,
    F_DIV_4,
    F_DIV_8,
    F_DIV_16,
    F_DIV_32,
    F_DIV_64,
    F_DIV_128,
    F_DIV_256,
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
