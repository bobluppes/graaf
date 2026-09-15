#include <benchmark/benchmark.h>
#include <graaflib/algorithm/coloring/greedy_graph_coloring.h>

#include "utils/dataset_reader.h"

namespace {

static void bm_greedy_graph_coloring(benchmark::State& state,
                                     const utils::dataset& dataset_name) {
  static const auto graph{utils::construct_graph_from_file(dataset_name)};

  for (auto _ : state) {
    auto result = graaf::algorithm::greedy_graph_coloring(graph);
    benchmark::DoNotOptimize(result);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_greedy_graph_coloring, web_google,
                  utils::dataset::WEB_GOOGLE);
BENCHMARK_CAPTURE(bm_greedy_graph_coloring, web_berkstan,
                  utils::dataset::WEB_BERK_STAN);
