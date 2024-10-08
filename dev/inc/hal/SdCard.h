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
#ifndef DEV_INC_HAL_SDCARD_H_
#define DEV_INC_HAL_SDCARD_H_

using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::spi;
#define SD_TIMEOUT    (200)
namespace stm32 {
namespace dev {
namespace hal {
namespace sdcard {
/**
 * @brief Enum representing SD card commands.
 * 
 * These commands are used to interact with the SD card via SPI.
 */
enum SDCommand {
    kCMD0  = 0,     /**< GO_IDLE_STATE - Reset card to idle state */
    kCMD1  = 1,     /**< SEND_OP_COND - Initialize card */
    kCMD8  = 8,     /**< SEND_IF_COND - Check voltage range */
    kCMD9  = 9,     /**< SEND_CSD - Read CSD register */
    kCMD10 = 10,    /**< SEND_CID - Read CID register */
    kCMD12 = 12,    /**< STOP_TRANSMISSION - Stop transmission during multiple block read */
    kCMD16 = 16,    /**< SET_BLOCKLEN - Set block length (in bytes) */
    kCMD17 = 17,    /**< READ_SINGLE_BLOCK - Read a single block of data */
    kCMD18 = 18,    /**< READ_MULTIPLE_BLOCK - Read multiple blocks of data */
    kCMD24 = 24,    /**< WRITE_BLOCK - Write a single block of data */
    kCMD25 = 25,    /**< WRITE_MULTIPLE_BLOCK - Write multiple blocks of data */
    kCMD32 = 32,    /**< ERASE_WR_BLK_START - Set first block to erase */
    kCMD33 = 33,    /**< ERASE_WR_BLK_END - Set last block to erase */
    kCMD38 = 38,    /**< ERASE - Erase selected blocks */
    kCMD55 = 55,    /**< APP_CMD - Next command is an application-specific command */
    kCMD58 = 58,    /**< READ_OCR - Read OCR register */
    kACMD41 = 41    /**< SD_SEND_OP_COND - Send operating condition */
};

/**
 * @brief SD card driver class.
 * 
 * This class provides an interface to initialize the SD card, and read/write data blocks.
 */
class SD {
 public:
  /**
   * @brief Constructs an SD card object.
   * 
   * @param Sdpin GPIO pin connected to the SD card.
   * @param SdSpi SPI interface used for communication with the SD card.
   */
  SD(const Pin& Sdpin, Spi SdSpi);

  /**
   * @brief Initializes the SD card.
   */
  void Init();

  /**
   * @brief Writes a block of data to the SD card.
   * 
   * @param blockAddr Address of the block to write.
   * @param data Pointer to the data to be written.
   * @return true if the operation was successful, false otherwise.
   */
  bool WriteBlock(uint32_t blockAddr, const uint8_t* data);

  /**
   * @brief Reads a block of data from the SD card.
   * 
   * @param blockAddr Address of the block to read.
   * @param data Pointer to the buffer where the read data will be stored.
   * @return true if the operation was successful, false otherwise.
   */
  bool ReadBlock(uint32_t blockAddr, uint8_t* data);

 private:
  /**
   * @brief Transmits a byte of data via SPI.
   * 
   * @param data Data byte to be transmitted.
   */
  void Transmit(uint8_t data);

  /**
   * @brief Sends a command to the SD card.
   * 
   * @param cmd The command to be sent.
   * @param arg Argument for the command.
   */
  void SendCommand(SDCommand cmd, uint32_t arg);

  /**
   * @brief Reads the response from the SD card.
   * 
   * @return The response byte from the SD card.
   */
  uint8_t ReadResponse();

  /**
   * @brief Toggles the clock for a specified number of cycles.
   * 
   * @param cycles Number of clock cycles to toggle.
   */
  void ToggleClock(int cycles);

  Pin Sdpin;    /**< The GPIO pin connected to the SD card. */
  Spi SdSpi;    /**< The SPI interface used for communication with the SD card. */
};
}   //  namespace sdcard
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  // DEV_INC_HAL_SDCARD_H_
