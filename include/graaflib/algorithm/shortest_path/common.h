#pragma once
#include <graaflib/types.h>

#include <list>
#include <optional>

namespace graaf::algorithm {

// Forward declaration
template <typename WEIGHT_T>
struct graph_path;

namespace detail {

template <typename WEIGHT_T>
struct path_vertex {
  vertex_id_t id;
  WEIGHT_T dist_from_start;
  vertex_id_t prev_id;

  [[nodiscard]] bool operator>(const path_vertex<WEIGHT_T>& other) {
    return dist_from_start > other.dist_from_start;
  }
};

template <typename WEIGHT_T>
std::optional<graph_path<WEIGHT_T>> reconstruct_path(
    vertex_id_t start_vertex, vertex_id_t end_vertex,
    std::unordered_map<vertex_id_t, path_vertex<WEIGHT_T>>& vertex_info);

}  // namespace detail

template <typename WEIGHT_T>
struct graph_path {
  std::list<vertex_id_t> vertices;
  WEIGHT_T total_weight;

  bool operator==(const graph_path& other) const {
    return vertices == other.vertices && total_weight == other.total_weight;
  }
};

}  // namespace graaf::algorithm

#include "common.tpp"