#pragma once

#include <graaflib/types.h>

#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace graaf::algorithm::detail {

/**
 * @brief A vertex_id_t-keyed set of "seen" vertices, backed by a densely
 * indexed vector rather than a hash set.
 *
 * Vertex ids are graph-owned and kept dense, so a vector indexed directly by
 * id avoids the hashing/bucket overhead of std::unordered_set<vertex_id_t>
 * for the same purpose. Grows lazily to cover the highest id inserted so
 * far, the same strategy graph itself uses for its own storage.
 */
class vertex_id_set {
 public:
  /**
   * Marks id as seen.
   *
   * @param id The vertex id to insert.
   * @return true if id was not already present (mirrors
   * std::unordered_set::insert().second).
   */
  bool insert(vertex_id_t id) {
    if (id >= seen_.size()) {
      seen_.resize(id + 1, false);
    }
    if (seen_[id]) {
      return false;
    }
    seen_[id] = true;
    return true;
  }

  [[nodiscard]] bool contains(vertex_id_t id) const noexcept {
    return id < seen_.size() && seen_[id];
  }

 private:
  std::vector<bool> seen_{};
};

/**
 * @brief A vertex_id_t-keyed map, backed by a densely indexed vector rather
 * than a hash map.
 *
 * Vertex ids are graph-owned and kept dense, so a vector indexed directly by
 * id avoids the hashing/bucket overhead of std::unordered_map<vertex_id_t, T>
 * for the same purpose. Grows lazily to cover the highest id accessed so
 * far, the same strategy graph itself uses for its own storage.
 */
template <typename T>
class vertex_id_map {
 public:
  [[nodiscard]] bool contains(vertex_id_t id) const noexcept {
    return id < values_.size() && values_[id].has_value();
  }

  /**
   * Access the value for id, default-constructing one in place if absent
   * (mirrors std::unordered_map::operator[]).
   */
  T& operator[](vertex_id_t id) {
    if (id >= values_.size()) {
      values_.resize(id + 1);
    }
    if (!values_[id].has_value()) {
      values_[id].emplace();
    }
    return *values_[id];
  }

  T& at(vertex_id_t id) { return const_cast<T&>(std::as_const(*this).at(id)); }

  const T& at(vertex_id_t id) const {
    if (!contains(id)) {
      throw std::out_of_range{"No value stored for vertex id [" +
                              std::to_string(id) + "]"};
    }
    return *values_[id];
  }

 private:
  std::vector<std::optional<T>> values_{};
};

}  // namespace graaf::algorithm::detail
