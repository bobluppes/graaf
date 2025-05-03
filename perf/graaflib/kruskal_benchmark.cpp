#include <benchmark/benchmark.h>
#include <graaflib/algorithm/minimum_spanning_tree/kruskal.h>
#include <graaflib/graph.h>

#include <filesystem>
#include <fstream>
#include <string>

namespace {

const std::filesystem::path IN_FILE{"./web-Google.txt"};
const std::size_t NUM_HEADER_LINES{4};

struct no_data {};
int UNIT_WEIGHT{1};
using graph_t = graaf::undirected_graph<no_data, int>;

[[nodiscard]] graph_t construct_graph_from_file() {
  std::ifstream file{};
  file.open(IN_FILE);
  assert(file.is_open());

  std::string line;

  // Skip the header lines
  for (int i{0}; i < NUM_HEADER_LINES; ++i) {
    std::getline(file, line);
  }

  graph_t graph{};

  while (std::getline(file, line)) {
    const auto delim{line.find("\t")};
    const auto source{std::stoi(line.substr(0, delim))};
    const auto target{std::stoi(line.substr(delim, line.size() - delim))};

    if (!graph.has_vertex(source)) {
      graph.add_vertex(no_data{}, source);
    }

    if (!graph.has_vertex(target)) {
      graph.add_vertex(no_data{}, target);
    }

    graph.add_edge(source, target, UNIT_WEIGHT);
  }

  return graph;
}

static void bm_prim_mst(benchmark::State& state) {
  static const auto graph{construct_graph_from_file()};

  for (auto _ : state) {
    auto result = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
    benchmark::DoNotOptimize(result);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK(bm_prim_mst)->Iterations(3);
