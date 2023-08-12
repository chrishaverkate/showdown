#include "controller_impl.h"

#include <utility>
#include "views/delta_table.h"
#include "views/home.h"
#include "views/system_info.h"
#include "views/time_table.h"
#include "views/timeline.h"

using std::make_unique;
using std::move;
using std::shared_ptr;
using std::unique_ptr;

void ControllerImpl::draw_current_view() {
	printf("\tController: draw_current_view\n");
	if(_views.empty()) {
		printf("Controller: no views to draw\n");
		return;
	}
	_views.at(_current_view_index)->activate();
	_views.at(_current_view_index)->draw();
}

void ControllerImpl::clear_current_view() {
	_views.at(_current_view_index)->deactivate();
	_views.at(_current_view_index)->clear();
}

void ControllerImpl::add_view(ViewType view_type, shared_ptr<Screen> screen) {
	switch (view_type) {
	case ViewType::HOME:
		add_view(make_unique<Home>(_session, screen));
		break;
	case ViewType::TIMELINE:
		add_view(make_unique<Timeline>(_session, screen));
		break;
	case ViewType::TIME_TABLE:
		add_view(make_unique<TimeTable>(_session, screen));
		break;
	case ViewType::DELTA_TABLE:
		add_view(make_unique<DeltaTable>(_session, screen));
		break;
	default:
		printf("Controller: unknown view type\n");
		break;
	}
}

const std::unique_ptr<ModelUpdatedReceiver>& ControllerImpl::add_view(ViewType view_type, std::shared_ptr<System> system, std::shared_ptr<Screen> screen) {
	switch (view_type) {
	case ViewType::SYSTEM_INFO:
		add_view(make_unique<SystemInfo>(system, screen));
		return reinterpret_cast<unique_ptr<ModelUpdatedReceiver>&&>(_views.back());
		break;
	}

}

void ControllerImpl::add_view(unique_ptr<View> view) {
	_views.push_back(std::move(view));

	if(_views.size() == 1) {
		_current_view_index = 0;
	}
}

void ControllerImpl::button_pressed_a(uint64_t current_time_us) {
    shot_detected(current_time_us);
}

void ControllerImpl::button_pressed_b(uint64_t current_time_us) {
	printf("\tController: starting new session - %llu\n", current_time_us);
	_session->start_new_session(current_time_us);
	_new_session_callback(current_time_us);
	clear_current_view();
	draw_current_view();
}

void ControllerImpl::button_pressed_up(uint64_t current_time_us) {
}

void ControllerImpl::button_pressed_down(uint64_t current_time_us) {
}

void ControllerImpl::button_pressed_left(uint64_t current_time_us) {
	clear_current_view();
	if (_current_view_index == 0) {
		_current_view_index = _views.size() - 1;
	} else {
		--_current_view_index;
	}


	draw_current_view();
}

void ControllerImpl::button_pressed_right(uint64_t current_time_us) {
	clear_current_view();
	_current_view_index = (_current_view_index + 1) % _views.size();
	draw_current_view();
}

void ControllerImpl::button_pressed_select(uint64_t current_time_us) {
}

void ControllerImpl::shot_detected(uint64_t current_time_us) {
	printf("\tController: shot detected - %llu\n", current_time_us);
	_session->add_shot(current_time_us);
	draw_current_view();
}

void ControllerImpl::override_session(std::shared_ptr<Session> session) {
	_session = std::move(session);
}

void ControllerImpl::register_new_session_callback(new_session_callback callback) {
	_new_session_callback = callback;
}
