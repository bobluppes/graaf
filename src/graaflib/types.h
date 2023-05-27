#pragma once

#include <cstddef>
#include <utility>

namespace graaf {

using vertex_id_t = std::size_t;
using edge_id_t = std::size_t;

using vertex_ids_t = std::pair<vertex_id_t, vertex_id_t>;

struct vertex_ids_hash {
  [[nodiscard]] std::size_t operator()(const vertex_ids_t& key) const;
};

}  // namespace graaf