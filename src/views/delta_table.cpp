#include "delta_table.h"

DeltaTable::DeltaTable(std::shared_ptr<Session> session, std::shared_ptr<Screen> screen)
    : _session(std::move(session)),
    _screen(std::move(screen)) {
}

void DeltaTable::draw() {
	printf("\tDeltaTable: draw\n");

	// TODO: Can I come up with a better way to only draw a "dirty region"?
	clear();

	_screen->draw_header(" #  split");
	_screen->draw_divider_vertical(40, 1);

	char buffer[15];

	uint8_t first_position = 10;
	uint8_t step_size = 20;
	uint8_t position = first_position;
	uint8_t shot_number = _session->get_shot_count();

	// TODO: Only draw new shots?
	auto shots = _session->get_shot_deltas();
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

void DeltaTable::clear() {
	_screen->clear();
}
