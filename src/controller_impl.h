#pragma once

#include <showdown/controller.h>
#include <showdown/screen.h>

#include "models/session.h"
#include "views/view.h"

#include <memory>
#include <vector>

class ControllerImpl : public Controller {
public:
	ControllerImpl() {printf("ControllerImpl: ctor\n");}
	~ControllerImpl() override = default;

	void draw_current_view() override;
	void add_view(ViewType view_type, std::shared_ptr<Screen> screen) override;

	void add_view(std::unique_ptr<View> view);

	void button_pressed_a(uint64_t current_time_us) override;
	void button_pressed_b(uint64_t current_time_us) override;
	void button_pressed_up(uint64_t current_time_us) override;
	void button_pressed_down(uint64_t current_time_us) override;
	void button_pressed_left(uint64_t current_time_us) override;
	void button_pressed_right(uint64_t current_time_us) override;
	void button_pressed_select(uint64_t current_time_us) override;
	void shot_detected(uint64_t current_time_us) override;

	void override_session(std::shared_ptr<Session> session);

private:
	std::vector<std::unique_ptr<View>> _views {};
	size_t _current_view_index = -1;

	std::shared_ptr<Session> _session = std::make_shared<Session>();
};
