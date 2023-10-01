#pragma once

#include <stdexcept>
#include <string>

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
  return vertices_.size();
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
std::size_t graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::edge_count() const noexcept {
  return edges_.size();
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
bool graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::has_vertex(
    vertex_id_t vertex_id) const noexcept {
  return vertices_.contains(vertex_id);
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
  return vertices_.at(vertex_id);
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

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
typename graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::vertices_t
graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::get_neighbors(
    vertex_id_t vertex_id) const {
  if (!adjacency_list_.contains(vertex_id)) {
    return {};
  }
  return adjacency_list_.at(vertex_id);
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
vertex_id_t graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::add_vertex(auto&& vertex) {
  // TODO: check overflow
  const auto vertex_id{vertex_id_supplier_++};
  vertices_.emplace(vertex_id, std::forward<VERTEX_T>(vertex));
  return vertex_id;
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
void graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::remove_vertex(
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

  using enum graph_type;
  if constexpr (GRAPH_TYPE_V == DIRECTED) {
    adjacency_list_[vertex_id_lhs].insert(vertex_id_rhs);
    edges_.emplace(std::make_pair(vertex_id_lhs, vertex_id_rhs),
                   std::forward<EDGE_T>(edge));
    return;
  } else if constexpr (GRAPH_TYPE_V == UNDIRECTED) {
    adjacency_list_[vertex_id_lhs].insert(vertex_id_rhs);
    adjacency_list_[vertex_id_rhs].insert(vertex_id_lhs);
    edges_.emplace(detail::make_sorted_pair(vertex_id_lhs, vertex_id_rhs),
                   std::forward<EDGE_T>(edge));
    return;
  }

  // Should never reach this
  std::abort();
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
void graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::remove_edge(
    vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) {
  using enum graph_type;
  if constexpr (GRAPH_TYPE_V == DIRECTED) {
    adjacency_list_.at(vertex_id_lhs).erase(vertex_id_rhs);
    edges_.erase(std::make_pair(vertex_id_lhs, vertex_id_rhs));
    return;
  } else if constexpr (GRAPH_TYPE_V == UNDIRECTED) {
    adjacency_list_.at(vertex_id_lhs).erase(vertex_id_rhs);
    adjacency_list_.at(vertex_id_rhs).erase(vertex_id_lhs);
    edges_.erase(detail::make_sorted_pair(vertex_id_lhs, vertex_id_rhs));
    return;
  }

  // Should never reach this
  std::abort();
}

template <typename VERTEX_T, typename EDGE_T>
vertex_id_t get_index_for_transposed_graph(
    vertex_id_t original_vertex_id,
    std::unordered_map<vertex_id_t, vertex_id_t>& id_mapping,
    const directed_graph<VERTEX_T, EDGE_T>& original_graph,
    directed_graph<VERTEX_T, EDGE_T>& out_transposed_graph) {
  vertex_id_t transposed_vertex_id;

  if (id_mapping.find(original_vertex_id) == id_mapping.end()) {
    vertex_id_t current_vertex_value_lhs =
        original_graph.get_vertex(original_vertex_id);
    transposed_vertex_id =
        out_transposed_graph.add_vertex(current_vertex_value_lhs);

    id_mapping.insert({original_vertex_id, transposed_vertex_id});
  } else {
    transposed_vertex_id = id_mapping.find(original_vertex_id)->second;
  }

  return transposed_vertex_id;
}

template <typename VERTEX_T, typename EDGE_T>
void get_transposed_graph(
    const directed_graph<VERTEX_T, EDGE_T>& original_graph,
    directed_graph<VERTEX_T, EDGE_T>& out_transposed_graph) {
  std::unordered_map<vertex_id_t, vertex_id_t> id_mapping;

  for (const auto& [edge, edge_type] : original_graph.get_edges()) {
    const auto [current_vertex_id_lhs, current_vertex_id_rhs]{edge};

    vertex_id_t vertex_id_lhs =
        get_index_for_transposed_graph(current_vertex_id_lhs, id_mapping,
                                       original_graph, out_transposed_graph);
    vertex_id_t vertex_id_rhs =
        get_index_for_transposed_graph(current_vertex_id_rhs, id_mapping,
                                       original_graph, out_transposed_graph);

    EDGE_T edge_type_to_add = edge_type;

    out_transposed_graph.add_edge(vertex_id_rhs, vertex_id_lhs,
                                  edge_type_to_add);
  }
}

}  // namespace graaf