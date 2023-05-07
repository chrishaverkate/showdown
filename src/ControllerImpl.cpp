#include "ControllerImpl.h"

using std::move;
using std::unique_ptr;

void ControllerImpl::draw_current_view() {
	_views.at(_current_view_index)->draw();
}

void ControllerImpl::add_view(ViewType view_type) {

	// TODO: for each view, get the correct model and create the view.
	switch (view_type) {
	case ViewType::HOME:
//		add_view(make_unique<Home>(get_model(view_type));
		break;
	case ViewType::TIMELINE:
		break;
	case ViewType::TIME_TABLE:
		break;
	case ViewType::DELTA_TABLE:
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
}

void ControllerImpl::button_pressed_b(uint64_t current_time_us) {
}

void ControllerImpl::button_pressed_up(uint64_t current_time_us) {
}

void ControllerImpl::button_pressed_down(uint64_t current_time_us) {
}

void ControllerImpl::button_pressed_left(uint64_t current_time_us) {
	_current_view_index = (_current_view_index - 1) % _views.size();
}

void ControllerImpl::button_pressed_right(uint64_t current_time_us) {
	_current_view_index = (_current_view_index + 1) % _views.size();
}

void ControllerImpl::button_pressed_select(uint64_t current_time_us) {
}

void ControllerImpl::shot_detected(uint64_t current_time_us) {
}
