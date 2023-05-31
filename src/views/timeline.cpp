#include "timeline.h"

#include <vector>

using std::vector;

Timeline::Timeline(std::shared_ptr<Session> session, std::shared_ptr<Screen> screen)
    : _session(std::move(session)), _screen(std::move(screen)) {
}

void Timeline::draw() {
	printf("\tTimeline: draw\n");
	char buffer[15];

	if (_last_shot_count == 0) {
		draw_structure();
	}

	uint8_t position = POSITION_FIRST_SHOT - (STEP_SIZE * _last_shot_count);

	auto shots = _session->get_shots();
	for (size_t i(_last_shot_count); i < shots.size(); ++i) {
		_last_shot_count++;
		auto shot = shots.at(i);
		printf("\t\tdraw shot %llu\n", shot);
		snprintf(buffer,
		         sizeof(buffer),
		         " %u    %.2f",
		         _last_shot_count,
		         Session::convert_time_to_seconds(shot));

		_screen->draw_text(buffer, 1, position - 5, Screen::FontSize::MEDIUM);
		_screen->draw_circle(40, position, 4, Screen::Color::GREEN);
		position -= STEP_SIZE;
	}
}

void Timeline::clear() {
	_screen->clear();
	_last_shot_count = 0;
}

void Timeline::draw_structure() {
	_screen->draw_header(" #    t");
	_screen->draw_divider_vertical(40, 1);
	_screen->draw_divider_horizontal(190, 1);
}
