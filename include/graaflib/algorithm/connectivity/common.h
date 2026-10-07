#pragma once

#include <graaflib/types.h>

#include <limits>
#include <vector>

namespace graaf::algorithm {

using articulation_points_t = std::vector<vertex_id_t>;
using bridges_t = std::vector<edge_id_t>;

inline constexpr vertex_id_t INVALID_VERTEX =
    std::numeric_limits<vertex_id_t>::max();

}  // namespace graaf::algorithm