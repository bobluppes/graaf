#include "dataset_reader.h"

#include <map>
#include <unordered_map>

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

  graph_t graph{};
  // Dataset vertex ids are not graph-assigned, so we track the mapping from
  // dataset id to graph id ourselves to hook up add_edge() correctly.
  std::unordered_map<std::size_t, graaf::vertex_id_t> dataset_id_to_vertex_id{};

  const auto get_or_insert_vertex{[&](std::size_t dataset_id) {
    const auto [it, inserted]{
        dataset_id_to_vertex_id.emplace(dataset_id, graaf::vertex_id_t{})};
    if (inserted) {
      it->second = graph.add_vertex(no_data{});
    }
    return it->second;
  }};

  perf_common::read_dataset_edges(
      dataset_name, [&](std::size_t source, std::size_t target) {
        graph.add_edge(get_or_insert_vertex(source),
                       get_or_insert_vertex(target), UNIT_WEIGHT);
      });

  const auto [inserted_it,
              inserted]{cache.emplace(dataset_name, std::move(graph))};
  return inserted_it->second;
}

}  // namespace utils
