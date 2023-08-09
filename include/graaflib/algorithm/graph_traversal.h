#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>

#include <concepts>

namespace graaf::algorithm {

namespace detail {

/**
 * An edge callback which does nothing.
 */
struct noop_callback {
  void operator()(const edge_id_t & /*edge*/) const {}
};

/*
 * A unary predicate which always returns false, effectively resulting in an
 * exhaustive search.
 */
struct exhaustive_search_strategy {
  [[nodiscard]] bool operator()(const vertex_id_t /*vertex*/) const {
    return false;
  }
};

}  // namespace detail

/**
 * @brief Traverses the graph, starting at start_vertex, and visits all
 * reachable vertices in a BFS manner.
 *
 * @param graph The graph to traverse.
 * @param start_vertex Vertex id where the traversal should be started.
 * @param edge_callback A callback which is called for each traversed edge.
 * Should be invocable with an edge_id_t.
 * @param search_termination_strategy A unary predicate to indicate whether we
 * should continue the traversal or not. Traversal continues while this
 * predicate returns false.
 */
template <
    typename V, typename E, graph_type T,
    typename EDGE_CALLBACK_T = detail::noop_callback,
    typename SEARCH_TERMINATION_STRATEGY_T = detail::exhaustive_search_strategy>
  requires std::invocable<EDGE_CALLBACK_T &, edge_id_t &> &&
           std::is_invocable_r_v<bool, SEARCH_TERMINATION_STRATEGY_T &,
                                 vertex_id_t>
void breadth_first_traverse(
    const graph<V, E, T> &graph, vertex_id_t start_vertex,
    const EDGE_CALLBACK_T &edge_callback,
    const SEARCH_TERMINATION_STRATEGY_T &search_termination_strategy =
        SEARCH_TERMINATION_STRATEGY_T{});

/**
 * @brief Traverses the graph, starting at start_vertex, and visits all
 * reachable vertices in a DFS manner.
 *
 * @param graph The graph to traverse.
 * @param start_vertex Vertex id where the traversal should be started.
 * @param edge_callback A callback which is called for each traversed edge.
 * Should be invocable with an edge_id_t.
 * @param search_termination_strategy A unary predicate to indicate whether we
 * should continue the traversal or not. Traversal continues while this
 * predicate returns false.
 */
template <
    typename V, typename E, graph_type T,
    typename EDGE_CALLBACK_T = detail::noop_callback,
    typename SEARCH_TERMINATION_STRATEGY_T = detail::exhaustive_search_strategy>
  requires std::invocable<EDGE_CALLBACK_T &, edge_id_t &> &&
           std::is_invocable_r_v<bool, SEARCH_TERMINATION_STRATEGY_T &,
                                 vertex_id_t>
void depth_first_traverse(
    const graph<V, E, T> &graph, vertex_id_t start_vertex,
    const EDGE_CALLBACK_T &edge_callback,
    const SEARCH_TERMINATION_STRATEGY_T &search_termination_strategy =
        SEARCH_TERMINATION_STRATEGY_T{});

}  // namespace graaf::algorithm

#include "graph_traversal.tpp"