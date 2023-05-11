#include "timeline.h"

#include <vector>

using std::vector;

Timeline::Timeline(std::shared_ptr<Session> session, std::shared_ptr<Screen> screen)
    : _session(std::move(session)),
    _screen(std::move(screen)) {
}

void Timeline::draw() {
	_screen->draw_header(" #    t");
	_screen->draw_divider_vertical(40, 1);
	_screen->draw_divider_horizontal(190, 1);

	char buffer[15];

	uint first_position = 160;
	uint step_size = 20;
	uint position = first_position;
	uint shot_number = 1;

	for(auto shot : _session->get_shots()) {
		snprintf(buffer, sizeof(buffer), " %u    %.2f",
		         shot_number++,
		         Session::convert_time_to_seconds(shot));
		_screen->draw_text(buffer, 1, position - 5, Screen::FontSize::MEDIUM);

		_screen->draw_circle(40, position, 4, Screen::Color::GREEN);
		position -= step_size;
	}
}

void Timeline::clear() {
	_screen->clear();
}
