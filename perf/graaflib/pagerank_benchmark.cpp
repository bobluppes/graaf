#include <benchmark/benchmark.h>
#include <graaflib/algorithm/ranking/pagerank.h>
#include <graaflib/graph.h>

#include <random>
#include <vector>

namespace {

[[nodiscard]] graaf::directed_graph<int, int> make_random_digraph(
    std::size_t vertex_count, std::size_t edge_count, unsigned seed,
    double dangling_fraction = 0.0) {
  graaf::directed_graph<int, int> graph{};

  std::vector<graaf::vertex_id_t> vertices{};
  vertices.reserve(vertex_count);
  for (std::size_t i = 0; i < vertex_count; ++i) {
    vertices.push_back(graph.add_vertex(static_cast<int>(i)));
  }

  const std::size_t first_active =
      static_cast<std::size_t>(vertex_count * dangling_fraction);

  // Vertices [0, first_active) stay dangling (no outgoing edges).
  // This exercises the dangling-rank redistribution path in pagerank.
  std::size_t source_range = vertex_count - first_active;
  if (source_range == 0) {
    source_range = 1;
  }

  std::mt19937 rng(seed);
  std::uniform_int_distribution<std::size_t> pick_source(0, source_range - 1);
  std::uniform_int_distribution<std::size_t> pick_target(0, vertex_count - 1);

  for (std::size_t i = 0; i < edge_count; ++i) {
    const std::size_t s_idx = first_active + pick_source(rng);
    std::size_t t_idx = pick_target(rng);
    if (vertices[s_idx] == vertices[t_idx]) {
      // Avoid self-loop dominating the benchmark input; keep it simple.
      t_idx = (t_idx + 1) % vertex_count;
    }
    const auto u = vertices[s_idx];
    const auto v = vertices[t_idx];
    if (!graph.has_edge(u, v)) {
      graph.add_edge(u, v, 1);
    }
  }

  return graph;
}

static void bm_pagerank_sparse(benchmark::State& state) {
  const std::size_t n = static_cast<std::size_t>(state.range(0));
  // Keep edge count roughly linear so we can report Complexity in N.
  const std::size_t m = n * 5;
  auto graph = make_random_digraph(n, m, 42, 0.0);

  for (auto _ : state) {
    auto result = graaf::algorithm::pagerank(graph);
    benchmark::DoNotOptimize(result);
  }

  state.SetComplexityN(static_cast<long>(n));
}

static void bm_pagerank_with_dangling(benchmark::State& state) {
  const std::size_t n = static_cast<std::size_t>(state.range(0));
  const std::size_t m = n * 5;
  // ~40% dangling vertices stresses the rank-redistribution branch.
  auto graph = make_random_digraph(n, m, 1337, 0.4);

  for (auto _ : state) {
    auto result = graaf::algorithm::pagerank(graph);
    benchmark::DoNotOptimize(result);
  }

  state.SetComplexityN(static_cast<long>(n));
}

}  // namespace

BENCHMARK(bm_pagerank_sparse)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 15)
    ->Complexity(benchmark::oN);

BENCHMARK(bm_pagerank_with_dangling)
    ->RangeMultiplier(4)
    ->Range(1 << 10, 1 << 15)
    ->Complexity(benchmark::oN);
