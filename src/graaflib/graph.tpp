#pragma once

namespace graaf {

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
std::size_t graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::vertex_count()
    const noexcept {
  return vertices_.size();
}

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
std::size_t graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::edge_count() const noexcept {
  return edges_.size();
}

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
bool graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::has_vertex(
    vertex_id_t vertex_id) const noexcept {
  return vertices_.contains(vertex_id);
}

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
bool graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::has_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) const noexcept {
  return do_has_edge(vertex_id_lhs, vertex_id_rhs);
}

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
VERTEX_T& graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::get_vertex(
    vertex_id_t vertex_id) {
  if (!has_vertex(vertex_id)) {
    throw std::out_of_range{
        fmt::format("Vertex with ID [{}] not found in graph.", vertex_id)};
    // May be more accurate to throw std::invalid_argument.
  }
  return vertices_.at(vertex_id);
}

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
const VERTEX_T& graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::get_vertex(
    vertex_id_t vertex_id) const {
  return get_vertex(vertex_id);
}

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
EDGE_T& graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::get_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) {
  if (!has_edge(vertex_id_lhs, vertex_id_rhs)) {
    throw std::out_of_range{
        fmt::format("No edge found between vertices [{}] -> [{}].",
                    vertex_id_lhs, vertex_id_rhs)};
  }
  return do_get_edge(vertex_id_lhs, vertex_id_rhs);
}

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
const EDGE_T& graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::get_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) const {
  return get_edge(vertex_id_lhs, vertex_id_rhs);
}

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::vertices_t
graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::get_neighbors(
    vertex_id_t vertex_id) const {
  if (!adjacency_list_.contains(vertex_id)) {
    return {};
  }
  return adjacency_list_.at(vertex_id);
}

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
vertex_id_t graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::add_vertex(VERTEX_T vertex) {
  // TODO: check overflow
  const auto vertex_id{vertex_id_supplier_++};
  vertices_.emplace(vertex_id, std::move(vertex));
  return vertex_id;
}

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
void graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::remove_vertex(
    vertex_id_t vertex_id) {
  if (adjacency_list_.contains(vertex_id)) {
    for (auto& target_vertex_id : adjacency_list_.at(vertex_id)) {
      edges_.erase({vertex_id, target_vertex_id});
    }
  }

  adjacency_list_.erase(vertex_id);
  vertices_.erase(vertex_id);

  for (auto& [source_vertex_id, neighbors] : adjacency_list_) {
    neighbors.erase(vertex_id);
    edges_.erase({source_vertex_id, vertex_id});
  }
}

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
void graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::add_edge(vertex_id_t vertex_id_lhs,
                                                     vertex_id_t vertex_id_rhs,
                                                     EDGE_T edge) {
  if (!has_vertex(vertex_id_lhs) || !has_vertex(vertex_id_rhs)) {
    throw std::out_of_range{
        fmt::format("Vertices with ID [{}] and [{}] not found in graph.",
                    vertex_id_lhs, vertex_id_rhs)};
  }
  do_add_edge(vertex_id_lhs, vertex_id_rhs, std::move(edge));
}

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::vertex_ids_t
graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::add_edge(VERTEX_T vertex_lhs,
                                                VERTEX_T vertex_rhs,
                                                EDGE_T edge) {
  const auto vertex_id_lhs{add_vertex(std::move(vertex_lhs))};
  const auto vertex_id_rhs{add_vertex(std::move(vertex_rhs))};
  add_edge(vertex_id_lhs, vertex_id_rhs, std::move(edge));
  return {vertex_id_lhs, vertex_id_rhs};
}

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
void graph<VERTEX_T, EDGE_T, GRAPH_SPEC_V>::remove_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) {
  do_remove_edge(vertex_id_lhs, vertex_id_rhs);
}

}  // namespace graaf