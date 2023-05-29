#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf {

template <typename VERTEX_T, typename EDGE_T>
class directed_graph final
    : public graph<VERTEX_T, EDGE_T, graph_spec::DIRECTED> {
 public:
  [[nodiscard]] std::size_t get_vertex_outdegree(
      vertex_id_t vertex_id) const noexcept;

  [[nodiscard]] std::size_t get_vertex_indegree(
      vertex_id_t vertex_id) const noexcept;

 private:
  [[nodiscard]] bool do_has_edge(
      vertex_id_t vertex_id_lhs,
      vertex_id_t vertex_id_rhs) const noexcept override;

  [[nodiscard]] EDGE_T& do_get_edge(vertex_id_t vertex_id_lhs,
                                    vertex_id_t vertex_id_rhs) override;

  void do_add_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs,
                   EDGE_T edge) override;

  void do_remove_edge(vertex_id_t vertex_id_lhs,
                      vertex_id_t vertex_id_rhs) override;
};

}  // namespace graaf

#include "directed_graph.tpp"