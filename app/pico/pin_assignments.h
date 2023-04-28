#pragma once

/** @brief The pin designations are in GPIO numbers. Refer to the Pico Pinout diagram.
 */
#include <cstdio>
namespace Pins {
/*******************************************************************************
 * Visual
 ******************************************************************************/

static const uint OB_LED = 25;    // On-board LED - show pico has life

/*******************************************************************************
 * Communications
 ******************************************************************************/

// Debug communication
static const uint UART_TX = 0;
static const uint UART_RX = 1;

// SPI Lines
static const uint SPI_0_MOSI = 16;
static const uint SPI_0_CS = 17;
static const uint SPI_0_SCK = 18;
static const uint SPI_0_MISO = 19;

// i2c port 0
static const uint I2C_0_SDA = 20;
static const uint I2C_0_SCL = 21;

// i2c port 1
static const uint I2C_1_SDA = 26;
static const uint I2C_1_SCL = 27;


}  // namespace Pins
