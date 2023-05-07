#pragma once

#include <cstdint>

/** @brief Declares a set of events that can be acted upon by the application.
 */
class EventReceiver {
public:
	virtual ~EventReceiver() = default;
    virtual void button_pressed_a(uint64_t current_time_us) = 0;
	virtual void button_pressed_b(uint64_t current_time_us) = 0;
	virtual void button_pressed_up(uint64_t current_time_us) = 0;
	virtual void button_pressed_down(uint64_t current_time_us) = 0;
	virtual void button_pressed_left(uint64_t current_time_us) = 0;
	virtual void button_pressed_right(uint64_t current_time_us) = 0;
	virtual void button_pressed_select(uint64_t current_time_us) = 0;

	virtual void shot_detected(uint64_t current_time_us) = 0;
};
