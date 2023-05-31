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
	static const constexpr uint8_t POSITION_FIRST_SHOT = 10;
	static const constexpr uint8_t STEP_SIZE = 20;

	std::shared_ptr<Session> _session;
	std::shared_ptr<Screen> _screen;
	size_t _last_shot_count = 0;

	void draw_structure();
};
