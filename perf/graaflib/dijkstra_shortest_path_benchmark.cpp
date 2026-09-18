#include <benchmark/benchmark.h>
#include <graaflib/algorithm/shortest_path/dijkstra_shortest_path.h>

#include "utils/dataset_reader.h"
#include "utils/farthest_vertex.h"

namespace {

static void bm_dijkstra_shortest_path(benchmark::State& state,
                                      const utils::dataset& dataset_name,
                                      const graaf::vertex_id_t start_vertex) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};
  const auto end_vertex{utils::find_farthest_vertex(graph, start_vertex)};

  for (auto _ : state) {
    auto result = graaf::algorithm::dijkstra_shortest_path(graph, start_vertex,
                                                           end_vertex);
    benchmark::DoNotOptimize(result);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_dijkstra_shortest_path, web_google,
                  utils::dataset::WEB_GOOGLE, 1);
BENCHMARK_CAPTURE(bm_dijkstra_shortest_path, web_berkstan,
                  utils::dataset::WEB_BERK_STAN, 1);
