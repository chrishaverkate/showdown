message("PRJ: Configuring options for Mac target")

#set(PRJ_APPS_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/" CACHE FILEPATH "Output directory to place binary files when built.")

option(PRJ_APPS_BUILD_PICO_BLINK "Build Pico specific applications" OFF)
option(PRJ_TESTS_BUILD "Unit tests" ON)

