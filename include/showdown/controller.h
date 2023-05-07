#pragma once

#include "view_type.h"

class Controller {
public:
	virtual ~Controller() = default;

	virtual void draw_current_view() = 0;

	virtual void add_view(ViewType view_type) = 0;
};
