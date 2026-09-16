#pragma once

#include <graaflib/graph.h>

namespace utils {

enum class dataset : int64_t { WEB_GOOGLE, WEB_BERK_STAN };

struct no_data {};
using graph_t = graaf::undirected_graph<no_data, int>;

// Loads the graph for the given dataset, caching it internally so the
// (expensive) parse only happens once per dataset.
[[nodiscard]] const graph_t& construct_graph_from_file(
    const dataset& dataset_name);

}  // namespace utils
