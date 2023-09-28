#pragma once

#include <graaflib/types.h>

#include <algorithm>
#include <unordered_map>
#include <unordered_set>

namespace graaf::algorithm {

// Disjoint Set Union to maintain sets of vertices
namespace detail {
void do_make_set(vertex_id_t v,
                 std::unordered_map<vertex_id_t, vertex_id_t>& parent,
                 std::unordered_map<vertex_id_t, vertex_id_t>& rank) {
  parent[v] = v;
  rank[v] = 0;
}

vertex_id_t do_find_set(vertex_id_t vertex,
                        std::unordered_map<vertex_id_t, vertex_id_t>& parent) {
  if (vertex == parent[vertex]) {
    return vertex;
  }
  return parent[vertex] = do_find_set(parent[vertex], parent);
}

void do_merge_sets(vertex_id_t vertex_a, vertex_id_t vertex_b,
                   std::unordered_map<vertex_id_t, vertex_id_t>& parent,
                   std::unordered_map<vertex_id_t, vertex_id_t>& rank) {
  vertex_a = do_find_set(vertex_a, parent);
  vertex_b = do_find_set(vertex_b, parent);

  if (vertex_a != vertex_b) {
    if (rank[vertex_a] < rank[vertex_b]) {
      std::swap(vertex_a, vertex_b);
    }
    parent[vertex_b] = vertex_a;

    if (rank[vertex_a] == rank[vertex_b]) {
      ++rank[vertex_a];
    }
  }
}

template <typename T>
struct edge_to_process : public weighted_edge<T> {
 public:
  vertex_id_t vertex_a, vertex_b;
  T weight_;

  [[nodiscard]] T get_weight() const noexcept override { return weight_; }

  edge_to_process(vertex_id_t vertex_u, vertex_id_t vertex_w, T weight)
      : vertex_a{vertex_u}, vertex_b{vertex_w}, weight_{weight} {};
  edge_to_process(){};
  ~edge_to_process(){};

  bool operator!=(const edge_to_process& e) const noexcept {
    return this->weight_ != e.weight_;
  }
};

template <class GRAPH_T>
[[nodiscard]] std::vector<edge_id_t> find_candidate_edges(
    const GRAPH_T& graph,
    const std::unordered_set<vertex_id_t>& fringe_vertices) {
  std::vector<edge_id_t> candidates{};

  for (const auto fringe_vertex : fringe_vertices) {
    for (const auto neighbor : graph.get_neighbors(fringe_vertex)) {
      if (!fringe_vertices.contains(neighbor)) {
        candidates.emplace_back(fringe_vertex, neighbor);
      }
    }
  }

  return candidates;
}

};  // namespace detail

template <typename V, typename E>
std::vector<edge_id_t> kruskal_minimum_spanning_tree(
    const graph<V, E, graph_type::UNDIRECTED>& graph) {
  // unordered_map in case of deletion of vertices
  std::unordered_map<vertex_id_t, vertex_id_t> rank, parent;
  std::vector<detail::edge_to_process<E>> edges_to_process{};
  std::vector<edge_id_t> mst_edges{};

  for (const auto& vertex : graph.get_vertices()) {
    detail::do_make_set(vertex.first, parent, rank);
  }
  for (const auto& edge : graph.get_edges()) {
    edges_to_process.push_back(
        {edge.first.first, edge.first.second, edge.second});
  }

  std::sort(edges_to_process.begin(), edges_to_process.end(),
            [](detail::edge_to_process<E>& e1, detail::edge_to_process<E>& e2) {
              if (e1 != e2) return e1.get_weight() < e2.get_weight();
              return e1.vertex_a < e2.vertex_a || e1.vertex_b < e2.vertex_b;
            });

  for (const auto& edge : edges_to_process) {
    if (detail::do_find_set(edge.vertex_a, parent) !=
        detail::do_find_set(edge.vertex_b, parent)) {
      mst_edges.push_back({edge.vertex_a, edge.vertex_b});
      detail::do_merge_sets(edge.vertex_a, edge.vertex_b, parent, rank);
    }
    // Found MST E == V - 1
    if (mst_edges.size() == graph.vertex_count() - 1) return mst_edges;
  }
  // Returns minimum spanning forest
  return mst_edges;
}

template <typename V, typename E>
std::optional<std::vector<edge_id_t>> prim_minimum_spanning_tree(
    const graph<V, E, graph_type::UNDIRECTED>& graph,
    vertex_id_t start_vertex) {
  std::vector<edge_id_t> edges_in_mst{};
  edges_in_mst.reserve(
      graph.edge_count());  // Reserve the upper bound of edges in the mst

  std::unordered_set<vertex_id_t> fringe_vertices{start_vertex};

  while (fringe_vertices.size() < graph.vertex_count()) {
    const auto candidates{detail::find_candidate_edges(graph, fringe_vertices)};

    if (candidates.empty()) {
      // The graph is not connected
      return std::nullopt;
    }

    const edge_id_t mst_edge{*std::ranges::min_element(
        candidates,
        [graph](const edge_id_t& lhs, const edge_id_t& rhs) -> bool {
          return get_weight(graph.get_edge(lhs)) <
                 get_weight(graph.get_edge(rhs));
        })};

    edges_in_mst.emplace_back(mst_edge);
    fringe_vertices.insert(mst_edge.second);
  }

  return edges_in_mst;
}

};  // namespace graaf::algorithm
