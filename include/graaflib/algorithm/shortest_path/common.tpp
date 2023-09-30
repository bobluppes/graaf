#pragma once

namespace graaf::algorithm {

namespace detail {

template <typename WEIGHT_T>
std::optional<graph_path<WEIGHT_T>> reconstruct_path(
    vertex_id_t start_vertex, vertex_id_t end_vertex,
    std::unordered_map<vertex_id_t, path_vertex<WEIGHT_T>>& vertex_info) {
  if (!vertex_info.contains(end_vertex)) {
    return std::nullopt;
  }

  graph_path<WEIGHT_T> path;
  auto current = end_vertex;

  while (current != start_vertex) {
    path.vertices.push_front(current);
    current = vertex_info[current].prev_id;
  }

  path.vertices.push_front(start_vertex);
  path.total_weight = vertex_info[end_vertex].dist_from_start;
  return path;
}

}  // namespace detail

}  // namespace graaf::algorithm