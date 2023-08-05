#pragma once

#include <concepts>
#include <type_traits>

namespace graaf {

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
  using weight_t = WEIGHT_T;

  virtual ~weighted_edge() = default;

  [[nodiscard]] virtual WEIGHT_T get_weight() const noexcept = 0;
};

template <typename derived>
concept derived_from_weighted_edge =
    std::is_base_of_v<weighted_edge<typename derived::weight_t>, derived>;

/**
 * Overload set to get the weight from an edge
 */
template <typename WEIGHTED_EDGE_T>
  requires derived_from_weighted_edge<WEIGHTED_EDGE_T>
[[nodiscard]] auto get_weight(const WEIGHTED_EDGE_T& edge);

template <typename EDGE_T>
  requires std::is_arithmetic_v<EDGE_T>
[[nodiscard]] EDGE_T get_weight(const EDGE_T& edge);

template <typename EDGE_T>
[[nodiscard]] int get_weight(const EDGE_T& /*edge*/);

}  // namespace graaf

#include "edge.tpp"