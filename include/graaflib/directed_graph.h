#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf {

template <typename VERTEX_T, typename EDGE_T>
class directed_graph final
    : public graph<VERTEX_T, EDGE_T, graph_spec::DIRECTED> {
 private:
  using edge_t = typename graph<VERTEX_T, EDGE_T, graph_spec::DIRECTED>::edge_t;

  [[nodiscard]] bool do_has_edge(
      vertex_id_t vertex_id_lhs,
      vertex_id_t vertex_id_rhs) const noexcept override;

  [[nodiscard]] const edge_t& do_get_edge(
      vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) const override;

  void do_add_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs,
                   edge_t edge) override;

  void do_remove_edge(vertex_id_t vertex_id_lhs,
                      vertex_id_t vertex_id_rhs) override;
};

}  // namespace graaf

#include "directed_graph.tpp"