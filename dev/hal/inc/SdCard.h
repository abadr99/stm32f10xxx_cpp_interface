/**
 * @file SdCard.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-07-28
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_HAL_INC_SDCARD_H_
#define DEV_HAL_INC_SDCARD_H_

using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::spi;
#define SD_TIMEOUT    (200)
namespace stm32 {
namespace dev {
namespace hal {
namespace sdcard {
enum  SDCommand {
    CMD0 = 0,     // GO_IDLE_STATE - Reset card to idle state
    CMD1 = 1,     // SEND_OP_COND - Initialize card
    CMD8 = 8,     // SEND_IF_COND - Check voltage range
    CMD9 = 9,     // SEND_CSD - Read CSD register
    CMD10 = 10,   // SEND_CID - Read CID register
    CMD12 = 12,   // STOP_TRANSMISSION - Stop transmission during multiple block read
    CMD16 = 16,   // SET_BLOCKLEN - Set block length (in bytes)
    CMD17 = 17,   // READ_SINGLE_BLOCK - Read a single block of data
    CMD18 = 18,   // READ_MULTIPLE_BLOCK - Read multiple blocks of data
    CMD24 = 24,   // WRITE_BLOCK - Write a single block of data
    CMD25 = 25,   // WRITE_MULTIPLE_BLOCK - Write multiple blocks of data
    CMD32 = 32,   // ERASE_WR_BLK_START - Set first block to erase
    CMD33 = 33,   // ERASE_WR_BLK_END - Set last block to erase
    CMD38 = 38,   // ERASE - Erase selected blocks
    CMD55 = 55,   // APP_CMD - Next command is an application-specific command
    CMD58 = 58,   // READ_OCR - Read OCR register
    ACMD41 = 41,  // SD_SEND_OP_COND - Send operating condition
};

class SD {
 public:
  SD(Pin Sdpin, Spi SdSpi);
  void Init();
  bool WriteBlock(uint32_t blockAddr, const uint8_t* data);
  bool ReadBlock(uint32_t blockAddr, uint8_t* data);
 private:
  void Transmit(uint8_t data);
  void SendCommand(SDCommand cmd, uint32_t arg);
  uint8_t ReadResponse();
  void toggleClock(int cycles);
  Pin Sdpin;
  Spi SdSpi;
};

}   //  namespace sdcard
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  // DEV_HAL_INC_SDCARD_H_
