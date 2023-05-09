#include <memory>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <stdio.h>

#include "pin_assignments.h"

#include "implementations/lcd_screen.h"

#include <showdown/controller.h>
#include <showdown/event_receiver.h>
#include <showdown/factory.h>
#include <showdown/screen.h>


using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::unique_ptr;

uint32_t pwm_setup(uint pin, uint32_t f, int d);
void check_button_a(unique_ptr<Controller>& controller);
void check_button_b(unique_ptr<Controller>& controller);
void check_button_up(unique_ptr<Controller>& controller);
void check_button_down(unique_ptr<Controller>& controller);
void check_button_left(unique_ptr<Controller>& controller);
void check_button_right(unique_ptr<Controller>& controller);
void onboard_led_heartbeat();
void init_io();

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main(int argc, char** argv) {
	init_io();

	printf("\n\n--------------------------\n- Welcome to Pico\n--------------------------\n");

	printf("Setting up LCD Screen...\n");
	LcdScreen lcd;
	lcd.initialize();
	lcd.draw_header("Showdown");

	printf("Setting up Controller and Views...\n");
	auto controller = Factory::create_controller();
	controller->add_view(ViewType::HOME, static_cast<std::shared_ptr<Screen>>(&lcd));
	controller->add_view(ViewType::TIMELINE, static_cast<std::shared_ptr<Screen>>(&lcd));
	controller->add_view(ViewType::TIME_TABLE, static_cast<std::shared_ptr<Screen>>(&lcd));
	controller->add_view(ViewType::DELTA_TABLE, static_cast<std::shared_ptr<Screen>>(&lcd));

	uint64_t count = 0;

	int vertical_offset = 0;

	printf("- Starting Main loop\n");
	while (true) {
		onboard_led_heartbeat();

		check_button_a(controller);
		check_button_b(controller);
		check_button_up(controller);
		check_button_down(controller);
		check_button_left(controller);
		check_button_right(controller);

		controller->draw_current_view();

		if (count++ % 10000000 == 0) {
			printf("Still alive! %llu\n", get_absolute_time());
		}
	}

	return 0;
}
#pragma clang diagnostic pop

/** @brief Setup the an IO pin as a PWM output
 * @param pin [in] The GPIO pin to configure for PWM
 * @param freq [in] The frequency in Hz
 * @param d [in] The duty cycle in percent
 * @return
 */
uint32_t pwm_setup(uint pin, uint32_t freq) {
	gpio_set_function(pin, GPIO_FUNC_PWM);
	uint slice_num = pwm_gpio_to_slice_num(pin);
	uint chan = pwm_gpio_to_channel(pin);

	uint duty_cycle = 50;
	uint32_t clock = 125000000;
	uint32_t divider16 = clock / freq / 4096 + (clock % (freq * 4096) != 0);
	if (divider16 / 16 == 0)
		divider16 = 16;

	uint32_t wrap = clock * 16 / divider16 / freq - 1;
	pwm_set_clkdiv_int_frac(slice_num, divider16 / 16, divider16 & 0xF);
	pwm_set_wrap(slice_num, wrap);
	pwm_set_chan_level(slice_num, chan, wrap * duty_cycle / 100);
	return wrap;
}

void check_button_a(unique_ptr<Controller>& controller) {
	static int last_button_state = 0;
	const int button_state = gpio_get(Pins::UI_BTN_A);

	if (button_state != last_button_state) {
		if (button_state == 0) {
			printf("Button A pressed\n");
		}
		last_button_state = button_state;
	}

	uint slice_num = pwm_gpio_to_slice_num(Pins::BUZZER);
	if(button_state == 0) {
		pwm_set_enabled(slice_num, true);
	} else {
		pwm_set_enabled(slice_num, false);
	}
}

void check_button_b(unique_ptr<Controller>& controller) {
	static int last_button_state = 0;
	const int button_state = gpio_get(Pins::UI_BTN_B);

	if (button_state != last_button_state) {
		if (button_state == 0) {
			printf("button: B\n");
			controller->button_pressed_b(get_absolute_time());
		}
		last_button_state = button_state;
	}
}

void check_button_up(unique_ptr<Controller>& controller) {
	static int last_button_state = 0;
	const int button_state = gpio_get(Pins::UI_BTN_UP);

	if (button_state != last_button_state) {
		if (button_state == 0) {
			printf("button: up\n");
			controller->button_pressed_up(get_absolute_time());
		}
		last_button_state = button_state;
	}
}

void check_button_down(unique_ptr<Controller>& controller) {
	static int last_button_state = 0;
	const int button_state = gpio_get(Pins::UI_BTN_DOWN);

	if (button_state != last_button_state) {
		if (button_state == 0) {
			printf("button: down\n");
			controller->button_pressed_down(get_absolute_time());
		}
		last_button_state = button_state;
	}
}

void check_button_left(unique_ptr<Controller>& controller) {
	static int last_button_state = 0;
	const int button_state = gpio_get(Pins::UI_BTN_LEFT);

	if (button_state != last_button_state) {
		if (button_state == 0) {
			printf("button: left\n");
			controller->button_pressed_left(get_absolute_time());
		}
		last_button_state = button_state;
	}
}

void check_button_right(unique_ptr<Controller>& controller) {
	static int last_button_state = 0;
	const int button_state = gpio_get(Pins::UI_BTN_RIGHT);

	if (button_state != last_button_state) {
		if (button_state == 0) {
			printf("button: left\n");
			controller->button_pressed_right(get_absolute_time());
		}
		last_button_state = button_state;
	}
}



void init_io() {
	stdio_init_all();
	gpio_init(Pins::OB_LED);
	gpio_set_dir(Pins::OB_LED, GPIO_OUT);

	gpio_init(Pins::UI_BTN_UP);
	gpio_set_dir(Pins::UI_BTN_UP, GPIO_IN);
	gpio_pull_up(Pins::UI_BTN_UP);

	gpio_init(Pins::UI_BTN_DOWN);
	gpio_set_dir(Pins::UI_BTN_DOWN, GPIO_IN);
	gpio_pull_up(Pins::UI_BTN_DOWN);

	gpio_init(Pins::UI_BTN_LEFT);
	gpio_set_dir(Pins::UI_BTN_LEFT, GPIO_IN);
	gpio_pull_up(Pins::UI_BTN_LEFT);

	gpio_init(Pins::UI_BTN_RIGHT);
	gpio_set_dir(Pins::UI_BTN_RIGHT, GPIO_IN);
	gpio_pull_up(Pins::UI_BTN_RIGHT);

	gpio_init(Pins::UI_BTN_A);
	gpio_set_dir(Pins::UI_BTN_A, GPIO_IN);
	gpio_pull_up(Pins::UI_BTN_A);

	gpio_init(Pins::UI_BTN_B);
	gpio_set_dir(Pins::UI_BTN_B, GPIO_IN);
	gpio_pull_up(Pins::UI_BTN_B);

	pwm_setup(Pins::BUZZER, 1500);


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
