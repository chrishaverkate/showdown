#include "system_info.h"

SystemInfo::SystemInfo(std::shared_ptr<System> system, std::shared_ptr<Screen> screen)
    : _system(std::move(system)),
    _screen(std::move(screen)) {
}

void SystemInfo::draw() {
	if (!_active) {
		return;
	}

	printf("\tSysInfo: draw\n");
	const char* usb_power = _system->get_usb_power() ? "ON" : "OFF";
	char buffer[15];

	if(_first_draw) {
		_first_draw = false;
		draw_structure();
	}

	_screen->draw_text(usb_power, 75, 10, Screen::FontSize::SMALL);

	snprintf(buffer, sizeof(buffer), "%.2f", _system->get_vsys_voltage());
	_screen->draw_text(buffer, 75, 30, Screen::FontSize::SMALL);

	float battery_percentage = _system->get_battery_percentage();

	if (battery_percentage > 100.0f) {
		snprintf(buffer, sizeof(buffer), "---");
	} else {
		snprintf(buffer, sizeof(buffer), "%.2u%%", static_cast<uint8_t>(battery_percentage));
	}
	_screen->draw_text(buffer, 75, 50, Screen::FontSize::SMALL);

	// if battery is > 100.0f -> draw charge symbol

	int battery_width = 87;
	int battery_height = 19;
	auto fill_color = Screen::Color::RED;
	int fill_width = static_cast<int>(battery_width * (battery_percentage / 100.0f));

	if (fill_width > battery_width) {
		fill_width = battery_width;
	}


	// Fill Battery
	if(battery_percentage > 80.0f) {
		fill_color = Screen::Color::GREEN;
	} else if(battery_percentage > 50.0f) {
		fill_color = Screen::Color::YELLOW;
	} else if(battery_percentage > 20.0f) {
		fill_color = Screen::Color::ORANGE;
	} else {
		fill_color = Screen::Color::RED;
	}

	_screen->draw_rectangle(2 + fill_width + 1, 71, battery_width - fill_width - 1, battery_height, Screen::Color::BLACK);
	_screen->draw_rectangle(2, 71, fill_width, battery_height, fill_color);
}

void SystemInfo::clear() {
	_screen->clear();
	_first_draw = true;
}

void SystemInfo::draw_structure() {
	_screen->draw_header("Sys Info");
	_screen->draw_text("USB Power: ", 1, 10, Screen::FontSize::SMALL);
	_screen->draw_text("Vsys Volt: ", 1, 30, Screen::FontSize::SMALL);
	_screen->draw_text("Battery %: ", 1, 50, Screen::FontSize::SMALL);

	// Battery shell
	_screen->draw_line(1, 70, 1, 90, 1);
	_screen->draw_line(1, 70, 90, 70, 1);
	_screen->draw_line(1, 90, 90, 90, 1);
	_screen->draw_line(90, 70, 90, 90, 1);
	_screen->draw_line(90, 75, 95, 75, 1);
	_screen->draw_line(90, 85, 95, 85, 1);
	_screen->draw_line(95, 75, 95, 85, 1);
}
void SystemInfo::model_updated() {
	draw();
}
