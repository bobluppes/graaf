#include <benchmark/benchmark.h>
#include <graaflib/algorithm/graph_traversal/breadth_first_search.h>
#include <graaflib/algorithm/shortest_path/bfs_shortest_path.h>

#include "utils/connected_subgraph.h"
#include "utils/dataset_reader.h"

namespace {

// graaf::algorithm::breadth_first_traverse() only marks a vertex as seen when
// it is popped from the queue, not when it is pushed, so a high-degree vertex
// can be enqueued (and its neighbors re-scanned) many times before it is
// finally marked seen. On the giant connected component of these datasets
// (~96-98% of all vertices, see the comment in prim_benchmark.cpp for exact
// figures) this makes an exhaustive traversal fire the edge callback tens of
// millions of times, which is slow enough that the benchmark never finishes
// in a reasonable time. We therefore run the shortest path search on a
// bounded subgraph, same as the Prim MST benchmark does for the same reason.
//
// The cap is chosen per dataset (rather than sharing one constant) because
// the two giant components don't grow in density at the same rate as the
// BFS explores them: web-BerkStan's component hits a much denser cluster at
// a smaller vertex count than web-Google's does, so the same cap makes this
// search run for very different amounts of time on each dataset. The two
// values below were found empirically to bring both benchmarks close to 1
// second.
static void bm_bfs_shortest_path(benchmark::State& state,
                                 const utils::dataset& dataset_name,
                                 const graaf::vertex_id_t start_vertex,
                                 const std::size_t max_subgraph_vertices) {
  const auto connected_subgraph{utils::construct_connected_subgraph(
      dataset_name, start_vertex, max_subgraph_vertices)};

  // Pick the vertex an exhaustive BFS over the subgraph dequeues last, so the
  // shortest-path search below has to do close to the maximum possible
  // amount of work before it can terminate early. An arbitrary vertex (e.g.
  // the highest id) would give no such guarantee and can make the search
  // terminate after visiting only a tiny, unrepresentative fraction of the
  // subgraph.
  graaf::vertex_id_t end_vertex{start_vertex};
  graaf::algorithm::breadth_first_traverse(
      connected_subgraph, start_vertex, [](const graaf::edge_id_t&) {},
      [&end_vertex](graaf::vertex_id_t current) {
        end_vertex = current;
        return false;
      });

  state.counters["subgraph_vertices_used"] =
      static_cast<double>(connected_subgraph.vertex_count());

  for (auto _ : state) {
    auto result = graaf::algorithm::bfs_shortest_path(connected_subgraph,
                                                      start_vertex, end_vertex);
    benchmark::DoNotOptimize(result);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_bfs_shortest_path, web_google, utils::dataset::WEB_GOOGLE,
                  1, 20'000);
BENCHMARK_CAPTURE(bm_bfs_shortest_path, web_berkstan,
                  utils::dataset::WEB_BERK_STAN, 1, 1'700);
