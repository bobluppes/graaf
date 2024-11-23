#pragma once

#include <cstddef>
#include <functional>
#include <utility>

namespace graaf {

using vertex_id_t = std::size_t;
using edge_id_t = std::pair<vertex_id_t, vertex_id_t>;

template <class T>
inline void hash_combine(std::size_t& seed, const T& v) {
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

struct edge_id_hash {
  [[nodiscard]] std::size_t operator()(const edge_id_t& key) const {
    size_t seed = 0;
    hash_combine(seed, key.first);
    hash_combine(seed, key.second);

    return seed;
  }
};

}  // namespace graaf
