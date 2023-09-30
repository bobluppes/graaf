#pragma once

#include <graaflib/types.h>

namespace graaf::algorithm {

namespace detail {

/**
 * An edge callback which does nothing.
 */
struct noop_callback {
  void operator()(const edge_id_t& /*edge*/) const {}
};

/*
 * A unary predicate which always returns false, effectively resulting in an
 * exhaustive search.
 */
struct exhaustive_search_strategy {
  [[nodiscard]] bool operator()(const vertex_id_t /*vertex*/) const {
    return false;
  }
};

}  // namespace detail

}  // namespace graaf::algorithm