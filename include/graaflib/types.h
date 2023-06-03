#pragma once

#include <cstddef>
#include <functional>
#include <utility>

namespace graaf {

using vertex_id_t = std::size_t;
using edge_id_t = std::pair<vertex_id_t, vertex_id_t>;

struct edge_id_hash {
  [[nodiscard]] std::size_t operator()(const edge_id_t& key) const {
    const auto h1{std::hash<vertex_id_t>{}(key.first)};
    const auto h2{std::hash<vertex_id_t>{}(key.second)};

    // TODO: use something like boost::hash_combine
    return h1 ^ h2;
  }
};

/**
 * @brief Interface for a weighted edge.
 *
 * This is what is stored internally and returned from a weighted graph in
 * order to make sure each edge in a weighted graph has a common interface to
 * extract the weight.
 *
 * @tparam WEIGHT_T The type of the weight.
 */
template <typename WEIGHT_T = int>
class weighted_edge {
 public:
  /**
   * By default an edge has a unit weight.
   */
  [[nodiscard]] virtual WEIGHT_T get_weight() const noexcept { return 1; };
};

/**
 * @brief Adapter for a weighted edge which wraps a primitive type.
 *
 * Weighted graphs support having primitive numeric types for the edges.
 * In this case, the edges are internally wrapped in this adapter to provide a
 * common interface for weighted edges.
 *
 * @tparam WEIGHT_T The type of the weight.
 */
template <typename WEIGHT_T>
class primitive_numeric_adapter final : public weighted_edge<WEIGHT_T> {
 public:
  explicit primitive_numeric_adapter(WEIGHT_T value) : value_{value} {}

  [[nodiscard]] WEIGHT_T get_weight() const noexcept override { return value_; }

 private:
  WEIGHT_T value_{};
};

}  // namespace graaf