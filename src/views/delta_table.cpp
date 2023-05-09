#include "delta_table.h"

DeltaTable::DeltaTable(std::shared_ptr<Session> session, std::shared_ptr<Screen> screen)
    : _session(std::move(session)),
    _screen(std::move(screen)) {
}

void DeltaTable::draw() {
	_screen->draw_text("Delta Table", 0, 0, Screen::FontSize::MEDIUM);
}

void DeltaTable::clear() {
	_screen->clear();
}
