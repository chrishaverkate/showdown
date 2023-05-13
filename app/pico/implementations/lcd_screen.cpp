#include "lcd_screen.h"

void LcdScreen::initialize() {
	printf("UI: Initializing...\n");
	sleep_ms(100);
	UDOUBLE image_size = MAX_HEIGHT * MAX_WIDTH * 2;
	_display_buffer = new UWORD[image_size];

	if (DEV_Module_Init() != 0) {
		printf("! LCD: Error DEV_Module_Init()\n");
		return;
	}

	// Set brightness
	DEV_SET_PWM(50);

	/* LCD Init */
	printf("Clearing Screen...\n");
	LCD_1IN14_Init(VERTICAL);
	LCD_1IN14_Clear(WHITE);

	Paint_NewImage((UBYTE*)_display_buffer, LCD_1IN14.WIDTH, LCD_1IN14.HEIGHT, 0, WHITE);
	Paint_SetScale(65);
	Paint_Clear(WHITE);
	Paint_SetRotate(ROTATE_180);
	Paint_Clear(BLACK);

	LCD_1IN14_Display(_display_buffer);
}

void LcdScreen::draw() {
	LCD_1IN14_Display(_display_buffer);
}

void LcdScreen::clear() {
	Paint_Clear(_color_background);
	_includes_header = false;
	_vertical_offset = 0;
	draw();
}

void LcdScreen::draw_line(uint8_t start_x, uint8_t start_y, uint8_t end_x, uint8_t end_y, uint8_t thickness) {
	Paint_DrawLine(start_x,
	               start_y + _vertical_offset,
	               end_x,
	               end_y + _vertical_offset,
	               _color_foreground,
	               convert_thickness(thickness),
	               LINE_STYLE_SOLID);
	draw();
}

void LcdScreen::draw_header(std::string string) {
	Paint_DrawString_EN(0,
	                    0,
	                    string.c_str(),
	                    &Font20,
	                    _color_foreground,
	                    _color_background);
	if(!_includes_header) {
		_includes_header = true;
		_vertical_offset += _header_offset;
	}
	draw();
}

void LcdScreen::draw_divider_horizontal(uint8_t position_px, uint8_t thickness) {
	Paint_DrawLine(0,
	               position_px + _vertical_offset,
	               MAX_WIDTH,
	               position_px + _vertical_offset,
	               GRAY,
	               convert_thickness(thickness),
	               LINE_STYLE_SOLID);
	draw();
}

void LcdScreen::draw_divider_vertical(uint8_t position_px, uint8_t thickness) {
	Paint_DrawLine(position_px,
	               1,
	               position_px,
	               MAX_HEIGHT,
	               GRAY,
	               convert_thickness(thickness),
	               LINE_STYLE_SOLID);
	draw();
}

void LcdScreen::draw_text(std::string text, uint8_t x, uint8_t y, Screen::FontSize size) {
	Paint_DrawString_EN(x,
	                    y + _vertical_offset,
	                    text.c_str(),
	                    convert_font(size),
	                    _color_foreground,
	                    _color_background);
	draw();
}

void LcdScreen::draw_circle(uint8_t center_x, uint8_t center_y, uint8_t radius, Screen::Color color) {
	Paint_DrawCircle(center_x,
	                 center_y + _vertical_offset,
	                 radius,
	                 convert_color(color),
	                 DOT_PIXEL_1X1,
	                 DRAW_FILL_FULL);
	draw();
}

DOT_PIXEL LcdScreen::convert_thickness(uint8_t thickness) {
	DOT_PIXEL result = DOT_PIXEL_1X1;

	switch (thickness) {
	case 1:
		result = DOT_PIXEL_1X1;
		break;
	case 2:
		result = DOT_PIXEL_2X2;
		break;
	case 3:
		result = DOT_PIXEL_3X3;
		break;
	case 4:
		result = DOT_PIXEL_4X4;
		break;
	case 5:
		result = DOT_PIXEL_5X5;
		break;
	default:
		result = DOT_PIXEL_1X1;
	}

	return result;
}

uint16_t LcdScreen::convert_color(Color color) {
	uint16_t result = WHITE;

	switch (color) {
	case Screen::Color::BLACK:
		result = BLACK;
		break;
	case Screen::Color::WHITE:
		result = WHITE;
		break;
	case Screen::Color::GRAY:
		result = GRAY;
		break;
	case Screen::Color::RED:
		result = RED;
		break;
	case Color::GREEN:
		result = GREEN;
		break;
	case Color::BLUE:
		result = BLUE;
		break;
	case Color::YELLOW:
		result = YELLOW;
		break;
	case Color::CYAN:
		result = CYAN;
		break;
	case Color::MAGENTA:
		result = MAGENTA;
		break;
	}

	return result;
}

_tFont* LcdScreen::convert_font(FontSize size) {
	_tFont* result = &Font16;

	switch (size) {
	case Screen::FontSize::SMALL:
		result = &Font12;
		break;
	case Screen::FontSize::MEDIUM:
		result = &Font16;
		break;
	case Screen::FontSize::LARGE:
		result = &Font20;
		break;
	}

	return result;
}
unsigned int LcdScreen::get_width() {
	return 0;
}

unsigned int LcdScreen::get_height() {
	return 0;
}
