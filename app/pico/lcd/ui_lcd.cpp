
#include "ui_lcd.h"

extern "C" {
#include "lib/Config/DEV_Config.h"
#include "lib/GUI/GUI_Paint.h"
#include "lib/LCD/LCD_1in14.h"
}

UiLCD::UiLCD() {
	printf("\nUI: Creating UI LCD!\n");
}

void UiLCD::initialize() {
	printf("UI: Initializing...\n");
	sleep_ms(100);
	UDOUBLE image_size = LCD_1IN14_HEIGHT * LCD_1IN14_WIDTH * 2;
	if ((_display_buffer = (UWORD*)malloc(image_size)) == NULL) {
		printf("Failed to apply for black memory...\r\n");
		while (1)
			;
	}

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

	//	update_lux(0.0f);
	//	update_red(0.0f);
	//	update_green(0.0f);
	//	update_blue(0.0f);
	//	update_clear(0.0f);
	//	update_cct(0);

	LCD_1IN14_Display(_display_buffer);
	//	sleep_ms(2000);
}

void UiLCD::draw() {
	LCD_1IN14_Display(_display_buffer);
}

void UiLCD::update_lux(uint32_t lux) {
	char buffer[30];
	snprintf(buffer, 29, "Lux: %lu", lux);
	Paint_DrawRectangle(40, 1, 150, 25, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawString_EN(1, 1, buffer, &Font24, BLACK, WHITE);
	draw();
}

void UiLCD::update_red(float red) {
	_red_light.percent_filled = red;
	draw_bar_vertical(_red_light);
}

void UiLCD::update_green(float green) {
	_green_light.percent_filled = green;
	draw_bar_vertical(_green_light);
}

void UiLCD::update_blue(float blue) {
	_blue_light.percent_filled = blue;
	draw_bar_vertical(_blue_light);
}

void UiLCD::update_clear(float clear) {
	_clear_light.percent_filled = clear;
	draw_bar_vertical(_clear_light);
}

void UiLCD::draw_bar_vertical(const Bar& bar) {
	float fill_percent = (float)bar.percent_filled / 100.0f;
	int y_start_for_fill = (bar.y_stop - bar.y_start) * fill_percent;
	Paint_DrawRectangle(bar.x_start, bar.y_start, bar.x_stop, bar.y_stop, bar.background, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawRectangle(bar.x_start, bar.y_start, bar.x_stop, bar.y_stop, bar.color, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	Paint_DrawRectangle(bar.x_start, bar.y_stop - y_start_for_fill, bar.x_stop, bar.y_stop, bar.color, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	draw();
}

void UiLCD::update_cct(int cct) {
	char buffer[30];
	snprintf(buffer, 29, "%d K", cct);
	Paint_DrawRectangle(1, 40, 100, 60, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawString_EN(1, 40, buffer, &Font24, BLACK, WHITE);
	draw();
}

void UiLCD::draw_test(int vertical_offset) {
	if (vertical_offset < 0) {
		vertical_offset = 0;
	}

	static int last_vertical_offset = -1;

	int offset_scalar = 8;

	const int v_offset = offset_scalar * vertical_offset;

	if (last_vertical_offset == vertical_offset) {
		return;
	}

	printf("Drawing: \n user_offset = %d \n v_offset = %d\n", vertical_offset, v_offset);
	last_vertical_offset = vertical_offset;
	Paint_Clear(BLACK);

	char buffer[30];

	const uint16_t shot_time_divider_top_x = 40;
	const uint16_t shot_time_divider_top_y = 1;
	const uint16_t shot_time_divider_bottom_x = shot_time_divider_top_x;
	const uint16_t shot_time_divider_bottom_y = LCD_1IN14.HEIGHT;

	const uint16_t zero_line_left_x = 20;
	const uint16_t zero_line_left_y = LCD_1IN14.HEIGHT - 50 + v_offset;
	const uint16_t zero_line_right_x = LCD_1IN14.WIDTH;
	const uint16_t zero_line_right_y = zero_line_left_y;

	const uint16_t zero_x = 1;
	const uint16_t zero_y = LCD_1IN14.HEIGHT - 60 + v_offset;



	// initial timeline
	sprintf(buffer, "0");
	Paint_DrawString_EN(zero_x, zero_y, buffer, &Font24, BLACK, WHITE);

	// shot time divider line
	Paint_DrawLine(shot_time_divider_top_x,
	               shot_time_divider_top_y,
	               shot_time_divider_bottom_x,
	               shot_time_divider_bottom_y,
	               GRAY,
	               DOT_PIXEL_1X1,
	               LINE_STYLE_SOLID);

	// zero time
	Paint_DrawLine(zero_line_left_x,
	               zero_line_left_y,
	               zero_line_right_x,
	               zero_line_right_y,
	               GRAY,
	               DOT_PIXEL_1X1,
	               LINE_STYLE_SOLID);

	// draw shot 1
	Paint_DrawCircle(40, LCD_1IN14.HEIGHT - 20 + v_offset, 5, RED, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	sprintf(buffer, " 1     -0.5");
	Paint_DrawString_EN(1, LCD_1IN14.HEIGHT - 25 + v_offset, buffer, &Font16, BLACK, WHITE);

	// draw shot 2
	Paint_DrawCircle(40, LCD_1IN14.HEIGHT - 100 + v_offset, 5, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	sprintf(buffer, " 2     1.10");
	Paint_DrawString_EN(1, LCD_1IN14.HEIGHT - 105 + v_offset, buffer, &Font16, BLACK, WHITE);

	// draw shot 3
	Paint_DrawCircle(40, LCD_1IN14.HEIGHT - 120 + v_offset, 5, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	sprintf(buffer, " 3     1.50");
	Paint_DrawString_EN(1, LCD_1IN14.HEIGHT - 125 + v_offset, buffer, &Font16, BLACK, WHITE);

	// draw shot 4
	Paint_DrawCircle(40, LCD_1IN14.HEIGHT - 170 + v_offset, 5, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	sprintf(buffer, " 4     1.90");
	Paint_DrawString_EN(1, LCD_1IN14.HEIGHT - 175 + v_offset, buffer, &Font16, BLACK, WHITE);

	// draw shot 4
	Paint_DrawCircle(40, LCD_1IN14.HEIGHT - 240 + v_offset, 5, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	sprintf(buffer, " 5     3.00");
	Paint_DrawString_EN(1, LCD_1IN14.HEIGHT - 245 + v_offset, buffer, &Font16, BLACK, WHITE);

	// header
	Paint_DrawRectangle(1, 1, LCD_1IN14.WIDTH, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	sprintf(buffer, "#     t");
	Paint_DrawString_EN(1, 1, buffer, &Font24, BLACK, WHITE);
	Paint_DrawLine(1, 21, LCD_1IN14.WIDTH, 21, WHITE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);

	draw();
}
