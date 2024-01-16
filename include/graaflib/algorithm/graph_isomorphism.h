#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <graaflib/algorithm/graph_isomorphism_util.h>

#include <algorithm>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>




namespace graaf::algorithm {

/**
 * @brief Checks if two graphs are isomorphic.
 *
 * This function checks whether two given graphs are isomorphic, meaning
 * they are structurally identical up to vertex and edge relabeling.
 * If the graphs are isomorphic, the function returns an optional containing
 * a mapping from the vertices of the first graph to the vertices of the second
 * graph. If the graphs are not isomorphic, the function returns std::nullopt.
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to compare.
 * @param rhs The second graph to compare.
 * @return An optional containing a mapping from the vertices of lhs to those of
 * rhs if isomorphic; otherwise std::nullopt.
 */

template <typename V, typename E, graph_type T>
std::optional<std::unordered_map<vertex_id_t, vertex_id_t>> check_isomorphism(
    const graph<V, E, T>& lhs, const graph<V, E, T>& rhs);
}  // namespace graaf::algorithm
#include "graph_isomorphism.tpp"
