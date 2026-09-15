#include <benchmark/benchmark.h>
#include <graaflib/algorithm/shortest_path/dijkstra_shortest_path.h>

#include "utils/dataset_reader.h"

namespace {

static void bm_dijkstra_shortest_path(benchmark::State& state,
                                      const utils::dataset& dataset_name,
                                      const graaf::vertex_id_t start_vertex,
                                      const graaf::vertex_id_t end_vertex) {
  static const auto graph{utils::construct_graph_from_file(dataset_name)};

  for (auto _ : state) {
    auto result = graaf::algorithm::dijkstra_shortest_path(graph, start_vertex,
                                                           end_vertex);
    benchmark::DoNotOptimize(result);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_dijkstra_shortest_path, web_google,
                  utils::dataset::WEB_GOOGLE, 1, 916427);
BENCHMARK_CAPTURE(bm_dijkstra_shortest_path, web_berkstan,
                  utils::dataset::WEB_BERK_STAN, 1, 685230);
