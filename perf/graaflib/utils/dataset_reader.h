#pragma once

#include <graaflib/graph.h>

namespace utils {

enum class dataset : int64_t { WEB_GOOGLE, WEB_BERK_STAN };

struct no_data {};
using graph_t = graaf::undirected_graph<no_data, int>;

[[nodiscard]] graph_t construct_graph_from_file(const dataset& dataset_name);

}  // namespace utils
