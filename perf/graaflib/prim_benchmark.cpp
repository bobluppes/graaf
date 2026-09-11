#include <benchmark/benchmark.h>
#include <graaflib/algorithm/graph_traversal/breadth_first_search.h>
#include <graaflib/algorithm/minimum_spanning_tree/prim.h>

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
// We deliberately do not also run an unbounded BFS to report the true full
// component size here: graaf::algorithm::breadth_first_traverse only marks a
// vertex as seen when it is popped, not when it is pushed, so it can
// re-enqueue and re-scan the same (especially high-degree) vertex many times
// before that. On the giant component this makes the edge callback fire tens
// of millions of times for a graph with only a few million edges, which is
// itself slow enough to reintroduce the runtime problem this cap exists to
// avoid.
constexpr std::size_t MAX_SUBGRAPH_VERTICES{2'400};

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

static void bm_prim(benchmark::State& state, const utils::dataset& dataset_name,
                    const graaf::vertex_id_t start_vertex) {
  static const auto graph{utils::construct_graph_from_file(dataset_name)};
  const auto connected_subgraph{
      compute_connected_subgraph(graph, start_vertex, MAX_SUBGRAPH_VERTICES)};

  state.counters["subgraph_vertices_used"] =
      static_cast<double>(connected_subgraph.vertex_count());

  for (auto _ : state) {
    auto result = graaf::algorithm::prim_minimum_spanning_tree(
        connected_subgraph, start_vertex);
    benchmark::DoNotOptimize(result);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_prim, web_google, utils::dataset::WEB_GOOGLE, 1);
BENCHMARK_CAPTURE(bm_prim, web_berkstan, utils::dataset::WEB_BERK_STAN, 1);
