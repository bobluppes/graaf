#pragma once

#include <graaflib/graph.h>

#include <cstddef>
#include <optional>
#include <unordered_map>

namespace graaf::algorithm {
/**
 * @brief Computes the PageRank of every vertex in a directed graph.
 *
 * The rank of a vertex reflects how likely a random surfer, who follows an
 * outgoing edge with probability damping_factor and otherwise jumps to a
 * uniformly random vertex, is to be at that vertex. Vertices without outgoing
 * edges are treated as linking to every vertex in the graph. The ranks of all
 * vertices sum to one.
 *
 * @tparam V The vertex type of the graph.
 * @tparam E The edge type of the graph.
 * @param graph The input graph.
 * @param damping_factor Probability of following an outgoing edge, in the
 * range [0, 1]. Defaults to 0.85.
 * @param tolerance Convergence threshold on the sum of the absolute changes in
 * rank between two consecutive iterations. Must be positive. Defaults to 1e-6.
 * @param max_iterations Maximum number of iterations. Must be positive.
 * Defaults to 100.
 * @return Map from each vertex id to its PageRank. If the ranks did not
 * converge within max_iterations, returns std::nullopt.
 * @throws std::invalid_argument If damping_factor is outside [0, 1], tolerance
 * is not positive, or max_iterations is zero.
 */
template <typename V, typename E>
[[nodiscard]] std::optional<std::unordered_map<vertex_id_t, double>> pagerank(
    const graph<V, E, graph_type::DIRECTED>& graph,
    double damping_factor = 0.85, double tolerance = 1.0e-6,
    std::size_t max_iterations = 100);

}  // namespace graaf::algorithm

#include "pagerank.tpp"
