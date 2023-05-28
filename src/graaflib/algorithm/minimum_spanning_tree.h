#pragma once

#include <vector>
#include <utility>
#include <algorithm>

#include <graaflib/graph.h>
#include <graaflib/types.h>

namespace graaf::algorithm {

// Helper struct for representing disjoint sets
struct DisjointSet {
  std::vector<vertex_id_t> parent;
  std::vector<size_t> rank;

  DisjointSet(size_t num_vertices) {
    parent.resize(num_vertices);
    rank.resize(num_vertices, 0);
    for (vertex_id_t i = 0; i < num_vertices; ++i)
      parent[i] = i;
  }

  vertex_id_t find(vertex_id_t vertex) {
    if (vertex != parent[vertex])
      parent[vertex] = find(parent[vertex]);
    return parent[vertex];
  }

  void union_sets(vertex_id_t vertex1, vertex_id_t vertex2) {
    vertex_id_t root1 = find(vertex1);
    vertex_id_t root2 = find(vertex2);
    if (root1 != root2) {
      if (rank[root1] < rank[root2])
        std::swap(root1, root2);
      parent[root2] = root1;
      if (rank[root1] == rank[root2])
        ++rank[root1];
    }
  }
};

template <typename V, typename E, graph_spec S>
std::vector<std::pair<vertex_id_t, vertex_id_t>> minimum_spanning_tree(const graph<V, E, S>& graph) {
  using Edge = std::pair<edge_weight_t, std::pair<vertex_id_t, vertex_id_t>>;
  std::vector<Edge> edges;

  // Populate the edges vector with all edges in the graph
  for (vertex_id_t source = 0; source < graph.num_vertices(); ++source) {
    for (auto edge : graph.get_outgoing_edges(source)) {
      vertex_id_t target = edge.target;
      edge_weight_t weight = edge.weight;
      edges.push_back({weight, {source, target}});
    }
  }

  // Sort the edges in ascending order based on their weights
  std::sort(edges.begin(), edges.end());

  // Initialize the minimum spanning tree and the disjoint set
  std::vector<std::pair<vertex_id_t, vertex_id_t>> minimum_spanning_tree;
  DisjointSet disjoint_set(graph.num_vertices());

  // Perform Kruskal's algorithm
  for (const auto& edge : edges) {
    vertex_id_t source = edge.second.first;
    vertex_id_t target = edge.second.second;

    if (disjoint_set.find(source) != disjoint_set.find(target)) {
      disjoint_set.union_sets(source, target);
      minimum_spanning_tree.push_back({source, target});
    }
  }

  return minimum_spanning_tree;
}

}  // namespace graaf::algorithm
