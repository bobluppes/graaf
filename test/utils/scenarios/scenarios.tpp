#pragma once

namespace graaf::utils::scenarios {

template <typename GRAPH_T>
scenario<GRAPH_T> create_tree_scenario() {
  std::vector<vertex_id_t> vertex_ids{};
  vertex_ids.reserve(5);

  GRAPH_T graph{};

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

template <typename GRAPH_T>
scenario<GRAPH_T> create_simple_graph_scenario() {
  std::vector<vertex_id_t> vertex_ids{};
  vertex_ids.reserve(5);

  GRAPH_T graph{};

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

}  // namespace graaf::utils::scenarios