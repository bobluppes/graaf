#pragma once

#include <graaflib/algorithm/graph_traversal/breadth_first_search.h>

namespace graaf::algorithm
{

template<typename V, typename E, graph_type T, typename WEIGHT_T>
std::optional<graph_path<WEIGHT_T>> bfs_shortest_path(graph<V, E, T> const& graph,
                                                      vertex_id_t start_vertex,
                                                      vertex_id_t end_vertex)
{
    std::unordered_map<vertex_id_t, detail::path_vertex<WEIGHT_T>> vertex_info {
        {start_vertex, {start_vertex, 0, start_vertex}}
    };

    auto const callback {
        [&vertex_info](edge_id_t const& edge)
        {
            auto const [source, target] {edge};

            if(!vertex_info.contains(target))
            {
                vertex_info[target] = {
                    target, vertex_info[source].dist_from_start + 1, source};
            }
        }};

    // We keep searching until we have reached the target vertex
    auto const search_termination_strategy {[end_vertex](vertex_id_t const vertex_id)
                                            {
                                                return vertex_id == end_vertex;
                                            }};

    breadth_first_traverse(graph, start_vertex, callback, search_termination_strategy);

    return reconstruct_path(start_vertex, end_vertex, vertex_info);
}

} // namespace graaf::algorithm
