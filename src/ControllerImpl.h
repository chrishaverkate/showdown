#pragma once

#include <showdown/controller.h>
#include <showdown/event_receiver.h>

#include "models/session.h"
#include "views/view.h"

#include <memory>
#include <vector>

class ControllerImpl : public Controller, public EventReceiver {
public:

	~ControllerImpl() override = default;

	void draw_current_view() override;
	void add_view(ViewType view_type) override;

	void add_view(std::unique_ptr<View> view);

	void button_pressed_a(uint64_t current_time_us) override;
	void button_pressed_b(uint64_t current_time_us) override;
	void button_pressed_up(uint64_t current_time_us) override;
	void button_pressed_down(uint64_t current_time_us) override;
	void button_pressed_left(uint64_t current_time_us) override;
	void button_pressed_right(uint64_t current_time_us) override;
	void button_pressed_select(uint64_t current_time_us) override;
	void shot_detected(uint64_t current_time_us) override;



private:
	std::vector<std::unique_ptr<View>> _views {};
	size_t _current_view_index = -1;
};
