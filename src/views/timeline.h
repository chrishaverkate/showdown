#pragma once

#include "../models/session.h"
#include "view.h"

#include "showdown/screen.h"

#include <memory>

class Timeline : public View {
public:
	explicit Timeline(std::shared_ptr<Session> session, std::shared_ptr<Screen> screen);
	~Timeline() override = default;

	void draw() override;
	void clear() override;

private:
	std::shared_ptr<Session> _session;
	std::shared_ptr<Screen> _screen;
};
