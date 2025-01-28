/**
 * @file Tft.h
 * @author noura36
 * @brief
 * @version 0.1
 * @date 2024-08-20
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DEV_INC_HAL_TFT_H_
#define DEV_INC_HAL_TFT_H_
using namespace stm32::dev::mcal::pin; 
using namespace stm32::dev::mcal::gpio;
using namespace stm32::dev::mcal::spi;
using namespace stm32::type;
namespace stm32 {
namespace dev {
namespace hal {
namespace tft {
#define RGB565  0x05    /**< Macro for RGB565 pixel format. */

/**
 * @brief Enumeration for TFT display commands.
 */
enum TftCommand {
    kSLPOUT   = 0x11,   /**< Sleep out & booster on command. */
    kCASET    = 0x2A,   /**< Column address set command. */
    kRASET    = 0x2B,   /**< Row address set command. */
    kRAWMR    = 0x2C,   /**< Memory write command. */
    kCOLMOD   = 0x3A,   /**< Interface pixel format command. */
    kDISPON   = 0x29    /**< Display on command. */
};

/**
 * @brief Enumeration for predefined TFT colors.
 */
enum TftColors {
    kBlack   = 0x0000,   /**< Black color. */
    kBlue    = 0x001F,   /**< Blue color. */
    kRed     = 0xF800,   /**< Red color. */
    kMagenta = 0xF81F,   /**< Magenta color. */
    kGreen   = 0x07E0,   /**< Green color. */
    kCyan    = 0x07FF,   /**< Cyan color. */
    kYellow  = 0xFFE0,   /**< Yellow color. */
    kWhite   = 0xFFFF    /**< White color. */
};

/**
 * @brief Enumeration for TFT display resolutions.
 */
enum TftResolution {
    k128x160,   /**< Common resolution for small TFT displays. */
    k240x320,   /**< Another common resolution. */
    k320x480,   /**< Larger resolution. */
    k480x800    /**< High-resolution TFT display. */
};

/**
 * @brief Structure to hold TFT display configuration.
 */
struct TftConfig {
    Pin A0;                       /**< Data/command pin. */
    Pin rst;                      /**< Reset pin. */
    Spi TFtSpi;                  /**< SPI interface for TFT communication. */
    TftResolution resolution;     /**< TFT display resolution. */
    uint16_t width;               /**< Width of the TFT display in pixels. */
    uint16_t height;              /**< Height of the TFT display in pixels. */
};

/**
 * @brief Class for controlling a TFT display.
 */
class Tft {
 public:
    /**
     * @brief Constructs a Tft object with the specified configuration.
     * 
     * @param config Configuration settings for the TFT display.
     */
    explicit Tft(const TftConfig& config);
    
    /**
     * @brief Resets the TFT display.
     */
    void Reset();
    
    /**
     * @brief Displays an image on the TFT display.
     * 
     * @param image The image data to be displayed, in RGB565 format.
     */
    void DisplayImage(const util::Array<uint16_t, 20480> image);
    
    /**
     * @brief Draws a rectangle on the TFT display.
     * 
     * @param height The height of the rectangle.
     * @param width The width of the rectangle.
     * @param xAxis The x-axis position of the rectangle.
     * @param yAxis The y-axis position of the rectangle.
     * @param color The color of the rectangle.
     */
    void DrawRectangle(uint8_t height, uint8_t width, uint8_t xAxis, uint8_t yAxis, TftColors color);   //  NOLINT

 private:
    TftConfig config_;   /**< TFT display configuration. */

    /**
     * @brief Sends a command to the TFT display.
     * 
     * @param command The command to be sent.
     */
    void SendCommand(uint8_t command);

    /**
     * @brief Sends data to the TFT display.
     * 
     * @param data The data byte to be sent.
     */
    void SendData(uint8_t data);

    /**
     * @brief Sets the address window for drawing on the display.
     * 
     * @param startX The starting x-coordinate.
     * @param endX The ending x-coordinate.
     * @param startY The starting y-coordinate.
     * @param endY The ending y-coordinate.
     */
    void SetAddress(uint16_t startX, uint16_t endX, uint16_t startY, uint16_t endY);

    /**
     * @brief Sets a single pixel on the display.
     * 
     * @param pixel The pixel value to be set.
     */
    void SetPixel(uint16_t pixel);

    /**
     * @brief Draws a horizontal line on the display.
     * 
     * @param xAxis The x-coordinate of the starting point.
     * @param yAxis The y-coordinate of the starting point.
     * @param length The length of the line.
     * @param color The color of the line.
     */
    void DrawHLine(uint8_t xAxis, uint8_t yAxis, uint8_t length, TftColors color);

    /**
     * @brief Draws a vertical line on the display.
     * 
     * @param xAxis The x-coordinate of the starting point.
     * @param yAxis The y-coordinate of the starting point.
     * @param length The length of the line.
     * @param color The color of the line.
     */
    void DrawVLine(uint8_t xAxis, uint8_t yAxis, uint8_t length, TftColors color);

    /**
     * @brief Initializes the display resolution settings.
     */
    void InitializeResolution(); 
};

}   //  namespace tft
}   //  namespace hal
}   //  namespace dev
}   //  namespace stm32
#endif  //  DEV_INC_HAL_TFT_H_
