#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf {

template <typename VERTEX_T, typename EDGE_T,
          edge_type EDGE_TYPE_V = edge_type::UNWEIGHTED>
class directed_graph final
    : public graph<VERTEX_T, EDGE_T, EDGE_TYPE_V, graph_spec::DIRECTED> {
 private:
  using edge_t =
      graph<VERTEX_T, EDGE_T, EDGE_TYPE_V, graph_spec::DIRECTED>::edge_t;

  [[nodiscard]] bool do_has_edge(
      vertex_id_t vertex_id_lhs,
      vertex_id_t vertex_id_rhs) const noexcept override;

  [[nodiscard]] edge_t& do_get_edge(vertex_id_t vertex_id_lhs,
                                    vertex_id_t vertex_id_rhs) override;

  void do_add_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs,
                   edge_t edge) override;

  void do_remove_edge(vertex_id_t vertex_id_lhs,
                      vertex_id_t vertex_id_rhs) override;
};

}  // namespace graaf

#include "directed_graph.tpp"