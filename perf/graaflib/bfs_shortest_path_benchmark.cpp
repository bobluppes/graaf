#include <benchmark/benchmark.h>
#include <graaflib/algorithm/graph_traversal/breadth_first_search.h>
#include <graaflib/algorithm/shortest_path/bfs_shortest_path.h>

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

[[nodiscard]] utils::graph_t compute_connected_subgraph(
    const utils::graph_t& graph, const graaf::vertex_id_t start_vertex,
    const std::size_t max_vertices) {
  utils::graph_t connected_subgraph{};
  connected_subgraph.add_vertex(utils::no_data{}, start_vertex);

  const auto stop_once_full{
      [&connected_subgraph, max_vertices](graaf::vertex_id_t) {
        return connected_subgraph.vertex_count() >= max_vertices;
      }};

  graaf::algorithm::breadth_first_traverse(
      graph, start_vertex,
      [&connected_subgraph, max_vertices](const graaf::edge_id_t& edge) {
        const auto [source, target](edge);

        if (connected_subgraph.vertex_count() >= max_vertices) {
          return;
        }

        if (!connected_subgraph.has_vertex(source)) {
          connected_subgraph.add_vertex(utils::no_data{}, source);
        }

        if (!connected_subgraph.has_vertex(target)) {
          connected_subgraph.add_vertex(utils::no_data{}, target);
        }

        if (connected_subgraph.has_vertex(source) &&
            connected_subgraph.has_vertex(target) &&
            !connected_subgraph.has_edge(source, target)) {
          connected_subgraph.add_edge(source, target, 1);
        }
      },
      stop_once_full);

  return connected_subgraph;
}

static void bm_bfs_shortest_path(benchmark::State& state,
                                 const utils::dataset& dataset_name,
                                 const graaf::vertex_id_t start_vertex) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};
  const auto connected_subgraph{
      compute_connected_subgraph(graph, start_vertex, MAX_SUBGRAPH_VERTICES)};

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
