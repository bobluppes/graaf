#include <benchmark/benchmark.h>
#include <graaflib/graph.h>
#include <graaflib/algorithm/cycle_detection/dfs_cycle_detection.h>

namespace {

template <typename EDGE_T, graaf::graph_type GRAPH_TYPE_V >
[[nodiscard]] std::vector<graaf::vertex_id_t> create_vertices(
    graaf::graph<int, EDGE_T, GRAPH_TYPE_V>& graph, size_t n) {
  std::vector<graaf::vertex_id_t> vertices{};
  vertices.reserve(n);

  for (size_t i{0}; i < n; ++i) {
    vertices.push_back(graph.add_vertex(i));
  }

  return vertices;
}

static void bm_dfs_cycle_detection_directed(benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};
  
  graaf::directed_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  // Linear Graph
  for (size_t i{0}; i < number_of_edges; ++i) {
    graph.add_edge(vertices[i], vertices[i+1], i);
  }

  for (auto _ : state) {
    auto result = graaf::algorithm::dfs_cycle_detection(graph);
    benchmark::DoNotOptimize(result);
  }
}

static void bm_dfs_cycle_detection_undirected(benchmark::State &state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};
  
  graaf::undirected_graph<int, int> graph{};


  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  // Linear Graph
  for (size_t i{0}; i < number_of_edges; ++i) {
    graph.add_edge(vertices[i], vertices[i+1], i);
  }

  for (auto _ : state) {
    auto result = graaf::algorithm::dfs_cycle_detection(graph);
    benchmark::DoNotOptimize(result);
  }
}
} // namespace

// Register the benchmarks
BENCHMARK(bm_dfs_cycle_detection_directed)->Range(100, 1000);
BENCHMARK(bm_dfs_cycle_detection_undirected) -> Range(100, 1000);