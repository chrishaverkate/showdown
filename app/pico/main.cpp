#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"


#include <memory>
#include <pico/binary_info.h>
#include <pico/stdlib.h>
#include <hardware/pwm.h>
#include <hardware/adc.h>
#include <stdio.h>
#include <vector>


#include "pin_assignments.h"

#include "implementations/lcd_screen.h"
#include "implementations/pico_system.h"

#include <showdown/controller.h>
#include <showdown/event_receiver.h>
#include <showdown/factory.h>
#include <showdown/screen.h>


using std::make_shared;
using std::make_unique;
using std::shared_ptr;
using std::unique_ptr;
using std::vector;

void build_fake_shot_session(unique_ptr<Controller>& controller);

void shot_detection_isr(uint gpio, uint32_t events);
uint32_t pwm_setup(uint8_t pin, uint32_t freq);

void service_buzzer();
void start_buzzer(uint64_t start_time_us);
void stop_buzzer();

template<uint8_t pin>
bool button_pressed();

void onboard_led_heartbeat();
void update_system_info(PicoSystem& system, Controller& controller);
void init_io();

bool g_shot_detected = false;  ///< set by the ISR and serviced + cleared when ack'd
bool g_buzzer_active = false;  ///< set by a callback from the controller and cleared when duration is finished.
uint64_t g_session_started = 0; ///< set by the callback from the controller when a session is started.

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main(int argc, char** argv) {
	init_io();

	printf("\n\n--------------------------\n- Welcome to Pico\n--------------------------\n");

	printf("Setting up LCD Screen...\n");
	LcdScreen lcd;
	lcd.initialize();

	printf("Setting up PicoSystem Model...\n");
	PicoSystem pico_system;

	printf("Setting up Controller and Views...\n");
	auto controller = Factory::create_controller();
	controller->add_view(ViewType::HOME, static_cast<std::shared_ptr<Screen>>(&lcd));
	controller->add_view(ViewType::TIMELINE, static_cast<std::shared_ptr<Screen>>(&lcd));
	controller->add_view(ViewType::TIME_TABLE, static_cast<std::shared_ptr<Screen>>(&lcd));
	controller->add_view(ViewType::DELTA_TABLE, static_cast<std::shared_ptr<Screen>>(&lcd));
	controller->add_view(ViewType::SYSTEM_INFO, static_cast<std::shared_ptr<System>>(&pico_system), static_cast<std::shared_ptr<Screen>>(&lcd));
	controller->draw_current_view();

	controller->register_new_session_callback(&start_buzzer);

	// Create lambda functions to help wrap the use of a template and reduce the number of functions
	// that are nearly alike.
	auto service_button_a = [&controller]() {
		if (button_pressed<Pins::UI_BTN_A>()) {
			controller->button_pressed_a(get_absolute_time());
		}
	};

	auto service_button_b = [&controller]() {
		if (button_pressed<Pins::UI_BTN_B>()) {
			controller->button_pressed_b(get_absolute_time());
		}
	};

	auto service_button_up = [&controller]() {
		if (button_pressed<Pins::UI_BTN_UP>()) {
			controller->button_pressed_up(get_absolute_time());
		}
	};

	auto service_button_down = [&controller]() {
		if (button_pressed<Pins::UI_BTN_DOWN>()) {
			controller->button_pressed_down(get_absolute_time());
		}
	};

	auto service_button_left = [&controller]() {
		if (button_pressed<Pins::UI_BTN_LEFT>()) {
			controller->button_pressed_left(get_absolute_time());
		}
	};

	auto service_button_right = [&controller]() {
		if (button_pressed<Pins::UI_BTN_RIGHT>()) {
			controller->button_pressed_right(get_absolute_time());
		}
	};


	printf("- Starting Main loop\n");
	while (true) {
		onboard_led_heartbeat();
		update_system_info(pico_system, *controller);

		service_button_a();
		service_button_b();
		service_button_up();
		service_button_down();
		service_button_left();
		service_button_right();

		service_buzzer();

		if (g_shot_detected) {
			g_shot_detected = false;
			controller->shot_detected(get_absolute_time());
		}
	}

	return 0;
}
#pragma clang diagnostic pop

void init_io() {
	stdio_init_all();

	// USB Power Sense
	gpio_init(Pins::SENSE_USB_POWER);
	gpio_set_dir(Pins::SENSE_USB_POWER, GPIO_IN);

	adc_init();
	adc_gpio_init(Pins::SENSE_VOLTAGE_VSYS);
	adc_select_input(3);

	// On-baord LED for heartbeat
	gpio_init(Pins::OB_LED);
	gpio_set_dir(Pins::OB_LED, GPIO_OUT);

	// User Buttons
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

	// Buzzer
	pwm_setup(Pins::BUZZER, 1500);

	// Shot detection interrupt
	gpio_init(Pins::SHOT_DETECTION);
	gpio_pull_up(Pins::SHOT_DETECTION);
	gpio_set_irq_enabled_with_callback(Pins::SHOT_DETECTION, GPIO_IRQ_EDGE_FALL, true, &shot_detection_isr);

	printf("\n\n -> IO Initialized!\n");
}

/** @brief Setup the an IO pin as a PWM output
 * @param pin [in] The GPIO pin to configure for PWM
 * @param freq [in] The frequency in Hz
 * @param d [in] The duty cycle in percent
 * @return
 */
uint32_t pwm_setup(uint8_t pin, uint32_t freq) {
	gpio_set_function(pin, GPIO_FUNC_PWM);
	uint8_t slice_num = pwm_gpio_to_slice_num(pin);
	uint8_t chan = pwm_gpio_to_channel(pin);

	uint8_t duty_cycle = 50;
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

void shot_detection_isr(uint gpio, uint32_t events) {
	printf("Shot detected!\n");
//	static const int debounce_delay = 50;

	if (gpio == Pins::SHOT_DETECTION) {
		if (gpio_get(Pins::SHOT_DETECTION) == 0) {
			g_shot_detected = true;
		}
	}
}

template<uint8_t pin>
bool button_pressed() {
	static int last_button_state = 0;
	const int button_state = gpio_get(pin);

	if (button_state != last_button_state) {
		if (button_state == 0) {
			printf("Button %d pressed\n", pin);
			return true;
		}
		last_button_state = button_state;
	}

	return false;
}

void service_buzzer() {
	static const uint64_t DURATION = 100 * 100 * 2;

	if(g_buzzer_active) {
		const uint64_t now = get_absolute_time();
		const bool buzzer_finished = (now - g_session_started) > DURATION;

		if (buzzer_finished) {
			stop_buzzer();
		}
	}
}

void start_buzzer(uint64_t start_time_us) {
    uint slice_num = pwm_gpio_to_slice_num(Pins::BUZZER);
	pwm_set_enabled(slice_num, true);
	g_buzzer_active = true;
	g_session_started = start_time_us;
}

void stop_buzzer() {
	uint slice_num = pwm_gpio_to_slice_num(Pins::BUZZER);
	pwm_set_enabled(slice_num, false);
	g_buzzer_active = false;
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

void update_system_info(PicoSystem& system, Controller& controller) {
	static const uint64_t HB_PERIOD = 500000;  // us
	static uint64_t last_time = 0;

	const uint64_t now = get_absolute_time();

	if ((now - last_time) > HB_PERIOD) {
		system.update();
//		controller.draw_current_view();
	}
}

#pragma clang diagnostic pop
