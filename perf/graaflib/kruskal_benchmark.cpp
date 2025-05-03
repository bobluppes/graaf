#include <benchmark/benchmark.h>
#include <graaflib/algorithm/minimum_spanning_tree/kruskal.h>

#include "utils/dataset_reader.h"

namespace {

static void bm_kruskal(benchmark::State& state,
                       const utils::dataset& dataset_name) {
  static const auto graph{utils::construct_graph_from_file(dataset_name)};

  for (auto _ : state) {
    auto result = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
    benchmark::DoNotOptimize(result);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_kruskal, web_google, utils::dataset::WEB_GOOGLE);
BENCHMARK_CAPTURE(bm_kruskal, web_berkstan, utils::dataset::WEB_BERK_STAN);
