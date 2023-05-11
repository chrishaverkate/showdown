#pragma once

extern "C" {
#include "../lcd/lib/Config/DEV_Config.h"
#include "../lcd/lib/GUI/GUI_Paint.h"
#include "../lcd/lib/LCD/LCD_1in14.h"
}

#include <showdown/screen.h>

extern "C" {
#include "GUI_Paint.h"
}

class LcdScreen : public Screen {
public:
	void initialize();

	unsigned int get_width() override;
	unsigned int get_height() override;

	void draw();

	void clear() override;
	void draw_line(uint start_x, uint start_y, uint end_x, uint end_y, uint thickness) override;
	void draw_header(std::string string) override;
	void draw_divider_horizontal(uint position_px, uint thickness) override;
	void draw_divider_vertical(uint position_px, uint thickness) override;
	void draw_text(std::string text, uint x, uint y, FontSize size) override;
	void draw_circle(uint center_x, uint center_y, uint radius, Color color) override;

private:
	uint16_t* _display_buffer{};

	static constexpr uint16_t MAX_WIDTH = LCD_1IN14_WIDTH;
	static constexpr uint16_t MAX_HEIGHT = LCD_1IN14_HEIGHT;

	// a positive offset is the number of pixels to move the screen down
	uint16_t _vertical_offset = 0;
	const uint16_t _header_offset = 20;
	bool _includes_header = false;

	uint16_t _color_foreground = WHITE;
	uint16_t _color_background = BLACK;

	static DOT_PIXEL convert_thickness(uint thickness);
	static uint16_t convert_color(Color color);
	static _tFont* convert_font(FontSize size);
};
