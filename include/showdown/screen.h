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
		RED,
		GREEN,
		BLUE,
		YELLOW,
		CYAN,
		MAGENTA
	};

	virtual ~Screen() = default;

	/** @brief Paint the entire screen to the background color. */
	virtual void clear() = 0;

	virtual void draw_line(uint start_x, uint start_y, uint end_x, uint end_y, uint thickness) = 0;

	/** @brief Draw a simple header at the top of the screen with the given text. */
	virtual void draw_header(std::string) = 0;

	/** @brief Draw a horizontal line across the screen at the given height. */
	virtual void draw_divider_horizontal(uint position_px, uint thickness) = 0;

	/** @brief Draw a vertical line across the screen at the given width. */
	virtual void draw_divider_vertical(uint position_px, uint thickness) = 0;

	virtual void draw_text(std::string text, uint x, uint y, FontSize size) = 0;

	virtual void draw_circle(uint center_x, uint center_y, uint radius, Color color) = 0;
};
