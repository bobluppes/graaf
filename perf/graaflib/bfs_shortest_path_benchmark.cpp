#include <benchmark/benchmark.h>
#include <graaflib/algorithm/graph_traversal/breadth_first_search.h>
#include <graaflib/algorithm/shortest_path/bfs_shortest_path.h>

#include "utils/dataset_reader.h"

namespace {

static void bm_bfs_shortest_path(benchmark::State& state,
                                 const utils::dataset& dataset_name,
                                 const graaf::vertex_id_t start_vertex) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};

  // Pick the vertex an exhaustive BFS over the graph dequeues last, so the
  // shortest-path search below has to do close to the maximum possible
  // amount of work before it can terminate early. An arbitrary vertex (e.g.
  // the highest id) would give no such guarantee and can make the search
  // terminate after visiting only a tiny, unrepresentative fraction of the
  // graph.
  graaf::vertex_id_t end_vertex{start_vertex};
  graaf::algorithm::breadth_first_traverse(
      graph, start_vertex, [](const graaf::edge_id_t&) {},
      [&end_vertex](graaf::vertex_id_t current) {
        end_vertex = current;
        return false;
      });

  for (auto _ : state) {
    auto result =
        graaf::algorithm::bfs_shortest_path(graph, start_vertex, end_vertex);
    benchmark::DoNotOptimize(result);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_bfs_shortest_path, web_google, utils::dataset::WEB_GOOGLE,
                  1);
BENCHMARK_CAPTURE(bm_bfs_shortest_path, web_berkstan,
                  utils::dataset::WEB_BERK_STAN, 1);
