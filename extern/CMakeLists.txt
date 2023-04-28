
if(PRJ_APPS_BUILD_PICO_BLINK)
	add_subdirectory(pico-sdk)
endif()

if(PRJ_TESTS_BUILD)
	add_subdirectory(googletest)

	set(BENCHMARK_ENABLE_TESTING OFF)
	add_subdirectory(benchmark)
endif()
