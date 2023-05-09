#include "time_table.h"

TimeTable::TimeTable(std::shared_ptr<Session> session, std::shared_ptr<Screen> screen)
    : _session(std::move(session)),
    _screen(std::move(screen)) {
}

void TimeTable::draw() {
	_screen->draw_text(" Time Table", 0, 0, Screen::FontSize::MEDIUM);
}

void TimeTable::clear() {
	_screen->clear();
}
