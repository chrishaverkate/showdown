#include "time_table.h"

TimeTable::TimeTable(std::shared_ptr<Session> session, std::shared_ptr<Screen> screen)
    : _session(std::move(session)),
    _screen(std::move(screen)) {
}

void TimeTable::draw() {
	printf("\tTimeTable: draw\n");

	// TODO: Can I come up with a better way to only draw a "dirty region"?
	clear();

	_screen->draw_header(" #    t");
	_screen->draw_divider_vertical(40, 1);

	char buffer[15];

	uint first_position = 10;
	uint step_size = 20;
	uint position = first_position;
	uint shot_number = _session->get_shot_count();

	// TODO: Only draw new shots?
	auto shots = _session->get_shots();
	for(auto shot = shots.rbegin(); shot != shots.rend(); ++shot) {
		printf("\t\tdraw shot %llu\n", *shot);
		snprintf(buffer, sizeof(buffer), " %u    %.2f",
		         shot_number--,
		         Session::convert_time_to_seconds(*shot));
		_screen->draw_text(buffer, 1, position + 3, Screen::FontSize::MEDIUM);

		_screen->draw_divider_horizontal(position, 1);
		position += step_size;
	}
}

void TimeTable::clear() {
	_screen->clear();
}
