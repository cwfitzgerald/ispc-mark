#include <benchmark/benchmark.h>
#include <ispc/src.h>
using namespace ispc;

static void BM_noop(benchmark::State& state) {
	constexpr std::size_t iterations = 100000;

	std::size_t count = 0;
	for (auto _ : state) {
		for (std::size_t i = 0; i < iterations; ++i) {
			noop();
		}
		count += iterations;
	}
	state.counters["Calls"] = benchmark::Counter(count, benchmark::Counter::kIsRate);
}
BENCHMARK(BM_noop);

static void BM_sum(benchmark::State& state) {
	int64_t size = state.range(0);
	float* array = new float[size];

	std::fill(array, array + size, 1);

	for (auto _ : state) {
		benchmark::DoNotOptimize(avg(array, size));
	}
	state.SetBytesProcessed(4 * int64_t(state.iterations()) * int64_t(size));
	delete[] array;
}
BENCHMARK(BM_sum)->RangeMultiplier(2)->Range(1 << 16, 1 << 26)->Unit(benchmark::kMicrosecond);
