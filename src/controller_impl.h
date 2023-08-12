#pragma once

#include <showdown/controller.h>
#include <showdown/screen.h>
#include <showdown/system.h>

#include "models/session.h"
#include "views/view.h"

#include <memory>
#include <vector>

class ControllerImpl : public Controller {
public:
	ControllerImpl() {printf("ControllerImpl: ctor\n");}
	~ControllerImpl() override = default;

	void draw_current_view() override;
	void clear_current_view();
	void add_view(ViewType view_type, std::shared_ptr<Screen> screen) override;
	void add_view(ViewType view_type, std::shared_ptr<System> system, std::shared_ptr<Screen> screen) override;

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

	void register_new_session_callback(new_session_callback callback) override;

private:
	new_session_callback _new_session_callback = &ControllerImpl::safe_new_session_callback;
	std::vector<std::unique_ptr<View>> _views {};
	size_t _current_view_index = -1;

	std::shared_ptr<Session> _session = std::make_shared<Session>();

	static void safe_new_session_callback(uint64_t current_time_us) { /* safer than nullptr */ }
};
