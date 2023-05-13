#include <benchmark/benchmark.h>

#include <controller_impl.h>

static void shot_detected(benchmark::State& state) {
	ControllerImpl c;
	for (auto _ : state)
		c.shot_detected(0);
}

BENCHMARK(shot_detected);
