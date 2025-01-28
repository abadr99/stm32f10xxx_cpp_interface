/**
 * @file I2c.h
 * @author
 * @brief 
 * @version 0.1
 * @date 2024-07-13
 * @copyright Copyright (c) 2024
 */

#ifndef DEV_INC_MCAL_I2C_H_
#define DEV_INC_MCAL_I2C_H_

namespace stm32 {
namespace dev   {
namespace mcal  {
namespace i2c   {

/**
 * @brief Enum for selecting I2C peripherals.
 */
enum I2CPeripheral {
    kI2C1,      /**< I2C1 peripheral */
    kI2C2       /**< I2C2 peripheral */
};

/**
 * @brief Enum for defining clock speeds in standard and fast modes.
 */
enum ClkSpeed {
    kMin_Sm = 0x04,  /**< Minimum clock speed for Standard mode */
    kMin_Fm = 0x01   /**< Minimum clock speed for Fast mode */
};

/**
 * @brief Enum for defining the duty cycle in Fast mode.
 */
enum DutyCycle : uint16_t {
    kduty_cycle_2    = 0xBFFF,      /**< Duty cycle of 2 */
    kduty_cycle_16_9 = 0x4000       /**< Duty cycle of 16/9 */
};

/**
 * @brief Enum for selecting the I2C communication mode.
 */
enum Mode {
    kSm,    /**< Standard mode (up to 100kHz) */
    kFm     /**< Fast mode (up to 400kHz) */
};

/**
 * @brief Enum for defining the address length.
 */
enum AddressLength {
    k7_bit,     /**< 7-bit addressing */
    k10_bit     /**< 10-bit addressing */
};

/**
 * @brief Enum for enabling or disabling I2C features.
 */
enum State {
    kDisable,   /**< Disable the feature */
    kEnable     /**< Enable the feature */
};

/**
 * @brief Enum for representing the address matching state.
 */
enum Address_State {
    kMatched,       /**< Address is matched */
    KNot_Matched    /**< Address is not matched */
};

/**
 * @brief Enum for defining the I2C direction (transmitter/receiver).
 */
enum Direction {
    kTransmitter,   /**< I2C Transmitter */
    kReceiver       /**< I2C Receiver */
};

/**
 * @brief Struct for I2C configuration settings.
 */
struct I2cConfig {
    I2CPeripheral i2cx;             /**< I2C peripheral */
    Mode mode;                      /**< I2C mode (Standard/Fast) */
    DutyCycle dutyCycle;            /**< Duty cycle for Fast mode */
    uint32_t speed;                 /**< I2C speed (up to 400kHz) */
    uint32_t ownAddress1;           /**< Own address 1 */
    uint32_t ownAddress2;           /**< Own address 2 */
    AddressLength addressLength;    /**< Address length (7-bit/10-bit) */
    State ack;                      /**< Acknowledge state */
    State interrupt;                /**< Interrupt enable state */
    State dual;                     /**< Dual addressing mode */
    State clkStretch;               /**< Clock stretching */
    State buffState;                /**< Buffer state */
    State eventState;               /**< Event state */
    State errorState;               /**< Error state */
    State genCall;                  /**< General call enable state */
};

/**
 * @note Ensure that the SDL & SCL pins are initialized before using this class.
 */
class I2c {
 public:
    /**
     * @brief Constructs an I2C object with the given configuration.
     * 
     * @param I2c The I2C configuration struct.
     */
    explicit I2c(const I2cConfig& I2c);

    /**
     * @brief Sends data as a master to the specified slave address.
     * 
     * @param slave The address of the slave device.
     * @param data The data buffer to be transmitted.
     * @param size The size of the data buffer.
     */
    void MasterTransmit(uint16_t slave, uint8_t* data, uint8_t size);

    /**
     * @brief Reads data as a master from the specified slave address.
     * 
     * @param slave The address of the slave device.
     * @param data The buffer to store received data.
     * @param size The size of the data buffer.
     */
    void MasterRead(uint16_t slave, uint8_t* data, uint8_t size);

    /**
     * @brief Sends data as a slave device.
     * 
     * @param data The data buffer to be transmitted.
     * @param size The size of the data buffer.
     */
    void SlaveTransmit(uint8_t* data, uint8_t size);

    /**
     * @brief Receives data as a slave device.
     * 
     * @param data The buffer to store received data.
     * @param size The size of the data buffer.
     */
    void SlaveRead(uint8_t* data, uint8_t size);

    /**
     * @brief De-initializes the I2C peripheral and releases resources.
     */
    void DeInit();

 private:
    /**
     * @brief Sends a 7-bit address to the slave with the specified direction.
     * 
     * @param address The 7-bit address of the slave.
     * @param direction The direction (Transmitter/Receiver).
     */
    void Send_7Bit_Add(uint8_t address, Direction direction);

    /**
     * @brief Transmits a byte of data to the slave device.
     * 
     * @param data The byte of data to be transmitted.
     */
    void TransmitData(uint8_t data);

    /**
     * @brief Receives a byte of data from the slave device.
     * 
     * @param data Pointer to store the received byte.
     */
    void ReceiveData(uint8_t* data);

    /**
     * @brief Generates an I2C start condition.
     */
    void StartCondition();

    /**
     * @brief Generates an I2C stop condition.
     */
    void StopCondition();

    /**
     * @brief Configures the I2C clock settings based on the given configuration.
     * 
     * @param I2c The I2C configuration struct.
     */
    void SetClk(const I2cConfig& I2c);

    /**< I2C register structure pointer */
    using I2CRegDef = stm32::registers::i2c::I2CRegDef;
    stm32::type::RegType<I2CRegDef>::ptr i2c_reg;
};

}   // namespace i2c
}   // namespace mcal
}   // namespace dev
}   // namespace stm32
#endif  // DEV_INC_MCAL_I2C_H_
