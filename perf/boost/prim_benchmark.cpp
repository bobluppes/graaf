#include <benchmark/benchmark.h>

#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <vector>

#include "utils/connected_subgraph.h"

namespace {

// See the comment in perf/graaflib/prim_benchmark.cpp for why Prim needs to
// run on a bounded subgraph rather than the full dataset: it re-scans every
// fringe vertex's neighbor list on each iteration, so its runtime grows
// super-linearly with the size of the connected component it runs on, and
// almost any start vertex in these datasets falls in a giant component
// covering ~96-98% of all vertices.
static void bm_prim(benchmark::State& state, const utils::dataset& dataset_name,
                    const std::size_t start_vertex,
                    const std::size_t max_subgraph_vertices) {
  const auto subgraph{utils::construct_connected_subgraph(
      dataset_name, start_vertex, max_subgraph_vertices)};

  state.counters["subgraph_vertices_used"] =
      static_cast<double>(boost::num_vertices(subgraph.graph));

  std::vector<boost::graph_traits<utils::graph_t>::vertex_descriptor>
      predecessors(boost::num_vertices(subgraph.graph));

  for (auto _ : state) {
    boost::prim_minimum_spanning_tree(
        subgraph.graph,
        boost::make_iterator_property_map(
            predecessors.begin(),
            boost::get(boost::vertex_index, subgraph.graph)),
        boost::root_vertex(subgraph.start_vertex));
    benchmark::DoNotOptimize(predecessors);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_prim, web_google, utils::dataset::WEB_GOOGLE, 1, 85'000);
BENCHMARK_CAPTURE(bm_prim, web_berkstan, utils::dataset::WEB_BERK_STAN, 1,
                  80'000);
