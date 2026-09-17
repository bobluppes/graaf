#include <benchmark/benchmark.h>

#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <iterator>
#include <vector>

#include "utils/dataset_reader.h"

namespace {

static void bm_kruskal(benchmark::State& state,
                       const utils::dataset& dataset_name) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};

  std::vector<boost::graph_traits<utils::graph_t>::edge_descriptor>
      spanning_tree{};

  for (auto _ : state) {
    spanning_tree.clear();
    boost::kruskal_minimum_spanning_tree(graph,
                                         std::back_inserter(spanning_tree));
    benchmark::DoNotOptimize(spanning_tree);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_kruskal, web_google, utils::dataset::WEB_GOOGLE);
BENCHMARK_CAPTURE(bm_kruskal, web_berkstan, utils::dataset::WEB_BERK_STAN);
