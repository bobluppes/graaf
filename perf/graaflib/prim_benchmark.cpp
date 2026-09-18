#include <benchmark/benchmark.h>
#include <graaflib/algorithm/minimum_spanning_tree/prim.h>

#include "utils/connected_subgraph.h"
#include "utils/dataset_reader.h"

namespace {

// graaf::algorithm::prim_minimum_spanning_tree() re-scans every fringe
// vertex's neighbor list on each iteration (see prim.tpp), so its runtime
// grows super-linearly with the size of the connected component it runs on.
//
// Both datasets used here consist of one giant connected component covering
// ~96-98% of all vertices (855,802 / 875,713 for web-Google; 654,782 /
// 685,230 for web-BerkStan, measured offline with a union-find pass over the
// raw edge list) plus thousands of components with only a few hundred
// vertices. There is no "medium sized" component to land on via a lucky
// choice of start vertex - almost any start vertex, including the vertex 1
// used below, falls in the giant component. Running Prim directly on the
// giant component takes well over an hour, so we cap the number of vertices
// the connected-subgraph BFS explores to keep the benchmark bounded
// regardless of which component the start vertex falls into.
//
// The cap is chosen per dataset (rather than sharing one constant) because
// the two giant components don't grow in density at the same rate as the
// BFS explores them: web-BerkStan's component hits a much denser cluster at
// a smaller vertex count than web-Google's does, so the same cap makes Prim
// run for very different amounts of time on each dataset. The two values
// below were found empirically to bring both benchmarks close to 1 second.

static void bm_prim(benchmark::State& state, const utils::dataset& dataset_name,
                    const graaf::vertex_id_t start_vertex,
                    const std::size_t max_subgraph_vertices) {
  const auto [connected_subgraph,
              subgraph_start_vertex]{utils::construct_connected_subgraph(
      dataset_name, start_vertex, max_subgraph_vertices)};

  state.counters["subgraph_vertices_used"] =
      static_cast<double>(connected_subgraph.vertex_count());

  for (auto _ : state) {
    auto result = graaf::algorithm::prim_minimum_spanning_tree(
        connected_subgraph, subgraph_start_vertex);
    benchmark::DoNotOptimize(result);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_prim, web_google, utils::dataset::WEB_GOOGLE, 1, 85'000);
BENCHMARK_CAPTURE(bm_prim, web_berkstan, utils::dataset::WEB_BERK_STAN, 1,
                  80'000);
