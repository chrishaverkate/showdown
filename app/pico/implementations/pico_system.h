#pragma once
#include <showdown/system.h>

class PicoSystem : public System {
public:
	[[nodiscard]] bool get_usb_power() const override;
	[[nodiscard]] float get_vsys_voltage() const override;
	[[nodiscard]] float get_battery_percentage() const override;

	void update();

private:
	// I don't know why it's x3. It's what is referenced online and the value matches measurements.
	static const constexpr float CONVERSION_FACTOR = 3.0 * 3.3f / (1 << 12);

	static const constexpr float BATTERY_VOLTAGE_MIN = 2.8f;
	static const constexpr float BATTERY_VOLTAGE_MAX = 4.2f;

	bool _usb_power = false;
	float _vsys_voltage = 0.0f;
	float _battery_percentage = 0.0f;
};
