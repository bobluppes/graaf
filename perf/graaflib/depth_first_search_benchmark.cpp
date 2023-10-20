#include <benchmark/benchmark.h>
#include <graaflib/algorithm/graph_traversal/depth_first_search.h>

#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace {
template <typename EDGE_T>
[[nodiscard]] std::vector<graaf::vertex_id_t> create_vertices(
    graaf::directed_graph<int, EDGE_T>& graph, size_t n) {
  std::vector<graaf::vertex_id_t> vertices{};
  vertices.reserve(n);

  for (size_t i{0}; i < n; ++i) {
    vertices.push_back(graph.add_vertex(i));
  }

  return vertices;
}

template <typename EDGE_T>
[[nodiscard]] std::vector<graaf::vertex_id_t> create_vertices(
    graaf::undirected_graph<int, EDGE_T>& graph, size_t n) {
  std::vector<graaf::vertex_id_t> vertices{};
  vertices.reserve(n);

  for (size_t i{0}; i < n; ++i) {
    vertices.push_back(graph.add_vertex(i));
  }

  return vertices;
}

using seen_edges_t =
    std::unordered_multiset<graaf::edge_id_t, graaf::edge_id_hash>;
using edge_order_t =
    std::unordered_map<graaf::edge_id_t, std::size_t, graaf::edge_id_hash>;

struct record_edge_callback {
  seen_edges_t& seen_edges;
  edge_order_t& edge_order;
  mutable std::size_t edge_order_supplier{0};

  record_edge_callback(seen_edges_t& seen_edges, edge_order_t& edge_order)
      : seen_edges{seen_edges}, edge_order{edge_order} {}

  void operator()(const graaf::edge_id_t& edge) const {
    seen_edges.insert(edge);
    edge_order[edge] = edge_order_supplier++;
  }
};

struct path_template {
  std::vector<std::vector<int>> simple = {
      {2, 1}, {1, 3}, {3, 2}, {1, 1}, {2, 3}};
  std::vector<std::vector<int>> connected_cones = {
      {1, 2, 3, 4}, {1, 3, 4}, {1, 3}, {1, 2}, {1}};
  /* 6x6 matrix */
  std::vector<std::vector<int>> matrix = {{1, 6}, {1, 6}, {1, 6},
                                          {1, 6}, {1, 6}, {6}};
  std::vector<std::vector<int>> binary_tree = {{1, 2}};
  std::vector<std::vector<int>> ternary_tree = {{1, 2, 3}};
} graph_path;

void construct_graph(graaf::directed_graph<int, int>& graph,
                     const std::vector<graaf::vertex_id_t>& vertices,
                     std::vector<std::vector<int>>& construct_path,
                     int modify = 1) {
  int graph_path = 0;
  for (const auto& vertex : vertices) {
    for (const auto path : construct_path[graph_path]) {
      auto next_vertex = (vertex + path) * modify;
      if (next_vertex >= vertices.size()) break;
      graph.add_edge(vertex, vertices[next_vertex], 1);
    }
    if (++graph_path >= construct_path.size()) graph_path = 0;
  }
}

void construct_graph(graaf::undirected_graph<int, int>& graph,
                     const std::vector<graaf::vertex_id_t>& vertices,
                     std::vector<std::vector<int>>& construct_path,
                     int modify = 1) {
  int graph_path = 0;
  for (const auto& vertex : vertices) {
    for (const auto path : construct_path[graph_path]) {
      auto next_vertex = (vertex + path) * modify;

      if (next_vertex >= vertices.size()) break;
      graph.add_edge(vertex, vertices[next_vertex], 1);
    }
    if (++graph_path >= construct_path.size()) graph_path = 0;
  }
}
}  // namespace

static void dfs_all_nodes_traversal(benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};
  graaf::directed_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  construct_graph(graph, vertices, graph_path.simple);

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};

  for (auto _ : state) {
    graaf::algorithm::depth_first_traverse(
        graph, vertices.front(), record_edge_callback{seen_edges, edge_order});
  }

  state.SetComplexityN(state.range(0));
}

