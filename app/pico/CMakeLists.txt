set(target_name ${CMAKE_PROJECT_NAME}_app)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

include_directories(${CMAKE_CURRENT_LIST_DIR}/lcd/lib/Config)
include_directories(${CMAKE_CURRENT_LIST_DIR}/lcd/lib/GUI)
include_directories(${CMAKE_CURRENT_LIST_DIR}/lcd/lib/LCD)
add_subdirectory(lcd)

add_executable(${target_name}
	main.cpp

	implementations/button.cpp
	implementations/lcd_screen.cpp
	implementations/pico_system.cpp
)

target_link_libraries(${target_name}
	pico_stdlib
	hardware_gpio
	hardware_i2c
	hardware_spi
	hardware_pwm
	${PROJECT_NAME}_lib

	# Screen libraries
	Config
	LCD
	GUI
	Fonts
)

set_target_properties(${target_name}
	PROPERTIES
		C_STANDARD 11
		CXX_STANDARD 17
)


# create map/bin/hex/uf2 file etc.
pico_add_extra_outputs(${target_name})

# Workaround for getting bin file to be copied from docker env when automated
add_custom_command(
	TARGET ${target_name}
	POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${target_name}> ${PRJ_APPS_OUTPUT_DIR}
	BYPRODUCTS ${PRJ_APPS_OUTPUT_DIR}/${target_name}
	COMMENT "Coping ${target_name} to: ${PRJ_APPS_OUTPUT_DIR}"
)
