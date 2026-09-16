#include <benchmark/benchmark.h>
#include <graaflib/algorithm/shortest_path/dijkstra_shortest_path.h>
#include <graaflib/algorithm/shortest_path/dijkstra_shortest_paths.h>

#include <algorithm>

#include "utils/dataset_reader.h"

namespace {

// Picks the vertex farthest (by total edge weight) from start_vertex, so the
// single-pair search below has to explore close to the entire reachable
// graph before it can terminate early. A hardcoded/arbitrary target vertex
// id can happen to sit very close to start_vertex in one dataset and far in
// another, making the two datasets' results incomparable.
[[nodiscard]] graaf::vertex_id_t find_farthest_vertex(
    const utils::graph_t& graph, const graaf::vertex_id_t start_vertex) {
  const auto shortest_paths{
      graaf::algorithm::dijkstra_shortest_paths(graph, start_vertex)};

  return std::ranges::max_element(
             shortest_paths, {},
             [](const auto& entry) { return entry.second.total_weight; })
      ->first;
}

static void bm_dijkstra_shortest_path(benchmark::State& state,
                                      const utils::dataset& dataset_name,
                                      const graaf::vertex_id_t start_vertex) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};
  const auto end_vertex{find_farthest_vertex(graph, start_vertex)};

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
