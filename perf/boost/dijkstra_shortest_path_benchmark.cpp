#include <benchmark/benchmark.h>

#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <vector>

#include "utils/dataset_reader.h"
#include "utils/farthest_vertex.h"

namespace {

// Thrown from the visitor below to unwind out of
// boost::dijkstra_shortest_paths as soon as the target vertex is settled,
// rather than letting it run to completion over the whole graph. This
// mirrors graaf::algorithm::dijkstra_shortest_path(), which returns as soon
// as it pops the end vertex from its queue.
struct target_reached {};

class stop_at_target_visitor : public boost::default_dijkstra_visitor {
 public:
  explicit stop_at_target_visitor(std::size_t target) : target_{target} {}

  void examine_vertex(std::size_t vertex, const utils::graph_t&) const {
    if (vertex == target_) {
      throw target_reached{};
    }
  }

 private:
  std::size_t target_;
};

static void bm_dijkstra_shortest_path(benchmark::State& state,
                                      const utils::dataset& dataset_name,
                                      const std::size_t start_vertex) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};
  const auto end_vertex{utils::find_farthest_vertex(graph, start_vertex)};

  std::vector<int> distances(boost::num_vertices(graph));

  for (auto _ : state) {
    try {
      boost::dijkstra_shortest_paths(
          graph, start_vertex,
          boost::distance_map(
              boost::make_iterator_property_map(
                  distances.begin(), boost::get(boost::vertex_index, graph)))
              .visitor(stop_at_target_visitor{end_vertex}));
    } catch (const target_reached&) {
    }
    benchmark::DoNotOptimize(distances[end_vertex]);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_dijkstra_shortest_path, web_google,
                  utils::dataset::WEB_GOOGLE, 1);
BENCHMARK_CAPTURE(bm_dijkstra_shortest_path, web_berkstan,
                  utils::dataset::WEB_BERK_STAN, 1);
