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

/**
 * @enum DataFrame
 * @brief Specifies the SPI data frame format.
 * 
 * This enum defines the available data frame formats for SPI communication: 
 * 8-bit and 16-bit.
 */
enum DataFrame {
    kSpi_8bit,      /**< 8-bit data frame */
    kSpi_16bit,     /**< 16-bit data frame */
};

/**
 * @enum FrameFormat
 * @brief Specifies the SPI frame format.
 * 
 * This enum defines the order in which bits are transmitted, either 
 * most significant bit (MSB) or least significant bit (LSB) first.
 */
enum FrameFormat {
    kMSB,   /**< Most significant bit first */
    kLSB,   /**< Least significant bit first */
};

/**
 * @enum ClkMode
 * @brief Specifies the SPI clock polarity and phase mode.
 * 
 * This enum defines the four possible SPI clock modes based on clock polarity 
 * and phase.
 */
enum ClkMode {
    kMode0,     /**< Clock polarity: 0, Clock phase: 0 */
    kMode1,     /**< Clock polarity: 0, Clock phase: 1 */
    kMode2,     /**< Clock polarity: 1, Clock phase: 0 */
    kMode3,     /**< Clock polarity: 1, Clock phase: 1 */
};

/**
 * @enum SlaveManage
 * @brief Specifies the SPI slave management mode.
 * 
 * This enum defines the available options for managing the SPI slave: 
 * hardware (HW) or software (SW) management.
 */
enum SlaveManage {
    kHW,    /**< Hardware-based slave management */
    kSW,    /**< Software-based slave management */
};

/**
 * @enum Spinum
 * @brief Specifies the SPI peripheral number.
 * 
 * This enum defines the available SPI peripherals, SPI1 or SPI2.
 */
enum Spinum {
    kSPI1,  /**< SPI1 peripheral */
    kSPI2   /**< SPI2 peripheral */
};

/**
 * @enum BaudRate
 * @brief Specifies the SPI baud rate prescaler.
 * 
 * This enum defines the available baud rate options for SPI communication, 
 * which determine the speed of the SPI clock.
 */
enum BaudRate {
    kF_DIV_2,       /**< SPI clock = fPCLK / 2 */
    kF_DIV_4,       /**< SPI clock = fPCLK / 4 */
    kF_DIV_8,       /**< SPI clock = fPCLK / 8 */
    kF_DIV_16,      /**< SPI clock = fPCLK / 16 */
    kF_DIV_32,      /**< SPI clock = fPCLK / 32 */
    kF_DIV_64,      /**< SPI clock = fPCLK / 64 */
    kF_DIV_128,     /**< SPI clock = fPCLK / 128 */
    kF_DIV_256,     /**< SPI clock = fPCLK / 256 */
};

/**
 * @struct SpiConfig
 * @brief Configuration structure for the SPI peripheral.
 * 
 * This structure defines the SPI configuration, including peripheral number, 
 * data frame format, frame format, clock mode, slave management mode, and baud rate.
 */
struct SpiConfig {
    Spinum number;      /**< SPI peripheral number */
    DataFrame data;     /**< Data frame format */
    FrameFormat frame;  /**< Frame format (MSB or LSB) */
    ClkMode clk;        /**< Clock mode (polarity and phase) */
    SlaveManage slave;  /**< Slave management mode (HW or SW) */
    BaudRate br;        /**< Baud rate prescaler */
};

/**
 * @class Spi
 * @brief Class representing the SPI peripheral interface.
 * 
 * This class provides methods to initialize and control the SPI peripheral for 
 * both master and slave modes. It supports reading and writing data, as well 
 * as configuring the peripheral's data frame, clock, and baud rate.
 */
class Spi {
 public:
    /**
     * @brief Constructs an Spi object with the specified configuration.
     * 
     * @param config Reference to the SpiConfig structure containing the desired configuration.
     */
    explicit Spi(const SpiConfig& config);

    /**
     * @brief Initializes the SPI peripheral in master mode.
     */
    void MasterInit();

    /**
     * @brief Initializes the SPI peripheral in slave mode.
     */
    void SlaveInit();

    /**
     * @brief Writes data to the SPI bus.
     * 
     * @param data The 8-bit data to be transmitted.
     */
    void Write(uint8_t data);

    /**
     * @brief Reads data from the SPI bus.
     * 
     * @return uint8_t The 8-bit data received.
     */
    uint8_t Read();

    /**
     * @brief Gets the SPI peripheral number.
     * 
     * @return Spinum The SPI peripheral number.
     */
    Spinum GetSpiNum();

 private:
    /**
     * @brief Sets the data frame format (8-bit or 16-bit).
     */
    void SetDataFrame();

    /**
     * @brief Sets the clock polarity and phase mode.
     */
    void SetClockMode();

    /**
     * @brief Sets the bit transmission order (MSB or LSB).
     */
    void SetFrameFormat();

    /**
     * @brief Configures the baud rate for master mode.
     */
    void MasterBaudRate();

    const SpiConfig& config_;  /**< Holds the SPI configuration */
    /**< Pointer to the SPI register definition */
    volatile stm32::registers::spi::SpiRegDef* spi_reg;
}; 
}   // namespace spi
}   // namespace mcal
}   // namespace dev
}   // namespace stm32

#endif  // DEV_INC_MCAL_SPI_H_ 
