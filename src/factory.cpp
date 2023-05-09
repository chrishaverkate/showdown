#include <showdown/factory.h>

#include "controller_impl.h"

#include <memory>

std::unique_ptr<Controller> Factory::create_controller() {
	printf("Factory: create_controller\n");
	return std::make_unique<ControllerImpl>();
}
