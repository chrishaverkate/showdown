#include "home.h"

Home::Home(std::shared_ptr<Session> session, std::shared_ptr<Screen> screen)
    : _session(std::move(session)),
    _screen(std::move(screen)) {
}

void Home::draw() {
	_screen->draw_text("    Home", 0, 0, Screen::FontSize::MEDIUM);
}

void Home::clear() {
	_screen->clear();
}
