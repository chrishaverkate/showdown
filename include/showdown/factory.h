#pragma once

#include "controller.h"

#include <memory>

class Factory {
public:
	static std::unique_ptr<Controller> create_controller();
};
