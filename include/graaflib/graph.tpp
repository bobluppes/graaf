#pragma once
#include <cstdlib>
#include <stdexcept>
#include <string>

#include "graph.h"

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

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
std::size_t graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::vertex_count()
    const noexcept {
  return vertex_count_;
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
std::size_t graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::edge_count() const noexcept {
  return edges_.size();
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
bool graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::has_vertex(
    vertex_id_t vertex_id) const noexcept {
  return vertex_id < vertices_.size() && vertices_[vertex_id].has_value();
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
bool graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::has_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) const noexcept {
  using enum graph_type;
  if constexpr (GRAPH_TYPE_V == DIRECTED) {
    return edges_.contains({vertex_id_lhs, vertex_id_rhs});
  } else if constexpr (GRAPH_TYPE_V == UNDIRECTED) {
    return edges_.contains(
        detail::make_sorted_pair(vertex_id_lhs, vertex_id_rhs));
  }

  // Should never reach this
  std::abort();
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
VERTEX_T& graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::get_vertex(
    vertex_id_t vertex_id) {
  // Effective C++ item 3: we can safely call a const function from a non-const.
  // one
  return const_cast<VERTEX_T&>(
      const_cast<const graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>*>(this)
          ->get_vertex(vertex_id));
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
const VERTEX_T& graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::get_vertex(
    vertex_id_t vertex_id) const {
  if (!has_vertex(vertex_id)) {
    // TODO(bluppes): replace with std::format once Clang supports it
    throw std::invalid_argument{"Vertex with ID [" + std::to_string(vertex_id) +
                                "] not found in graph."};
  }
  return *vertices_[vertex_id];
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
typename graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::edge_t&
graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::get_edge(vertex_id_t vertex_id_lhs,
                                                vertex_id_t vertex_id_rhs) {
  // Effective C++ item 3: we can safely call a const function from a non-const.
  return const_cast<graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::edge_t&>(
      const_cast<const graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>*>(this)->get_edge(
          vertex_id_lhs, vertex_id_rhs));
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
const typename graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::edge_t&
graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::get_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) const {
  if (!has_edge(vertex_id_lhs, vertex_id_rhs)) {
    // TODO(bluppes): replace with std::format once Clang supports it
    throw std::invalid_argument{"No edge found between vertices [" +
                                std::to_string(vertex_id_lhs) + "] -> [" +
                                std::to_string(vertex_id_rhs) + "]."};
  }

  using enum graph_type;
  if constexpr (GRAPH_TYPE_V == DIRECTED) {
    return edges_.at({vertex_id_lhs, vertex_id_rhs});
  } else if constexpr (GRAPH_TYPE_V == UNDIRECTED) {
    return edges_.at(detail::make_sorted_pair(vertex_id_lhs, vertex_id_rhs));
  }

  // Should never reach this
  std::abort();
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
typename graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::edge_t&
graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::get_edge(const edge_id_t& edge_id) {
  const auto [vertex_id_lhs, vertex_id_rhs]{edge_id};
  return get_edge(vertex_id_lhs, vertex_id_rhs);
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
const typename graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::edge_t&
graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::get_edge(
    const edge_id_t& edge_id) const {
  const auto [vertex_id_lhs, vertex_id_rhs]{edge_id};
  return get_edge(vertex_id_lhs, vertex_id_rhs);
}

static const std::vector<vertex_id_t> empty_list;

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
const typename graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::neighbors_t&
graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::get_neighbors(
    vertex_id_t vertex_id) const {
  const auto it{adjacency_list_.find(vertex_id)};
  if (it == adjacency_list_.end()) {
    return empty_list;
  }
  return it->second;
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
vertex_id_t graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::add_vertex(auto&& vertex) {
  vertex_id_t vertex_id;
  if (!free_vertex_ids_.empty()) {
    vertex_id = free_vertex_ids_.back();
    free_vertex_ids_.pop_back();
  } else {
    // add_vertex_with_id() inserts directly, bypassing both
    // free_vertex_ids_ and vertex_id_supplier_, so the supplier can lag
    // behind ids that already exist (e.g. a freshly transposed graph, whose
    // vertices were all inserted that way). A single increment isn't
    // enough in that case, so this has to scan forward until it finds an
    // actually free id.
    while (has_vertex(vertex_id_supplier_)) {
      ++vertex_id_supplier_;
    }
    vertex_id = vertex_id_supplier_;
  }

  if (vertex_id >= vertices_.size()) {
    vertices_.resize(vertex_id + 1);
  }
  vertices_[vertex_id].emplace(std::forward<decltype(vertex)>(vertex));
  ++vertex_count_;
  return vertex_id;
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
vertex_id_t graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::add_vertex_with_id(
    auto&& vertex, vertex_id_t id) {
  if (has_vertex(id)) {
    throw std::invalid_argument{"Vertex already exists at ID [" +
                                std::to_string(id) + "]"};
  }

  if (id >= vertices_.size()) {
    vertices_.resize(id + 1);
  }
  vertices_[id].emplace(std::forward<decltype(vertex)>(vertex));
  ++vertex_count_;
  return id;
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
void graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::remove_vertex(
    vertex_id_t vertex_id) {
  // Only ids that were actually in use get freed for reuse - otherwise
  // removing an id that was never assigned would leak it into
  // free_vertex_ids_ and have a later add_vertex() hand it out.
  const bool existed{has_vertex(vertex_id)};

  if (adjacency_list_.contains(vertex_id)) {
    for (auto& target_vertex_id : adjacency_list_.at(vertex_id)) {
      edges_.erase({vertex_id, target_vertex_id});
    }
  }

  adjacency_list_.erase(vertex_id);

  for (auto& [source_vertex_id, neighbors] : adjacency_list_) {
    std::erase(neighbors, vertex_id);
    edges_.erase({source_vertex_id, vertex_id});
  }

  if (existed) {
    vertices_[vertex_id].reset();
    --vertex_count_;
    free_vertex_ids_.push_back(vertex_id);
  }
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
void graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::add_edge(vertex_id_t vertex_id_lhs,
                                                     vertex_id_t vertex_id_rhs,
                                                     auto&& edge) {
  if (!has_vertex(vertex_id_lhs) || !has_vertex(vertex_id_rhs)) {
    // TODO(bluppes): replace with std::format once Clang supports it
    throw std::invalid_argument{
        "Vertices with ID [" + std::to_string(vertex_id_lhs) + "] and [" +
        std::to_string(vertex_id_rhs) + "] not found in graph."};
  }

  if (has_edge(vertex_id_lhs, vertex_id_rhs)) {
    // TODO(bluppes): replace with std::format once Clang supports it
    throw std::invalid_argument{
        "An edge already exists between vertices with ID [" +
        std::to_string(vertex_id_lhs) + "] and [" +
        std::to_string(vertex_id_rhs) + "]."};
  }

  using enum graph_type;
  if constexpr (GRAPH_TYPE_V == DIRECTED) {
    adjacency_list_[vertex_id_lhs].push_back(vertex_id_rhs);
    edges_.emplace(std::make_pair(vertex_id_lhs, vertex_id_rhs),
                   std::forward<decltype(edge)>(edge));
    return;
  } else if constexpr (GRAPH_TYPE_V == UNDIRECTED) {
    adjacency_list_[vertex_id_lhs].push_back(vertex_id_rhs);
    // A self-loop is a single neighbor entry
    if (vertex_id_lhs != vertex_id_rhs) {
      adjacency_list_[vertex_id_rhs].push_back(vertex_id_lhs);
    }
    edges_.emplace(detail::make_sorted_pair(vertex_id_lhs, vertex_id_rhs),
                   std::forward<decltype(edge)>(edge));
    return;
  }

  // Should never reach this
  std::abort();
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
void graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::remove_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) {
  if (!has_edge(vertex_id_lhs, vertex_id_rhs)) {
    // TODO(bluppes): replace with std::format once Clang supports it
    throw std::invalid_argument{"No edge found between vertices [" +
                                std::to_string(vertex_id_lhs) + "] -> [" +
                                std::to_string(vertex_id_rhs) + "]."};
  }

  using enum graph_type;
  if constexpr (GRAPH_TYPE_V == DIRECTED) {
    std::erase(adjacency_list_.at(vertex_id_lhs), vertex_id_rhs);
    edges_.erase(std::make_pair(vertex_id_lhs, vertex_id_rhs));
    return;
  } else if constexpr (GRAPH_TYPE_V == UNDIRECTED) {
    std::erase(adjacency_list_.at(vertex_id_lhs), vertex_id_rhs);
    std::erase(adjacency_list_.at(vertex_id_rhs), vertex_id_lhs);
    edges_.erase(detail::make_sorted_pair(vertex_id_lhs, vertex_id_rhs));
    return;
  }

  // Should never reach this
  std::abort();
}

}  // namespace graaf
