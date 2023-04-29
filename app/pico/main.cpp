#include <memory>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <stdio.h>

#include "lcd/ui_lcd.h"
#include "pin_assignments.h"

using std::make_unique;

void check_button_left(uint32_t& button_press_count);
void check_button_right(uint32_t& button_press_count);
void onboard_led_heartbeat();
void init_io();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main(int argc, char** argv) {
	init_io();

	printf("\n\n--------------------------\n- Welcome to Pico\n--------------------------\n");

	uint64_t count = 0;
	printf("- Starting Main loop\n");

	printf("...Setting up LCD Screen\n");

	auto ui_lcd = make_unique<UiLCD>();
	ui_lcd->initialize();

	ui_lcd->update_lux(0);
	uint32_t button_press_count = 0;
	uint32_t time_us = 0;

	while (true) {
		onboard_led_heartbeat();
//		check_button_left(button_press_count);
//		check_button_right(button_press_count);

		time_us = to_ms_since_boot(get_absolute_time());

		ui_lcd->update_lux(time_us / 1000);

		if (count++ % 10000000 == 0) {
			printf("Still alive! %llu\n", get_absolute_time());
		}
	}

	return 0;
}
#pragma clang diagnostic pop

void check_button_left(uint32_t& button_press_count) {
	static uint32_t last_button_state = 0;
	const uint32_t button_state = gpio_get(Pins::UI_BTN_LEFT);

	if (button_state != last_button_state) {
		if (button_state == 0) {
			printf("Button pressed %lu times\n", --button_press_count);
		}
		last_button_state = button_state;
	}
}

void check_button_right(uint32_t& button_press_count) {
	static uint32_t last_button_state = 0;
	const uint32_t button_state = gpio_get(Pins::UI_BTN_RIGHT);

	if (button_state != last_button_state) {
		if (button_state == 0) {
			printf("Button pressed %lu times\n", ++button_press_count);
		}
		last_button_state = button_state;
	}
}

void init_io() {
	stdio_init_all();
	gpio_init(Pins::OB_LED);
	gpio_set_dir(Pins::OB_LED, GPIO_OUT);

	gpio_init(Pins::UI_BTN_LEFT);
	gpio_set_dir(Pins::UI_BTN_LEFT, GPIO_IN);
	gpio_pull_up(Pins::UI_BTN_LEFT);

	gpio_init(Pins::UI_BTN_RIGHT);
	gpio_set_dir(Pins::UI_BTN_RIGHT, GPIO_IN);
	gpio_pull_up(Pins::UI_BTN_RIGHT);

	printf("\n\n -> IO Initialized!\n");
}

void onboard_led_heartbeat() {
	static const uint64_t HB_PERIOD = 500000;  // us
	static uint64_t last_time = 0;
	static bool state = false;

	const uint64_t now = get_absolute_time();

	if ((now - last_time) > HB_PERIOD) {
		state = !state;
		last_time = now;
		gpio_put(Pins::OB_LED, state);
	}
}
