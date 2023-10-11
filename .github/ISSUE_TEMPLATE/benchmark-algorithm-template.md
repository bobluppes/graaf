---
name: Benchmark Algorithm Template
about: Template used for creating benchmark issues.
title: "[BENCH]"
labels: good first issue, help wanted, performance
assignees: ''

---

# Benchmark [ALGORITHM NAME]
The goal of this issues is to add a benchmark for the `[ALGORITHM NAME]` algorithm. The algorithm implementation is located under `include/graaflib/algorithm/`. Benchmarks are vital to our library and allow us to measure the impact of future performance improvements.

We use the [Google benchmark](https://github.com/google/benchmark/blob/main/docs/user_guide.md) framework. For inspiration, please take a look at the existing benchmarks in `/perf`.

The benchmark should be added under `/perf` in a directory which resembles the file structure of the original algorithm. i.e. if the algorithm is implemented in `include/graaflib/algorithm/coloring/greedy_graph_coloring.h` then the benchmark should be added to `perf/graaflib/algorithm/coloring/greedy_graph_coloring_benchmark.cpp`.

The benchmark should measure the runtime performance of the algorithm for increasing input sizes.

## Running Benchmarks
If you IDE has the necessary integrations for it, all benchmarks can be run in the IDE from the `perf/graaflib/benchmark.cpp` file.

Otherwise, we can run the benchmarks from the command line:
```bash
# run all benchmarks
cd build/perf && ./Graaf_perf
```

To run an individual benchmark:
```bash
./Graaf_perf --benchmark_filter=YOUR_BENCHMARK_NAME
```

For more options, pass the `--help` flag.


## Definition of Done
- [ ] A benchmark is added for the algorithm
- [ ] Benchmark results (copy past of the output is fine) is added to the PR
