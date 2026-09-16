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
// 50k vertices was chosen empirically (see PR discussion) to bring the
// search close to 1 second on both datasets despite the above re-enqueue
// effect already being present at this scale.
constexpr std::size_t MAX_SUBGRAPH_VERTICES{50'000};

static void bm_bfs_shortest_path(benchmark::State& state,
                                 const utils::dataset& dataset_name,
                                 const graaf::vertex_id_t start_vertex) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};
  const auto connected_subgraph{utils::compute_connected_subgraph(
      graph, start_vertex, MAX_SUBGRAPH_VERTICES)};

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
                  1);
BENCHMARK_CAPTURE(bm_bfs_shortest_path, web_berkstan,
                  utils::dataset::WEB_BERK_STAN, 1);
