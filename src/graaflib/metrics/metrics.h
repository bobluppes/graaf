#pragma once

#include <graaflib/graph_fwd.h>

namespace graaf::metrics {

    template <typename T, typename T_HASH>
    [[nodiscard]] float density(const graph<T, T_HASH>& graph) {
        // TODO: this differs for undirected graphs
        const auto edge_count_complete_graph{graph.vertex_count() * (graph.vertex_count() - 1)};
        return static_cast<float>(graph.edge_count()) / edge_count_complete_graph;
    }

}