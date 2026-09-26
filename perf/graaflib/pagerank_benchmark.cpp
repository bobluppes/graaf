#include <benchmark/benchmark.h>
#include <graaflib/algorithm/ranking/pagerank.h>
#include <graaflib/graph.h>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <random>
#include <vector>

namespace {

// Builds a random directed graph in which every vertex has out_degree distinct
// outgoing edges, except for the first dangling_percentage percent of the
// vertices, which have none. Fixed seed so the benchmark input is
// reproducible across runs.
[[nodiscard]] graaf::directed_graph<int, int> create_random_graph(
    std::size_t vertex_count, std::size_t out_degree,
    std::size_t dangling_percentage) {
  std::mt19937 rng{42};
  std::uniform_int_distribution<std::size_t> random_index(0, vertex_count - 1);

  graaf::directed_graph<int, int> graph{};
  std::vector<graaf::vertex_id_t> vertices{};
  vertices.reserve(vertex_count);
  for (std::size_t i{0}; i < vertex_count; ++i) {
    vertices.push_back(graph.add_vertex(static_cast<int>(i)));
  }

  const auto dangling_count{vertex_count * dangling_percentage / 100};
  for (std::size_t i{dangling_count}; i < vertex_count; ++i) {
    std::size_t added{0};
    while (added < out_degree) {
      const auto target{vertices[random_index(rng)]};
      // add_edge throws on an existing edge, so duplicate targets are redrawn
      if (!graph.has_edge(vertices[i], target)) {
        graph.add_edge(vertices[i], target, 1);
        ++added;
      }
    }
  }

  return graph;
}

[[nodiscard]] graaf::directed_graph<int, int> create_graph_from_state(
    const benchmark::State& state) {
  return create_random_graph(static_cast<std::size_t>(state.range(0)),
                             static_cast<std::size_t>(state.range(1)),
                             static_cast<std::size_t>(state.range(2)));
}

void set_complexity_n(benchmark::State& state,
                      const graaf::directed_graph<int, int>& graph) {
  state.SetComplexityN(
      static_cast<std::int64_t>(graph.vertex_count() + graph.edge_count()));
}

}  // namespace

// How many iterations pagerank needs to converge depends on the structure of
// the input graph, which makes timings of different graphs hard to compare.
// With a tolerance that can never be reached, every run performs exactly
// fixed_iterations iterations, so this measures the cost of a single
// iteration, which should grow linearly in |V| + |E|.
static void pagerank_fixed_iterations(benchmark::State& state) {
  constexpr std::size_t fixed_iterations{20};
  constexpr double unreachable_tolerance{std::numeric_limits<double>::min()};

  const auto graph{create_graph_from_state(state)};

  for (auto _ : state) {
    auto result = graaf::algorithm::pagerank(graph, 0.85, unreachable_tolerance,
                                             fixed_iterations);
    benchmark::DoNotOptimize(result);
  }

  set_complexity_n(state, graph);
}

static void pagerank_until_convergence(benchmark::State& state) {
  const auto graph{create_graph_from_state(state)};

  for (auto _ : state) {
    auto result = graaf::algorithm::pagerank(graph);
    benchmark::DoNotOptimize(result);
  }

  set_complexity_n(state, graph);
}

// Arguments: {vertex count, out-degree, percentage of dangling vertices}.
// Each registration varies only the vertex count, so that Complexity() fits a
// single family of similarly shaped graphs.
BENCHMARK(pagerank_fixed_iterations) /* sparse */
    ->ArgsProduct({benchmark::CreateRange(1 << 10, 1 << 16, 4), {4}, {0}})
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(pagerank_fixed_iterations) /* dense */
    ->ArgsProduct({benchmark::CreateRange(1 << 10, 1 << 16, 4), {16}, {0}})
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(pagerank_fixed_iterations) /* half of the vertices dangling */
    ->ArgsProduct({benchmark::CreateRange(1 << 10, 1 << 16, 4), {4}, {50}})
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(pagerank_until_convergence) /* sparse */
    ->ArgsProduct({benchmark::CreateRange(1 << 10, 1 << 16, 4), {4}, {0}})
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(pagerank_until_convergence) /* half of the vertices dangling */
    ->ArgsProduct({benchmark::CreateRange(1 << 10, 1 << 16, 4), {4}, {50}})
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