static void dfs_target_traversal(benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};

  graaf::directed_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  construct_graph(graph, vertices, graph_path.simple);

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};
  auto target_vertex = std::min(static_cast<graaf::vertex_id_t>(state.range(1)),
                                number_of_vertices);
  const auto termination_strategy{
      [target = vertices[target_vertex]](const graaf::vertex_id_t& vertex) {
        return vertex == target;
      }};

  for (auto _ : state) {
    graaf::algorithm::depth_first_traverse(
        graph, vertices.front(), record_edge_callback{seen_edges, edge_order},
        termination_strategy);
  }

  state.SetComplexityN(state.range(1));
}

static void dfs_target_traversal_matrix(benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};

  graaf::directed_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  construct_graph(graph, vertices, graph_path.matrix);

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};
  auto target_vertex = std::min(static_cast<graaf::vertex_id_t>(state.range(1)),
                                number_of_vertices);
  const auto termination_strategy{
      [target = vertices[target_vertex]](const graaf::vertex_id_t& vertex) {
        return vertex == target;
      }};

  for (auto _ : state) {
    graaf::algorithm::depth_first_traverse(
        graph, vertices.front(), record_edge_callback{seen_edges, edge_order},
        termination_strategy);
  }

  state.SetComplexityN(state.range(1));
}

static void dfs_target_traversal_cones(benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};

  graaf::directed_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  construct_graph(graph, vertices, graph_path.connected_cones);

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};
  auto target_vertex = std::min(static_cast<graaf::vertex_id_t>(state.range(1)),
                                number_of_vertices);
  const auto termination_strategy{
      [target = vertices[target_vertex]](const graaf::vertex_id_t& vertex) {
        return vertex == target;
      }};

  for (auto _ : state) {
    graaf::algorithm::depth_first_traverse(
        graph, vertices.front(), record_edge_callback{seen_edges, edge_order},
        termination_strategy);
  }

  state.SetComplexityN(state.range(1));
}

static void dfs_target_traversal_binary_tree(benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};

  graaf::directed_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  construct_graph(graph, vertices, graph_path.binary_tree, 2);

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};
  auto target_vertex = std::min(static_cast<graaf::vertex_id_t>(state.range(1)),
                                number_of_vertices);
  const auto termination_strategy{
      [target = vertices[target_vertex]](const graaf::vertex_id_t& vertex) {
        return vertex == target;
      }};

  for (auto _ : state) {
    graaf::algorithm::depth_first_traverse(
        graph, vertices.front(), record_edge_callback{seen_edges, edge_order},
        termination_strategy);
  }

  state.SetComplexityN(state.range(1));
}

static void dfs_target_traversal_ternary_tree(benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};

  graaf::directed_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  construct_graph(graph, vertices, graph_path.ternary_tree, 3);

  seen_edges_t seen_edges{};
  edge_order_t edge_order{};
  auto target_vertex = std::min(static_cast<graaf::vertex_id_t>(state.range(1)),
                                number_of_vertices);
  const auto termination_strategy{
      [target = vertices[target_vertex]](const graaf::vertex_id_t& vertex) {
        return vertex == target;
      }};

  for (auto _ : state) {
    graaf::algorithm::depth_first_traverse(
        graph, vertices.front(), record_edge_callback{seen_edges, edge_order},
        termination_strategy);
  }

  state.SetComplexityN(state.range(1));
}

BENCHMARK(dfs_all_nodes_traversal)
    ->Range(100, 300)
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(dfs_target_traversal)
    ->Ranges({{100, 10000}, {2, 8192}})
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(dfs_target_traversal_matrix)
    ->Ranges({{100, 10000}, {2, 8192}})
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(dfs_target_traversal_cones)
    ->Ranges({{100, 10000}, {2, 8192}})
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(dfs_target_traversal_binary_tree)
    ->Ranges({{100, 10000}, {2, 8192}})
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(dfs_target_traversal_ternary_tree)
    ->Ranges({{100, 10000}, {3, 8192}})
    ->Unit(benchmark::kMillisecond)
    ->Complexity();