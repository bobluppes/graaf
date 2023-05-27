#include <functional>

#include "types.h"

namespace graaf {
std::size_t vertex_ids_hash::operator()(const vertex_ids_t& key) const {
  const auto h1{std::hash<vertex_id_t>{}(key.first)};
  const auto h2{std::hash<vertex_id_t>{}(key.second)};

  // TODO: use something like boost::hash_combine
  return h1 ^ h2;
}
}  // namespace graaf