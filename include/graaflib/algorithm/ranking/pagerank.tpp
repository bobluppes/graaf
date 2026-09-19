#pragma once
#include <graaflib/algorithm/ranking/pagerank.h>

#include <cmath>
#include <cstddef>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

namespace graaf::algorithm {

namespace detail {

inline void validate_pagerank_parameters(double damping_factor,
                                         double tolerance,
                                         std::size_t max_iterations) {
  // Written as negated range checks so that NaN is rejected as well
  if (!(damping_factor >= 0.0 && damping_factor <= 1.0)) {
    std::ostringstream error_msg;
    error_msg << "Damping factor [" << damping_factor
              << "] must lie in the range [0, 1].";
    throw std::invalid_argument{error_msg.str()};
  }

  if (!(tolerance > 0.0)) {
    std::ostringstream error_msg;
    error_msg << "Tolerance [" << tolerance << "] must be positive.";
    throw std::invalid_argument{error_msg.str()};
  }

  if (max_iterations == 0) {
    throw std::invalid_argument{
        "Maximum number of iterations must be positive."};
  }
}

}  // namespace detail

template <typename V, typename E>
std::optional<std::unordered_map<vertex_id_t, double>> pagerank(
    const graph<V, E, graph_type::DIRECTED>& graph, double damping_factor,
    double tolerance, std::size_t max_iterations) {
  detail::validate_pagerank_parameters(damping_factor, tolerance,
                                       max_iterations);

  std::unordered_map<vertex_id_t, double> ranks{};
  if (graph.vertex_count() == 0) {
    return ranks;
  }

  const auto vertex_count{static_cast<double>(graph.vertex_count())};
  const double teleport_rank{(1.0 - damping_factor) / vertex_count};

  ranks.reserve(graph.vertex_count());
  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    ranks.emplace(vertex_id, 1.0 / vertex_count);
  }

  auto next_ranks{ranks};

  for (std::size_t iteration{0}; iteration < max_iterations; ++iteration) {
    // Rank held by vertices without outgoing edges would otherwise leak out
    // of the system, so it is spread evenly over all vertices instead. This
    // keeps the ranks summing to one.
    double dangling_rank{0.0};
    for (auto& [_, next_rank] : next_ranks) {
      next_rank = 0.0;
    }

    for (const auto& [vertex_id, rank] : ranks) {
      const auto& neighbors{graph.get_neighbors(vertex_id)};
      if (neighbors.empty()) {
        dangling_rank += rank;
        continue;
      }

      const double share{rank / static_cast<double>(neighbors.size())};
      for (const auto& neighbor : neighbors) {
        next_ranks.at(neighbor) += share;
      }
    }

    const double base_rank{teleport_rank +
                           damping_factor * dangling_rank / vertex_count};
    double total_change{0.0};
    for (auto& [vertex_id, next_rank] : next_ranks) {
      next_rank = base_rank + damping_factor * next_rank;
      total_change += std::abs(next_rank - ranks.at(vertex_id));
    }

    ranks.swap(next_ranks);

    if (total_change <= tolerance) {
      return ranks;
    }
  }

  return std::nullopt;
}

}  // namespace graaf::algorithm
