#include "system_info.h"

SystemInfo::SystemInfo(std::shared_ptr<Screen> screen)
    : _screen(std::move(screen)) {
}

void SystemInfo::draw() {
	printf("\tSysInfo: draw\n");
	char buffer[15];

	draw_structure();

}

void SystemInfo::clear() {
	_screen->clear();
}

void SystemInfo::draw_structure() {
	_screen->draw_header("Sys Info");
	_screen->draw_divider_horizontal(_screen->get_height() / 2, 3);
}
