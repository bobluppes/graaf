#pragma once
#include <graaflib/algorithm/ranking/pagerank.h>

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <unordered_map>
#include <vector>

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

  if (graph.vertex_count() == 0) {
    return std::unordered_map<vertex_id_t, double>{};
  }

  const auto vertex_count{static_cast<double>(graph.vertex_count())};
  const double teleport_rank{(1.0 - damping_factor) / vertex_count};

  // Ranks are indexed directly by vertex_id_t: every iteration follows each
  // edge and looks up the rank of its target, so that lookup sits on the hot
  // path. Ids of removed vertices leave gaps, so the vectors span the largest
  // live id while only the live ids collected here are iterated.
  std::vector<vertex_id_t> vertex_ids{};
  vertex_ids.reserve(graph.vertex_count());
  vertex_id_t max_vertex_id{0};
  for (const auto& [vertex_id, _] : graph.get_vertices()) {
    vertex_ids.push_back(vertex_id);
    max_vertex_id = std::max(max_vertex_id, vertex_id);
  }

  std::vector<double> ranks(max_vertex_id + 1, 0.0);
  std::vector<double> next_ranks(max_vertex_id + 1, 0.0);
  for (const auto vertex_id : vertex_ids) {
    ranks[vertex_id] = 1.0 / vertex_count;
  }

  for (std::size_t iteration{0}; iteration < max_iterations; ++iteration) {
    // Rank held by vertices without outgoing edges would otherwise leak out
    // of the system, so it is spread evenly over all vertices instead. This
    // keeps the ranks summing to one.
    double dangling_rank{0.0};
    std::fill(next_ranks.begin(), next_ranks.end(), 0.0);

    for (const auto vertex_id : vertex_ids) {
      const auto& neighbors{graph.get_neighbors(vertex_id)};
      if (neighbors.empty()) {
        dangling_rank += ranks[vertex_id];
        continue;
      }

      const double share{ranks[vertex_id] /
                         static_cast<double>(neighbors.size())};
      for (const auto neighbor : neighbors) {
        next_ranks[neighbor] += share;
      }
    }

    const double base_rank{teleport_rank +
                           damping_factor * dangling_rank / vertex_count};
    double total_change{0.0};
    for (const auto vertex_id : vertex_ids) {
      auto& next_rank{next_ranks[vertex_id]};
      next_rank = base_rank + damping_factor * next_rank;
      total_change += std::abs(next_rank - ranks[vertex_id]);
    }

    ranks.swap(next_ranks);

    if (total_change <= tolerance) {
      std::unordered_map<vertex_id_t, double> ranks_by_vertex{};
      ranks_by_vertex.reserve(vertex_ids.size());
      for (const auto vertex_id : vertex_ids) {
        ranks_by_vertex.emplace(vertex_id, ranks[vertex_id]);
      }
      return ranks_by_vertex;
    }
  }

  return std::nullopt;
}

}  // namespace graaf::algorithm
