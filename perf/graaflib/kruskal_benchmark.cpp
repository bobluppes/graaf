#include <benchmark/benchmark.h>
#include <graaflib/algorithm/minimum_spanning_tree/kruskal.h>
#include <graaflib/graph.h>

#include <filesystem>
#include <fstream>
#include <string>
#include <unordered_map>

namespace {

struct graph_file {
  std::filesystem::path filename{};
  std::size_t number_of_header_lines{};
};

enum class dataset : int64_t { WEB_GOOGLE, WEB_BERK_STAN };

const std::unordered_map<dataset, graph_file> DATASETS{
    {dataset::WEB_GOOGLE, graph_file{.filename = "input_data/web-Google.txt",
                                     .number_of_header_lines = 4}},
    {dataset::WEB_BERK_STAN,
     graph_file{.filename = "input_data/web-BerkStan.txt",
                .number_of_header_lines = 4}}};

struct no_data {};
int UNIT_WEIGHT{1};
using graph_t = graaf::undirected_graph<no_data, int>;

[[nodiscard]] graph_t construct_graph_from_file(const dataset& dataset_name) {
  const auto& dataset{DATASETS.at(dataset_name)};

  std::ifstream file{};
  file.open(dataset.filename);
  assert(file.is_open());

  std::string line;

  // Skip the header lines
  for (int i{0}; i < dataset.number_of_header_lines; ++i) {
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

static void bm_kruskal(benchmark::State& state, const dataset& dataset_name) {
  static const auto graph{construct_graph_from_file(dataset_name)};

  for (auto _ : state) {
    auto result = graaf::algorithm::kruskal_minimum_spanning_tree(graph);
    benchmark::DoNotOptimize(result);
  }
}

}  // namespace

// Register the benchmarks
static void CustomArguments(benchmark::internal::Benchmark* b) {
  b->Iterations(3);
}

BENCHMARK_CAPTURE(bm_kruskal, web_google, dataset::WEB_GOOGLE)
    ->Apply(CustomArguments);
BENCHMARK_CAPTURE(bm_kruskal, web_berkstan, dataset::WEB_BERK_STAN)
    ->Apply(CustomArguments);
