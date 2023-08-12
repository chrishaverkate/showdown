#pragma once
#include <cstdint>
#include <cstdlib>
#include <vector>

class System {
public:
	[[nodiscard]] virtual bool get_usb_power() const = 0;
	[[nodiscard]] virtual float get_vsys_voltage() const = 0;
	[[nodiscard]] virtual float get_battery_percentage() const = 0;

};
