#include <benchmark/benchmark.h>
#include <graaflib/algorithm/shortest_path/a_star.h>

namespace {

void bm_a_star_grid(benchmark::State& state) {
  const auto side{static_cast<graaf::vertex_id_t>(state.range(0))};
  const bool use_heuristic{state.range(1) != 0};
  graaf::graph<int, int, graaf::graph_type::UNDIRECTED> graph;
  for (graaf::vertex_id_t id{0}; id < side * side; ++id) {
    [[maybe_unused]] const auto vertex{graph.add_vertex(0)};
  }
  for (graaf::vertex_id_t row{0}; row < side; ++row) {
    for (graaf::vertex_id_t col{0}; col < side; ++col) {
      const auto id{row * side + col};
      if (col + 1 < side) {
        graph.add_edge(id, id + 1, 1);
      }
      if (row + 1 < side) {
        graph.add_edge(id, id + side, 1);
      }
    }
  }
  const auto heuristic{[side, use_heuristic](graaf::vertex_id_t id) {
    return use_heuristic
               ? static_cast<int>(2 * (side - 1) - id / side - id % side)
               : 0;
  }};
  for (auto _ : state) {
    auto result{
        graaf::algorithm::a_star_search(graph, 0, side * side - 1, heuristic)};
    if (!result || result->total_weight != static_cast<int>(2 * (side - 1))) {
      state.SkipWithError("Unexpected grid shortest path");
      break;
    }
    benchmark::DoNotOptimize(result);
  }
}

}  // namespace

BENCHMARK(bm_a_star_grid)
    ->Args({32, 0})
    ->Args({32, 1})
    ->Args({128, 0})
    ->Args({128, 1});
