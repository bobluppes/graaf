#pragma once

#include <cstddef>
#include <functional>
#include <type_traits>
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

template <typename T>
class weighted_edge {
 public:
  [[nodiscard]] virtual T get_weight() const noexcept = 0;
};

template <typename T>
class primitive_numeric_adapter final : public weighted_edge<T> {
 public:
  explicit primitive_numeric_adapter(T value) : value_{value} {}

  [[nodiscard]] T get_weight() const noexcept override { return value_; }

 private:
  T value_{};
};

}  // namespace graaf