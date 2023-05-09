#pragma once

#include "screen.h"
#include "view_type.h"

#include <memory>

class Controller {
public:
	virtual ~Controller() = default;

	virtual void draw_current_view() = 0;

	virtual void add_view(ViewType view_type, std::shared_ptr<Screen> screen) = 0;

	virtual void button_pressed_a(uint64_t current_time_us) = 0;
	virtual void button_pressed_b(uint64_t current_time_us) = 0;
	virtual void button_pressed_up(uint64_t current_time_us) = 0;
	virtual void button_pressed_down(uint64_t current_time_us) = 0;
	virtual void button_pressed_left(uint64_t current_time_us) = 0;
	virtual void button_pressed_right(uint64_t current_time_us) = 0;
	virtual void button_pressed_select(uint64_t current_time_us) = 0;

	virtual void shot_detected(uint64_t current_time_us) = 0;
};
