#include <benchmark/benchmark.h>
#include <graaflib/algorithm/graph_traversal/breadth_first_search.h>

#include "utils/dataset_reader.h"

namespace {

static void bm_breadth_first_search(benchmark::State& state,
                                    const utils::dataset& dataset_name,
                                    const graaf::vertex_id_t start_vertex) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};

  for (auto _ : state) {
    std::size_t edges_visited{0};
    graaf::algorithm::breadth_first_traverse(
        graph, start_vertex,
        [&edges_visited](const graaf::edge_id_t&) { ++edges_visited; });
    benchmark::DoNotOptimize(edges_visited);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_breadth_first_search, web_google,
                  utils::dataset::WEB_GOOGLE, 1);
BENCHMARK_CAPTURE(bm_breadth_first_search, web_berkstan,
                  utils::dataset::WEB_BERK_STAN, 1);
