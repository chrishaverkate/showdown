#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <memory>

#include "pin_assignments.h"
#include "lcd/ui_lcd.h"

using std::make_unique;

void onboard_led_heartbeat();
void init_io();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main (int argc, char** argv) {
	init_io();

	printf("\n\n--------------------------\n- Welcome to Pico\n--------------------------\n");

	uint64_t count = 0;
	printf("- Starting Main loop\n");

    printf("...Setting up LCD Screen\n");

    auto ui_lcd = make_unique<UiLCD>();
    ui_lcd->initialize();

    ui_lcd->update_lux(100);

	while(true) {
		onboard_led_heartbeat();

		if (count++ % 10000000 == 0) {
			printf("Still alive! %llu\n", get_absolute_time());
		}
	}

	return 0;
}
#pragma clang diagnostic pop

void init_io() {
	stdio_init_all();
	gpio_init(Pins::OB_LED);
	gpio_set_dir(Pins::OB_LED, GPIO_OUT);

	printf("\n\n -> IO Initialized!\n");
}

void onboard_led_heartbeat() {
	static const uint64_t HB_PERIOD = 500000; // us
	static uint64_t last_time = 0;
	static bool state = false;

	const uint64_t now = get_absolute_time();

	if((now - last_time) > HB_PERIOD) {
		state = !state;
		last_time = now;
		gpio_put(Pins::OB_LED, state);
	}
}
