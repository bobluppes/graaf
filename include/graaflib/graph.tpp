#pragma once
#include <cstdlib>
#include <iterator>
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

// A read-only view over a dense, tombstoned vertex_id_t -> VERTEX_T vector,
// yielding (id, value) pairs for the live slots only. Hand-rolled rather
// than composed from std::views: std::views::filter's begin() caches state
// on first call and so can't be const, which would rule out storing the
// result of graph::get_vertices() in a const variable.
template <typename VERTEX_T>
class vertex_view {
 public:
  using dense_vertices_t = std::vector<std::optional<VERTEX_T>>;

  class iterator {
   public:
    using value_type = std::pair<vertex_id_t, const VERTEX_T&>;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    iterator() = default;
    iterator(const dense_vertices_t& data, vertex_id_t idx)
        : data_{&data}, idx_{idx} {}

    value_type operator*() const { return {idx_, *(*data_)[idx_]}; }

    iterator& operator++() {
      do {
        ++idx_;
      } while (idx_ < data_->size() && !(*data_)[idx_].has_value());
      return *this;
    }

    iterator operator++(int) {
      auto tmp{*this};
      ++*this;
      return tmp;
    }

    bool operator==(const iterator& other) const = default;

   private:
    const dense_vertices_t* data_{nullptr};
    vertex_id_t idx_{0};
  };

  explicit vertex_view(const dense_vertices_t& data) : data_{&data} {}

  [[nodiscard]] iterator begin() const {
    vertex_id_t idx{0};
    while (idx < data_->size() && !(*data_)[idx].has_value()) {
      ++idx;
    }
    return {*data_, idx};
  }

  [[nodiscard]] iterator end() const { return {*data_, data_->size()}; }

 private:
  const dense_vertices_t* data_;
};

}  // namespace detail

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
std::size_t graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::vertex_count()
    const noexcept {
  return vertex_count_;
}

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
auto graph<VERTEX_T, EDGE_T, GRAPH_TYPE_V>::get_vertices() const noexcept {
  return detail::vertex_view<VERTEX_T>{vertices_};
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
  // A vertex_id that was never assigned can't be anyone's neighbor, so
  // there's nothing to clean up in adjacency_list_/edges_, and it must not
  // be freed for reuse (that would leak an arbitrary id into
  // free_vertex_ids_ for a later add_vertex() to hand out).
  if (!has_vertex(vertex_id)) {
    return;
  }

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

  vertices_[vertex_id].reset();
  --vertex_count_;
  free_vertex_ids_.push_back(vertex_id);
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
