#pragma once

namespace graaf {

template <typename VERTEX_T, typename EDGE_T>
bool directed_graph<VERTEX_T, EDGE_T>::do_has_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) const noexcept {
  return this->edges_.contains({vertex_id_lhs, vertex_id_rhs});
}

template <typename VERTEX_T, typename EDGE_T>
EDGE_T& directed_graph<VERTEX_T, EDGE_T>::do_get_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) {
  return this->edges_.at({vertex_id_lhs, vertex_id_rhs});
}

template <typename VERTEX_T, typename EDGE_T>
void directed_graph<VERTEX_T, EDGE_T>::do_add_edge(vertex_id_t vertex_id_lhs,
                                                   vertex_id_t vertex_id_rhs,
                                                   EDGE_T edge) {
  this->adjacency_list_[vertex_id_lhs].insert(vertex_id_rhs);
  this->edges_.emplace(std::make_pair(vertex_id_lhs, vertex_id_rhs),
                       std::move(edge));
}

template <typename VERTEX_T, typename EDGE_T>
void directed_graph<VERTEX_T, EDGE_T>::do_remove_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) {
  this->adjacency_list_.at(vertex_id_lhs).erase(vertex_id_rhs);
  this->edges_.erase(std::make_pair(vertex_id_lhs, vertex_id_rhs));
}

}  // namespace graaf