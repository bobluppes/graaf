#pragma once

#include <graaflib/graph.h>

namespace utils {

enum class dataset : int64_t { WEB_GOOGLE, WEB_BERK_STAN };

struct no_data {};
using graph_t = graaf::undirected_graph<no_data, int>;

// Loads the graph for the given dataset, caching it internally so that the
// (expensive) parse only happens once per dataset no matter how many
// benchmark functions call this for the same dataset_name - including
// separate calls from the same function-local static, which would otherwise
// only ever load whichever dataset was passed on that static's first
// initialization and silently reuse it for every other dataset afterwards.
[[nodiscard]] const graph_t& construct_graph_from_file(
    const dataset& dataset_name);

}  // namespace utils
