#include <benchmark/benchmark.h>

#include <algorithm>
#include <boost/graph/sequential_vertex_coloring.hpp>
#include <vector>

#include "utils/dataset_reader.h"

namespace {

// Welsh-Powell is sequential greedy coloring (assign each vertex the
// smallest color not used by its already-colored neighbors) applied in
// descending-degree vertex order, rather than boost::sequential_vertex_
// coloring()'s default vertex-index order. Boost supports this directly by
// accepting a custom order.
static void bm_welsh_powell_coloring(benchmark::State& state,
                                     const utils::dataset& dataset_name) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};

  std::vector<boost::graph_traits<utils::graph_t>::vertex_descriptor> order(
      boost::vertices(graph).first, boost::vertices(graph).second);
  std::vector<int> colors(boost::num_vertices(graph));
  const auto color_map{boost::make_iterator_property_map(
      colors.begin(), boost::get(boost::vertex_index, graph))};

  for (auto _ : state) {
    std::ranges::sort(order, std::greater<>{}, [&graph](const auto vertex) {
      return boost::degree(vertex, graph);
    });
    const auto order_map{boost::make_iterator_property_map(
        order.begin(), boost::identity_property_map{})};

    auto number_of_colors{
        boost::sequential_vertex_coloring(graph, order_map, color_map)};
    benchmark::DoNotOptimize(number_of_colors);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_welsh_powell_coloring, web_google,
                  utils::dataset::WEB_GOOGLE);
BENCHMARK_CAPTURE(bm_welsh_powell_coloring, web_berkstan,
                  utils::dataset::WEB_BERK_STAN);
