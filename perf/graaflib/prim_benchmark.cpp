#include <benchmark/benchmark.h>
#include <graaflib/algorithm/graph_traversal/breadth_first_search.h>
#include <graaflib/algorithm/minimum_spanning_tree/prim.h>

#include <iostream>

#include "utils/dataset_reader.h"

namespace {

namespace {

[[nodiscard]] utils::graph_t compute_connected_subgraph(
    const utils::graph_t& graph, const graaf::vertex_id_t start_vertex) {
  utils::graph_t connected_subgraph{};

  graaf::algorithm::breadth_first_traverse(
      graph, start_vertex, [&connected_subgraph](const graaf::edge_id_t& edge) {
        const auto [source, target](edge);

        if (!connected_subgraph.has_vertex(source)) {
          connected_subgraph.add_vertex(utils::no_data{}, source);
        }

        if (!connected_subgraph.has_vertex(target)) {
          connected_subgraph.add_vertex(utils::no_data{}, target);
        }

        connected_subgraph.add_edge(source, target, 1);
      });

  return connected_subgraph;
}

}  // namespace

static void bm_prim(benchmark::State& state, const utils::dataset& dataset_name,
                    const graaf::vertex_id_t start_vertex) {
  static const auto graph{utils::construct_graph_from_file(dataset_name)};
  const auto connected_subgraph{
      compute_connected_subgraph(graph, start_vertex)};

  std::cout << "number of vertices in connected subgraph: "
            << connected_subgraph.vertex_count() << std::endl;

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
