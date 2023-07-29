#pragma once

// TODO: create new model for collecting system data (voltage, etc).
//#include "../models/session.h"

#include "view.h"

#include "showdown/screen.h"

#include <memory>

class SystemInfo : public View {
public:
	explicit SystemInfo(std::shared_ptr<Screen> screen);
	~SystemInfo() override = default;
	void draw() override;
	void clear() override;

private:
//	std::shared_ptr<Session> _session;
	std::shared_ptr<Screen> _screen;

	void draw_structure();
};
