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
class Spi {
 public:
    static void SpiMasterInit(const DataFrame data, const FrameFormat frame, ClkMode clk, SlaveManage slave); // NOLINT
    static void SpiSlaveInit(const DataFrame data, const FrameFormat frame, ClkMode clk);
    static void SpiWrite(uint8_t data);
    static uint8_t SpiRead();
};
}   // namespace spi
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif  // DEV_MCAL_INC_SPI_H_ 
