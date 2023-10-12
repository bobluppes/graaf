#include <benchmark/benchmark.h>
#include <graaflib/algorithm/clique_detection/bron_kerbosch.h>
#include <graaflib/graph.h>

#include <random>
#include <vector>

namespace {

// Generating random number of vertices (1- 30) for a clique
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> random_clique_size(1,
                                                                            30);

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

template <typename EDGE_T>
void add_clique(graaf::undirected_graph<int, EDGE_T>& graph,
                const std::vector<graaf::vertex_id_t>& vertices,
                size_t start_vertex, size_t clique_size) {
  // We are in range of vector of vertices
  size_t end_vertex = std::min(start_vertex + clique_size, vertices.size());
  std::vector<graaf::edge_id_t> clique{};
  clique.reserve((clique_size * (clique_size - 1)) / 2);

  // Constructing a clique
  for (size_t i{start_vertex}; i < end_vertex; ++i) {
    for (size_t j{i + 1}; j < end_vertex; ++j) {
      clique.emplace_back(vertices[i], vertices[j]);
    }
  }

  for (auto& edge_t : clique) {
    graph.add_edge(edge_t.first, edge_t.second, 1);
  }
}
}  // namespace

static void bron_kerbosh_two_vertices_cliques(benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};

  graaf::undirected_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  for (auto _ : state) {
    for (size_t i{0}; i < number_of_edges; ++i) {
      graph.add_edge(vertices[i], vertices[i + 1], 1);
    }
  }

  graaf::algorithm::bron_kerbosch(graph);
  state.SetComplexityN(state.range(0));
}

static void bron_kerbosh_dense_graph(benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};

  graaf::undirected_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  for (auto _ : state) {
    for (size_t i{0}; i < number_of_edges; ++i) {
      for (size_t j{i + 1}; j < number_of_edges; ++j) {
        if (i != j && !graph.has_edge(vertices[i], vertices[j]))
          graph.add_edge(vertices[i], vertices[j], 1);
      }
    }
  }

  graaf::algorithm::bron_kerbosch(graph);
  state.SetComplexityN(state.range(0));
}

static void bron_kerbosh_graph_triangle_cliques(benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};

  graaf::undirected_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  size_t clique_size = 4;

  for (auto _ : state) {
    for (size_t i{0}; i < number_of_edges; i += clique_size) {
      std::vector<graaf::edge_id_t> clique{};
      add_clique(graph, vertices, i, clique_size);
    }
  }

  graaf::algorithm::bron_kerbosch(graph);
  state.SetComplexityN(state.range(0));
}

static void bron_kerbosh_graph_connected_triangle_cliques(
    benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};

  graaf::undirected_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  size_t clique_size = 4;

  for (auto _ : state) {
    // Connecting all cliques
    for (size_t i{0}; i + clique_size < number_of_edges; i += clique_size) {
      graph.add_edge(vertices[i], vertices[i + clique_size], 1);
    }

    for (size_t i{0}; i < number_of_edges; i += clique_size) {
      std::vector<graaf::edge_id_t> clique{};
      add_clique(graph, vertices, i, clique_size);
    }
  }

  graaf::algorithm::bron_kerbosch(graph);
  state.SetComplexityN(state.range(0));
}

static void bron_kerbosh_graph_large_cliques(benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};

  graaf::undirected_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  size_t clique_size = 25;

  for (auto _ : state) {
    for (size_t i{0}; i < number_of_edges; i += clique_size) {
      std::vector<graaf::edge_id_t> clique{};
      add_clique(graph, vertices, i, clique_size);
    }
  }

  graaf::algorithm::bron_kerbosch(graph);
  state.SetComplexityN(state.range(0));
}

static void bron_kerbosh_graph_mixed_random_cliques(benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};

  graaf::undirected_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  size_t clique_size = 3;

  for (auto _ : state) {
    for (size_t i{0}; i + clique_size < number_of_edges; i += clique_size) {
      std::vector<graaf::edge_id_t> clique{};
      add_clique(graph, vertices, i, clique_size++);

      clique_size = random_clique_size(rng);
    }
  }

  graaf::algorithm::bron_kerbosch(graph);
  state.SetComplexityN(state.range(0));
}

static void bron_kerbosh_graph_connected_mixed_random_cliques(
    benchmark::State& state) {
  const auto number_of_edges{static_cast<size_t>(state.range(0))};

  graaf::undirected_graph<int, int> graph{};

  // We create enough vertices to construct the requested number of edges
  const auto number_of_vertices{number_of_edges + 1};
  const auto vertices{create_vertices(graph, number_of_vertices)};

  size_t clique_size = 3;

  for (auto _ : state) {
    // Connecting all cliques
    for (size_t i{0}; i < number_of_edges; ++i) {
      graph.add_edge(vertices[i], vertices[i + 1], 1);
    }

    for (size_t i{0}; i + clique_size < number_of_edges; i += clique_size) {
      std::vector<graaf::edge_id_t> clique{};
      add_clique(graph, vertices, i, clique_size++);

      clique_size = random_clique_size(rng);
    }
  }

  graaf::algorithm::bron_kerbosch(graph);
  state.SetComplexityN(state.range(0));
}

BENCHMARK(bron_kerbosh_two_vertices_cliques)
    ->Range(100, 10000)
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(bron_kerbosh_dense_graph) /* large amount of vertices to process */
    ->Range(100, 1000)
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(bron_kerbosh_graph_triangle_cliques)
    ->Range(100, 10000)
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(bron_kerbosh_graph_connected_triangle_cliques)
    ->Range(100, 10000)
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(bron_kerbosh_graph_large_cliques)
    ->Range(100, 10000)
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(bron_kerbosh_graph_mixed_random_cliques)
    ->Range(100, 10000)
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(bron_kerbosh_graph_connected_mixed_random_cliques)
    ->Range(100, 10000)
    ->Unit(benchmark::kMillisecond)
    ->Complexity();