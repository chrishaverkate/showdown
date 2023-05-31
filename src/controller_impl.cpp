#include "controller_impl.h"
#include "views/delta_table.h"
#include "views/home.h"
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
	_views.at(_current_view_index)->draw();
}

void ControllerImpl::clear_current_view() {
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
	}
}

void ControllerImpl::add_view(unique_ptr<View> view) {
	_views.push_back(move(view));

	if(_views.size() == 1) {
		_current_view_index = 0;
	}
}

void ControllerImpl::button_pressed_a(uint64_t current_time_us) {
    shot_detected(current_time_us);
}

void ControllerImpl::button_pressed_b(uint64_t current_time_us) {
	printf("\tController: button pressed b - %llu\n", current_time_us);
	_session->start_new_session(current_time_us);
	clear_current_view();
	draw_current_view();
}

void ControllerImpl::button_pressed_up(uint64_t current_time_us) {
}

void ControllerImpl::button_pressed_down(uint64_t current_time_us) {
}

void ControllerImpl::button_pressed_left(uint64_t current_time_us) {
	_views.at(_current_view_index)->clear();
	_current_view_index = (_current_view_index - 1) % _views.size();
	clear_current_view();
	draw_current_view();
}

void ControllerImpl::button_pressed_right(uint64_t current_time_us) {
	_views.at(_current_view_index)->clear();
	_current_view_index = (_current_view_index + 1) % _views.size();
	clear_current_view();
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
	_session = session;
}

