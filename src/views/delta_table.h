#pragma once

#include "../models/session.h"
#include "view.h"

#include "showdown/screen.h"

#include <memory>

class DeltaTable : public View {
public:
	explicit DeltaTable(std::shared_ptr<Session> session, std::shared_ptr<Screen> screen);
	~DeltaTable() override = default;
	void draw() override;
	void clear() override;

private:
	std::shared_ptr<Session> _session;
	std::shared_ptr<Screen> _screen;
};
