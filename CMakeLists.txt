cmake_minimum_required(VERSION 3.18)
cmake_policy(SET CMP0077 NEW)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

if(NOT DEFINED PRJ_TARGET)
	message(FATAL_ERROR "No Project target defined. Set PRJ_TARGET to supported platform")
endif()

if(PRJ_TARGET STREQUAL "pico")
	# pico-sdk must be initialized before the project command because it sets CMAKE_TOOLCHAIN_FILE
	message("Project target is Pico, adding sdk init")
	include(${CMAKE_SOURCE_DIR}/extern/pico-sdk/pico_sdk_init.cmake)
	set(build_options cmake/build-options/pico.cmake) # Defines options / settings specific to the pico platform
elseif(PRJ_TARGET STREQUAL "linux")
	set(CMAKE_TOOLCHAIN_FILE cmake/toolchains/linux-amd64.cmake)
	set(build_options cmake/build-options/linux.cmake)
elseif(PRJ_TARGET STREQUAL "mac")
	set(CMAKE_TOOLCHAIN_FILE cmake/toolchains/mac-arm64.cmake)
	set(build_options cmake/build-options/mac.cmake)
endif()

#set(CMAKE_VERBOSE_MAKEFILE ON)


project(showdown
	LANGUAGES C CXX ASM
	VERSION 0.1.0
)

include(${build_options})

add_subdirectory(app)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(extern)

if(PRJ_TESTS_BUILD)
	add_subdirectory(tests)
endif()

include(project-build-summary)
