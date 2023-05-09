#include "timeline.h"

Timeline::Timeline(std::shared_ptr<Session> session, std::shared_ptr<Screen> screen)
    : _session(std::move(session)),
    _screen(std::move(screen)) {
}

void Timeline::draw() {
	_screen->draw_text("  Timeline", 0, 0, Screen::FontSize::MEDIUM);
}

void Timeline::clear() {
	_screen->clear();
}
