// graaflib/algorithm/topological_sorting/kahn.cpp
#include "kahn.h"

namespace graaflib::algorithm::topological_sorting {

    template <typename V, typename E>
    std::optional<std::vector<vertex_id_t>> kahns_topological_sort(
        const graph<V, E, graph_type::DIRECTED>& graph
    ) {
        std::vector<vertex_id_t> topological_order;
        std::vector<vertex_id_t> in_degree(graph.num_vertices(), 0);

        //calculate in-degrees for all vertices
        for (const auto& edge : graph.edges()) {
            in_degree[edge.target()]++;
        }

        //queue to store vertices with in-degree 0
        std::queue<vertex_id_t> zero_in_degree_vertices;

        //initialize the queue with vertices having in-degree 0
        for (vertex_id_t vertex = 0; vertex < graph.num_vertices(); ++vertex) {
            if (in_degree[vertex] == 0) {
                zero_in_degree_vertices.push(vertex);
            }
        }

        while (!zero_in_degree_vertices.empty()) {
            vertex_id_t current_vertex = zero_in_degree_vertices.front();
            zero_in_degree_vertices.pop();

            topological_order.push_back(current_vertex);

            //remove the current vertex and its outgoing edges
            for (const auto& edge : graph.edges_from(current_vertex)) {
                vertex_id_t neighbor = edge.target();
                if (--in_degree[neighbor] == 0) {
                    zero_in_degree_vertices.push(neighbor);
                }
            }
        }

        //check for the presence of a cycle
        if (topological_order.size() != graph.num_vertices()) {
            return std::nullopt; //graph contains a cycle
        }

        return topological_order;
    }

}
