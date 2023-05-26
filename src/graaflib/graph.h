#pragma once

#include <fmt/core.h>
#include <graaflib/types.h>

#include <algorithm>
#include <initializer_list>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <utility>

namespace graaf {

enum class graph_spec { DIRECTED, UNDIRECTED };

template <typename VERTEX_T, typename EDGE_T, graph_spec GRAPH_SPEC_V>
class graph {
 public:
  using vertex_t = VERTEX_T;
  using edge_t = EDGE_T;

  using vertex_ids_t = std::pair<vertex_id_t, vertex_id_t>;

  using vertices_t = std::unordered_set<vertex_id_t>;

  /**
   * Checks whether graph is directed.
   *
   * @return boolean - Return true for directed graph otherwise false
   */
  [[nodiscard]] constexpr bool is_directed() const {
    return GRAPH_SPEC_V == graph_spec::DIRECTED;
  }

  /**
   * Checks whether graph is undirected.
   *
   * @return boolean - Returns true for undirected graph otherwise false
   */
  [[nodiscard]] constexpr bool is_undirected() const {
    return GRAPH_SPEC_V == graph_spec::UNDIRECTED;
  }

  /**
   * Query the number of vertices
   *
   * @return size_t - Number of vertices
   */
  [[nodiscard]] std::size_t vertex_count() const noexcept;

  /**
   * Query the number of edges
   *
   * @return size_t - Number of edges
   */
  [[nodiscard]] std::size_t edge_count() const noexcept;

  /**
   * Checks whether a vertex with a given ID is contained in the graph.
   *
   * @param  vertex_id The ID of the vertex we want to check
   * @return boolean - This return Ture to indicate the vertex is contained in
   * the graph otherwise False
   */
  [[nodiscard]] bool has_vertex(vertex_id_t vertex_id) const noexcept;

  /**
   * Checks whether two vertices are connected
   *
   * @param  vertex_id_lhs The ID of the first vertex
   * @param  vertex_id_rhs The ID of the second vertex
   * @return boolean - This return Ture to indicate there is an edge between the
   * two vertices otherwise False
   */

  [[nodiscard]] bool has_edge(vertex_id_t vertex_id_lhs,
                              vertex_id_t vertex_id_rhs) const noexcept;

  /**
   * Get a reference to the vertex using its vertex_id
   *
   * @param vertex_id The ID of the vertex
   * @return vertex_t - A reference to the vertex
   * @throws out_of_range exception - If vertex_id does not existing within the
   * graph
   */
  [[nodiscard]] vertex_t& get_vertex(vertex_id_t vertex_id);

  /**
   * Get a const reference to the vertex using its vertex_id
   *
   * @see graph#get_vertex()
   * @param  vertex_id The ID of the vertex
   * @return vertex_t - A const reference to the vertex
   */

  [[nodiscard]] const vertex_t& get_vertex(vertex_id_t vertex_id) const;

  /**
   * Get edge between two vertices with theirs ID
   *
   * @param  vertex_id_lhs The ID of the first vertex
   * @param  vertex_id_rhs The ID of the second vertex
   * @return edge_t - A reference to edge
   * @throws out_of_range exception - If No edge exit between the two vertices
   */
  [[nodiscard]] edge_t& get_edge(vertex_id_t vertex_id_lhs,
                                 vertex_id_t vertex_id_rhs);

  /**
   * Get const version of edge between two vertices with their ID by calling
   * get_edge()
   *
   * @see    graph#get_edge()
   * @param  vertex_id_lhs The ID of the first vertex
   * @param  vertex_id_rhs The ID of the second vertex
   * @return edge_t - A const reference to the edge
   */
  [[nodiscard]] const edge_t& get_edge(vertex_id_t vertex_id_lhs,
                                       vertex_id_t vertex_id_rhs) const;

  /**
   * Get a list of neighbour vertices
   *
   * @param  vertex_id The ID of the vertex
   * @return vertices_t - A list of neigbounthood vertices
   */
  [[nodiscard]] vertices_t get_neighbors(vertex_id_t vertex_id) const;

  /**
   * Add a vertex to the graph
   *
   * @param  vertex The vertex to be added
   * @return vertices_id_t - The ID of the new vertex
   */
  vertex_id_t add_vertex(VERTEX_T vertex);

  /**
   * Remove a vertex from the graph and update all its neighbors
   *
   * @param  vertex_id - The ID of the vertex
   */
  void remove_vertex(vertex_id_t vertex_id);

  /**
   * Add a new edge between two existing vertices
   *
   * @param  vertex_id The ID of the vertex
   * @throws out_of_range - If either of the vertex does not exist in graph
   */
  void add_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs,
                EDGE_T edge);

  /**
   * Add two connected new vertices to the graph
   *
   * @param  vertex_id_lhs The ID of the first vertex
   * @param  vertex_id_rhs The ID of the second vertex
   * @param  edge
   * @return vertex_ids_t - Vertices ID of the pair of vertices
   */
  vertex_ids_t add_edge(VERTEX_T vertex_lhs, VERTEX_T vertex_rhs, EDGE_T edge);

  /**
   * Remove the edge between two vertices
   *
   * @param  vertex_id_lhs The ID of the first vertex
   * @param  vertex_id_rhs The ID of the second vertex
   */
  void remove_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs);

 protected:
  struct vertex_ids_hash {
    [[nodiscard]] std::size_t operator()(const vertex_ids_t& key) const {
      const auto h1{std::hash<vertex_id_t>{}(key.first)};
      const auto h2{std::hash<vertex_id_t>{}(key.second)};

      // TODO: use something like boost::hash_combine
      return h1 ^ h2;
    }
  };

  using vertex_id_to_vertex_t = std::unordered_map<vertex_id_t, vertex_t>;
  using vertex_ids_to_edge_t =
      std::unordered_map<vertex_ids_t, edge_t, vertex_ids_hash>;

  std::unordered_map<vertex_id_t, vertices_t> adjacency_list_{};

  vertex_id_to_vertex_t vertices_{};
  vertex_ids_to_edge_t edges_{};

 private:
  [[nodiscard]] virtual bool do_has_edge(
      vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) const noexcept = 0;
  [[nodiscard]] virtual edge_t& do_get_edge(vertex_id_t vertex_id_lhs,
                                            vertex_id_t vertex_id_rhs) = 0;
  virtual void do_add_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs,
                           EDGE_T edge) = 0;
  virtual void do_remove_edge(vertex_id_t vertex_id_lhs,
                              vertex_id_t vertex_id_rhs) = 0;

  size_t vertex_id_supplier_{0};
};

}  // namespace graaf

#include "graph.tpp"
