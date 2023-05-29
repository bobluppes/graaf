#pragma once

namespace graaf {

namespace detail {
inline std::pair<vertex_id_t, vertex_id_t> make_sorted_pair(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) {
  if (vertex_id_lhs < vertex_id_rhs) {
    return std::make_pair(vertex_id_lhs, vertex_id_rhs);
  }
  return std::make_pair(vertex_id_rhs, vertex_id_lhs);
}
}  // namespace detail

template <typename VERTEX_T, typename EDGE_T>
bool undirected_graph<VERTEX_T, EDGE_T>::do_has_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) const noexcept {
  return this->edges_.contains(
      detail::make_sorted_pair(vertex_id_lhs, vertex_id_rhs));
}

template <typename VERTEX_T, typename EDGE_T>
EDGE_T& undirected_graph<VERTEX_T, EDGE_T>::do_get_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) {
  return this->edges_.at(
      detail::make_sorted_pair(vertex_id_lhs, vertex_id_rhs));
}

template <typename VERTEX_T, typename EDGE_T>
void undirected_graph<VERTEX_T, EDGE_T>::do_add_edge(vertex_id_t vertex_id_lhs,
                                                     vertex_id_t vertex_id_rhs,
                                                     EDGE_T edge) {
  this->adjacency_list_[vertex_id_lhs].insert(vertex_id_rhs);
  this->adjacency_list_[vertex_id_rhs].insert(vertex_id_lhs);

  this->edges_.emplace(detail::make_sorted_pair(vertex_id_lhs, vertex_id_rhs),
                       std::move(edge));
}

template <typename VERTEX_T, typename EDGE_T>
void undirected_graph<VERTEX_T, EDGE_T>::do_remove_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) {
  this->adjacency_list_.at(vertex_id_lhs).erase(vertex_id_rhs);
  this->adjacency_list_.at(vertex_id_rhs).erase(vertex_id_lhs);
  this->edges_.erase(detail::make_sorted_pair(vertex_id_lhs, vertex_id_rhs));
}

template <typename VERTEX_T, typename EDGE_T>
std::size_t undirected_graph<VERTEX_T, EDGE_T>::get_vertex_degree(
    vertex_id_t vertex_id) const noexcept {
  return (this->get_neighbors(vertex_id)).size();
}

}  // namespace graaf