#include "pico_system.h"

#include <pico/stdlib.h>
#include <hardware/adc.h>

#include "../pin_assignments.h"

bool PicoSystem::get_usb_power() const {
	return _usb_power;
}

float PicoSystem::get_vsys_voltage() const {
	return _vsys_voltage;
}

float PicoSystem::get_battery_percentage() const {
	return _battery_percentage;
}

void PicoSystem::update() {
	// wasn't working...
//	_usb_power = gpio_get(Pins::SENSE_USB_POWER) == 1;

	auto vsys_raw = adc_read();
	_vsys_voltage = static_cast<float>(vsys_raw) * CONVERSION_FACTOR;

	float level = 100.0f * ((_vsys_voltage - BATTERY_VOLTAGE_MIN) / (BATTERY_VOLTAGE_MAX - BATTERY_VOLTAGE_MIN));
	_battery_percentage = level;

	_usb_power = _battery_percentage > 100.0f;
}
