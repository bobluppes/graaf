#include <benchmark/benchmark.h>

#include <boost/graph/sequential_vertex_coloring.hpp>
#include <vector>

#include "utils/dataset_reader.h"

namespace {

static void bm_greedy_graph_coloring(benchmark::State& state,
                                     const utils::dataset& dataset_name) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};

  std::vector<int> colors(boost::num_vertices(graph));
  const auto color_map{boost::make_iterator_property_map(
      colors.begin(), boost::get(boost::vertex_index, graph))};

  for (auto _ : state) {
    auto number_of_colors{boost::sequential_vertex_coloring(graph, color_map)};
    benchmark::DoNotOptimize(number_of_colors);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_greedy_graph_coloring, web_google,
                  utils::dataset::WEB_GOOGLE);
BENCHMARK_CAPTURE(bm_greedy_graph_coloring, web_berkstan,
                  utils::dataset::WEB_BERK_STAN);
