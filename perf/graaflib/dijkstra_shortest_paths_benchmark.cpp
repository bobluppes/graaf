#include <benchmark/benchmark.h>
#include <graaflib/algorithm/shortest_path/dijkstra_shortest_paths.h>

#include "utils/dataset_reader.h"

namespace {

static void bm_dijkstra_shortest_paths(benchmark::State& state,
                                       const utils::dataset& dataset_name,
                                       const graaf::vertex_id_t start_vertex) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};

  for (auto _ : state) {
    auto result =
        graaf::algorithm::dijkstra_shortest_paths(graph, start_vertex);
    benchmark::DoNotOptimize(result);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_dijkstra_shortest_paths, web_google,
                  utils::dataset::WEB_GOOGLE, 1);
BENCHMARK_CAPTURE(bm_dijkstra_shortest_paths, web_berkstan,
                  utils::dataset::WEB_BERK_STAN, 1);
