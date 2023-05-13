#pragma once

#include <string>

/** @brief Declares an interface to a basic color screen that supports drawing lines, text, and shapes.
 */
class Screen {
public:

	enum class FontSize {
		SMALL,
		MEDIUM,
		LARGE
	};

	enum class Color {
		BLACK,
		WHITE,
		GRAY,
		RED,
		GREEN,
		BLUE,
		YELLOW,
		CYAN,
		MAGENTA
	};

	virtual ~Screen() = default;

	virtual unsigned int get_width() = 0;

	virtual unsigned int get_height() = 0;

	/** @brief Paint the entire screen to the background color. */
	virtual void clear() = 0;

	virtual void draw_line(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y, uint8_t thickness) = 0;

	/** @brief Draw a simple header at the top of the screen with the given text. */
	virtual void draw_header(std::string) = 0;

	/** @brief Draw a horizontal line across the screen at the given height. */
	virtual void draw_divider_horizontal(uint8_t position_px, uint8_t thickness) = 0;

	/** @brief Draw a vertical line across the screen at the given width. */
	virtual void draw_divider_vertical(uint8_t position_px, uint8_t thickness) = 0;

	virtual void draw_text(std::string text, uint8_t x, uint8_t y, FontSize size) = 0;

	virtual void draw_circle(uint8_t center_x, uint8_t center_y, uint8_t radius, Color color) = 0;
};
