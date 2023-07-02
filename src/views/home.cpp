#include "home.h"

Home::Home(std::shared_ptr<Session> session, std::shared_ptr<Screen> screen)
    : _session(std::move(session)),
    _screen(std::move(screen)) {
}

void Home::draw() {
	printf("\tHome: draw\n");
	char buffer[15];

	if (_last_shot_count == 0) {
		draw_structure();
	}

	_last_shot_count = _session->get_shot_count();
	double last_shot_seconds = Session::convert_time_to_seconds(_session->get_last_shot_time());
	int last_shot_whole_seconds = (int)last_shot_seconds;
	int last_shot_frac_seconds = (int)((last_shot_seconds - last_shot_whole_seconds) * 100);

	// Draw the time of the last shot
	_screen->draw_text("Time", 1, 10, Screen::FontSize::SMALL);

	snprintf(buffer, sizeof(buffer), "%02d", last_shot_whole_seconds);
	_screen->draw_text(buffer, 0, 30, Screen::FontSize::XL);

	snprintf(buffer, sizeof(buffer), ".%02d", last_shot_frac_seconds);
	_screen->draw_text(buffer, 75, 69, Screen::FontSize::LARGE);

	_screen->draw_text("Shots", 1, (_screen->get_height() / 2) + 10, Screen::FontSize::SMALL);

	// Draw the number of shots
	snprintf(buffer, sizeof(buffer), "%d", _last_shot_count);
	_screen->draw_text(buffer, 10, (_screen->get_height() / 2) + 30, Screen::FontSize::XL);
}

void Home::clear() {
	_screen->clear();
	_last_shot_count = 0;
}

void Home::draw_structure() {
	_screen->draw_header("Overview");
	_screen->draw_divider_horizontal(_screen->get_height() / 2, 3);
}
