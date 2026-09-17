#pragma once

#include <boost/graph/adjacency_list.hpp>

#include "common/dataset.h"

namespace utils {

using dataset = perf_common::dataset;

using graph_t =
    boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS,
                          boost::no_property,
                          boost::property<boost::edge_weight_t, int>>;

// Loads the graph for the given dataset, caching it internally so the
// (expensive) parse only happens once per dataset.
[[nodiscard]] const graph_t& construct_graph_from_file(
    const dataset& dataset_name);

}  // namespace utils
