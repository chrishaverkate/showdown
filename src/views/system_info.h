#pragma once

#include <showdown/system.h>

#include "view.h"

#include "showdown/screen.h"

#include <memory>

class SystemInfo : public View {
public:
	explicit SystemInfo(std::shared_ptr<System> system, std::shared_ptr<Screen> screen);
	~SystemInfo() override = default;
	void draw() override;
	void clear() override;

private:
	std::shared_ptr<System> _system;
	std::shared_ptr<Screen> _screen;
	bool _first_draw = true;

	void draw_structure();
};
