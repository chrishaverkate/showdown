#pragma once

#include "../models/session.h"
#include "view.h"

#include "showdown/screen.h"

#include <memory>

class Home : public View {
public:
	explicit Home(std::shared_ptr<Session> session, std::shared_ptr<Screen> screen);
	~Home() override = default;
	void draw() override;
	void clear() override;

private:
	std::shared_ptr<Session> _session;
	std::shared_ptr<Screen> _screen;
	size_t _last_shot_count = 0;

	void draw_structure();
};
