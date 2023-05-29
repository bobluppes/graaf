#include <cassert>
#include <iostream>

#include "minimum_spanning_tree.h"

void testMinimumSpanningTree() {
  // Test Case 1: Empty graph
  {
    graaf::graph<int, int> graph;
    auto result = graaf::algorithm::minimum_spanning_tree(graph);
    assert(result.empty());
  }

  // Test Case 2: Single vertex
  {
    graaf::graph<int, int> graph;
    graph.add_vertex(0);
    auto result = graaf::algorithm::minimum_spanning_tree(graph);
    assert(result.empty());
  }

  // Test Case 3: Linear graph
  {
    graaf::graph<int, int> graph;
    graph.add_vertex(0);
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(0, 1, 2);
    graph.add_edge(1, 2, 3);
    graph.add_edge(2, 3, 4);
    auto result = graaf::algorithm::minimum_spanning_tree(graph);
    std::vector<std::pair<graaf::vertex_id_t, graaf::vertex_id_t>> expected{
        {0, 1}, {1, 2}, {2, 3}};
    assert(result == expected);
  }

  // Test Case 4: Complete graph
  {
    graaf::graph<int, int> graph;
    graph.add_vertex(0);
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_edge(0, 1, 2);
    graph.add_edge(0, 2, 1);
    graph.add_edge(1, 2, 3);
    auto result = graaf::algorithm::minimum_spanning_tree(graph);
    std::vector<std::pair<graaf::vertex_id_t, graaf::vertex_id_t>> expected{
        {0, 2}, {0, 1}};
    assert(result == expected);
  }

  // Test Case 5: Graph with disconnected components
  {
    graaf::graph<int, int> graph;
    graph.add_vertex(0);
    graph.add_vertex(1);
    graph.add_vertex(2);
    graph.add_vertex(3);
    graph.add_edge(0, 1, 2);
    graph.add_edge(2, 3, 3);
    auto result = graaf::algorithm::minimum_spanning_tree(graph);
    std::vector<std::pair<graaf::vertex_id_t, graaf::vertex_id_t>> expected{
        {0, 1}, {2, 3}};
    assert(result == expected);
  }

  // If no assert fails print -
  std::cout << "All tests passed!\n";
}
