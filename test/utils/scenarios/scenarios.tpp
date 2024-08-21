#pragma once

namespace graaf::utils::scenarios
{

template<typename GRAPH_T>
scenario<GRAPH_T> create_tree_scenario()
{
    std::vector<vertex_id_t> vertex_ids {};
    vertex_ids.reserve(5);

    GRAPH_T graph {};

    vertex_ids.push_back(graph.add_vertex(10));
    vertex_ids.push_back(graph.add_vertex(20));
    vertex_ids.push_back(graph.add_vertex(30));
    vertex_ids.push_back(graph.add_vertex(40));
    vertex_ids.push_back(graph.add_vertex(50));

    graph.add_edge(vertex_ids[0], vertex_ids[1], 100);
    graph.add_edge(vertex_ids[0], vertex_ids[2], 200);
    graph.add_edge(vertex_ids[2], vertex_ids[3], 300);
    graph.add_edge(vertex_ids[2], vertex_ids[4], 400);

    return {std::move(graph), std::move(vertex_ids)};
}

template<typename GRAPH_T>
scenario<GRAPH_T> create_simple_graph_scenario()
{
    std::vector<vertex_id_t> vertex_ids {};
    vertex_ids.reserve(5);

    GRAPH_T graph {};

    vertex_ids.push_back(graph.add_vertex(10));
    vertex_ids.push_back(graph.add_vertex(20));
    vertex_ids.push_back(graph.add_vertex(30));
    vertex_ids.push_back(graph.add_vertex(40));
    vertex_ids.push_back(graph.add_vertex(50));

    graph.add_edge(vertex_ids[0], vertex_ids[1], 100);
    graph.add_edge(vertex_ids[1], vertex_ids[2], 200);
    graph.add_edge(vertex_ids[2], vertex_ids[0], 300);
    graph.add_edge(vertex_ids[2], vertex_ids[3], 400);
    graph.add_edge(vertex_ids[3], vertex_ids[4], 500);
    graph.add_edge(vertex_ids[2], vertex_ids[4], 600);

    return {std::move(graph), std::move(vertex_ids)};
}

template<typename GRAPH_T>
scenario<GRAPH_T> create_fully_connected_graph_scenario()
{
    std::vector<vertex_id_t> vertex_ids {};
    vertex_ids.reserve(5);

    GRAPH_T graph {};

    vertex_ids.push_back(graph.add_vertex(10));
    vertex_ids.push_back(graph.add_vertex(20));
    vertex_ids.push_back(graph.add_vertex(30));
    vertex_ids.push_back(graph.add_vertex(40));
    vertex_ids.push_back(graph.add_vertex(50));

    graph.add_edge(vertex_ids[0], vertex_ids[1], 100);
    graph.add_edge(vertex_ids[0], vertex_ids[2], 200);
    graph.add_edge(vertex_ids[0], vertex_ids[3], 300);
    graph.add_edge(vertex_ids[0], vertex_ids[4], 400);
    graph.add_edge(vertex_ids[1], vertex_ids[2], 500);
    graph.add_edge(vertex_ids[1], vertex_ids[3], 600);
    graph.add_edge(vertex_ids[1], vertex_ids[4], 700);
    graph.add_edge(vertex_ids[2], vertex_ids[3], 800);
    graph.add_edge(vertex_ids[2], vertex_ids[4], 900);
    graph.add_edge(vertex_ids[3], vertex_ids[4], 1000);

    return {std::move(graph), std::move(vertex_ids)};
}

template<typename GRAPH_T>
scenario<GRAPH_T> create_disconnected_graph_scenario()
{
    std::vector<vertex_id_t> vertex_ids {};
    vertex_ids.reserve(6);

    GRAPH_T graph {};

    vertex_ids.push_back(graph.add_vertex(10));
    vertex_ids.push_back(graph.add_vertex(20));
    vertex_ids.push_back(graph.add_vertex(30));

    vertex_ids.push_back(graph.add_vertex(40));
    vertex_ids.push_back(graph.add_vertex(50));
    vertex_ids.push_back(graph.add_vertex(60));

    graph.add_edge(vertex_ids[0], vertex_ids[1], 100);
    graph.add_edge(vertex_ids[0], vertex_ids[2], 200);

    graph.add_edge(vertex_ids[3], vertex_ids[4], 300);
    graph.add_edge(vertex_ids[4], vertex_ids[5], 400);
    graph.add_edge(vertex_ids[5], vertex_ids[3], 500);

    return {std::move(graph), std::move(vertex_ids)};
}

} // namespace graaf::utils::scenarios
