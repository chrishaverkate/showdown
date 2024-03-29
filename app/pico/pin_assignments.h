#pragma once

#include <cstdio>
#include <stdint.h>

/** @brief The pin designations are in GPIO numbers. Refer to the Pico Pinout diagram.
 */
namespace Pins {
/*******************************************************************************
 * Sensors
 ******************************************************************************/
static const uint8_t SENSE_USB_POWER = 24;     // Identifies if USB power is present
static const uint8_t SENSE_VOLTAGE_VSYS = 29;  // Voltage of the system


/*******************************************************************************
 * Visual / Audio
 ******************************************************************************/

static const uint8_t OB_LED = 25;    // On-board LED - show pico has life

/* Pin 21 was carefully selected because it uses PWM Generator slice 2 channel B (1),
 * which is shared with pin 5. Pin 5 should be avoided.
 */
static const uint8_t BUZZER = 21;    // Buzzer
static const uint8_t DEAD_PIN = 5;   // Do not use this pin

// Shot detection
static const uint8_t SHOT_DETECTION = 14;

/*******************************************************************************
 * Communications
 ******************************************************************************/

// Debug communication
static const uint8_t UART_TX = 0;
static const uint8_t UART_RX = 1;

// SPI Lines
//static const uint8_t SPI_0_MOSI = 16;
//static const uint8_t SPI_0_CS = 17;//static const uint8_t SPI_0_SCK = 18;
//static const uint8_t SPI_0_MISO = 19;

// i2c port 0
//static const uint8_t I2C_0_SDA = 20;
//static const uint8_t I2C_0_SCL = 21;

// i2c port 1
//static const uint8_t I2C_1_SDA = 26;
//static const uint8_t I2C_1_SCL = 27;

/*******************************************************************************
 * Reserved for LCD
 ******************************************************************************/
// Buttons
static const uint8_t UI_BTN_A = 15;
static const uint8_t UI_BTN_B = 17;

static const uint8_t UI_BTN_LEFT = 2;   // documented as up
static const uint8_t UI_BTN_RIGHT = 18; // documented as down
static const uint8_t UI_BTN_DOWN = 16;  //documented as left
static const uint8_t UI_BTN_UP = 20;    // documented as right
static const uint8_t UI_BTN_CENTER = 3;

/* Declared in the LCD library
EPD_RST_PIN  = 12;
EPD_DC_PIN   = 8;
EPD_BL_PIN   = 13;

EPD_CS_PIN   = 9;
EPD_CLK_PIN  = 10;
EPD_MOSI_PIN = 11;

EPD_SCL_PIN  = 7;
EPD_SDA_PIN  = 6;
*/
}  // namespace Pins
