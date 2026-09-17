#include "dataset_reader.h"

#include <algorithm>
#include <map>

#include "common/dataset.h"

namespace utils {

namespace {

int UNIT_WEIGHT{1};

}  // namespace

const graph_t& construct_graph_from_file(const dataset& dataset_name) {
  static std::map<dataset, graph_t> cache{};
  if (const auto it{cache.find(dataset_name)}; it != cache.end()) {
    return it->second;
  }

  // boost::adjacency_list<vecS, ...> identifies vertices by a dense index
  // into an internal vector, so - unlike graaf's graph, which can add
  // vertices under arbitrary IDs on demand - the graph must be pre-sized to
  // the largest vertex ID seen in the dataset before any edges are added.
  std::size_t max_vertex_id{0};
  perf_common::read_dataset_edges(
      dataset_name,
      [&max_vertex_id](std::size_t source, std::size_t target) {
        max_vertex_id = std::max({max_vertex_id, source, target});
      });

  graph_t graph{max_vertex_id + 1};

  perf_common::read_dataset_edges(
      dataset_name, [&graph](std::size_t source, std::size_t target) {
        boost::add_edge(source, target, UNIT_WEIGHT, graph);
      });

  const auto [inserted_it,
              inserted]{cache.emplace(dataset_name, std::move(graph))};
  return inserted_it->second;
}

}  // namespace utils
