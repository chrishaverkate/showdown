#include <benchmark/benchmark.h>

#include <pico-demo/message.h>

static void get_hello(benchmark::State& state) {
	Message m;
	for (auto _ : state)
		auto hello = m.get_hello();
}

BENCHMARK(get_hello);
