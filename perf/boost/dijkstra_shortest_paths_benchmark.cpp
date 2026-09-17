#include <benchmark/benchmark.h>

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <vector>

#include "utils/dataset_reader.h"

namespace {

static void bm_dijkstra_shortest_paths(benchmark::State& state,
                                       const utils::dataset& dataset_name,
                                       const std::size_t start_vertex) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};
  std::vector<int> distances(boost::num_vertices(graph));

  for (auto _ : state) {
    boost::dijkstra_shortest_paths(
        graph, start_vertex,
        boost::distance_map(boost::make_iterator_property_map(
            distances.begin(), boost::get(boost::vertex_index, graph))));
    benchmark::DoNotOptimize(distances);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_dijkstra_shortest_paths, web_google,
                  utils::dataset::WEB_GOOGLE, 1);
BENCHMARK_CAPTURE(bm_dijkstra_shortest_paths, web_berkstan,
                  utils::dataset::WEB_BERK_STAN, 1);
