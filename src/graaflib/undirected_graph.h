#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf {

template <typename VERTEX_T, typename EDGE_T>
class undirected_graph final
    : public graph<VERTEX_T, EDGE_T, GRAPH_SPEC::UNDIRECTED> {
 private:
  using vertex_ids_t =
      graph<VERTEX_T, EDGE_T, GRAPH_SPEC::UNDIRECTED>::vertex_ids_t;
  using edge_t = graph<VERTEX_T, EDGE_T, GRAPH_SPEC::UNDIRECTED>::edge_t;

  vertex_ids_t make_sorted_pair(vertex_id_t vertex_id_lhs,
                                vertex_id_t vertex_id_rhs) const {
    if (vertex_id_lhs < vertex_id_rhs) {
      return std::make_pair(vertex_id_lhs, vertex_id_rhs);
    }
    return std::make_pair(vertex_id_rhs, vertex_id_lhs);
  }

  [[nodiscard]] bool do_has_edge(
      vertex_id_t vertex_id_lhs,
      vertex_id_t vertex_id_rhs) const noexcept override {
    return this->edges_.contains(
        make_sorted_pair(vertex_id_lhs, vertex_id_rhs));
  }

  [[nodiscard]] edge_t& do_get_edge(vertex_id_t vertex_id_lhs,
                                    vertex_id_t vertex_id_rhs) override {
    return this->edges_.at(make_sorted_pair(vertex_id_lhs, vertex_id_rhs));
  }

  void do_add_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs,
                   EDGE_T edge) override {
    this->adjacency_list_[vertex_id_lhs].insert(vertex_id_rhs);
    this->adjacency_list_[vertex_id_rhs].insert(vertex_id_lhs);

    this->edges_.emplace(make_sorted_pair(vertex_id_lhs, vertex_id_rhs),
                         std::move(edge));
  }

  void do_remove_edge(vertex_id_t vertex_id_lhs,
                      vertex_id_t vertex_id_rhs) override {
    this->adjacency_list_.at(vertex_id_lhs).erase(vertex_id_rhs);
    this->adjacency_list_.at(vertex_id_rhs).erase(vertex_id_lhs);
    this->edges_.erase(make_sorted_pair(vertex_id_lhs, vertex_id_rhs));
  }
};

}  // namespace graaf