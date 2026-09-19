#pragma once

#include <graaflib/edge.h>
#include <graaflib/types.h>

#include <memory>
#include <optional>
#include <ranges>
#include <unordered_map>
#include <vector>

namespace graaf {

enum class graph_type { DIRECTED, UNDIRECTED };

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
class graph;

template <typename VERTEX_T, typename EDGE_T>
using directed_graph = graph<VERTEX_T, EDGE_T, graph_type::DIRECTED>;

template <typename VERTEX_T, typename EDGE_T>
using undirected_graph = graph<VERTEX_T, EDGE_T, graph_type::UNDIRECTED>;

// Forward declared so it can be granted friend access below: algorithms
// which require fine grained control over vertex id assignment get it
// through a private hook rather than through the public API.
template <typename VERTEX_T, typename EDGE_T>
directed_graph<VERTEX_T, EDGE_T> get_transposed_graph(
    const directed_graph<VERTEX_T, EDGE_T>& graph);

template <typename VERTEX_T, typename EDGE_T, graph_type GRAPH_TYPE_V>
class graph {
 public:
  using vertex_t = VERTEX_T;
  using edge_t = EDGE_T;

  using neighbors_t = std::vector<vertex_id_t>;

  using edge_id_to_edge_t = std::unordered_map<edge_id_t, edge_t, edge_id_hash>;

  /**
   * Checks whether graph is directed.
   *
   * @return bool - Return true for directed graphs otherwise false
   */
  [[nodiscard]] constexpr bool is_directed() const {
    return GRAPH_TYPE_V == graph_type::DIRECTED;
  }

  /**
   * Checks whether graph is undirected.
   *
   * @return bool - Returns true for undirected graphs otherwise false
   */
  [[nodiscard]] constexpr bool is_undirected() const {
    return GRAPH_TYPE_V == graph_type::UNDIRECTED;
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
   * @brief Get a read-only view over the graph's vertices
   *
   * If you store the result in a variable rather than using it directly in a
   * range-based for loop, store it as non-const (e.g. `auto`, not
   * `const auto&`) - a filtering range can't be iterated through a const
   * reference.
   *
   * @return A range yielding a (vertex_id_t, const VERTEX_T&) pair for every
   * vertex currently in the graph.
   */
  [[nodiscard]] auto get_vertices() const noexcept {
    return std::views::iota(vertex_id_t{0}, vertices_.size()) |
           std::views::filter(
               [this](vertex_id_t id) { return vertices_[id].has_value(); }) |
           std::views::transform([this](vertex_id_t id) {
             return std::pair<vertex_id_t, const VERTEX_T&>(id, *vertices_[id]);
           });
  }

  /**
   * @brief Get the internal edges
   *
   * One thing to note here is that edges are internally stored as shared
   * pointers to either the user provided edge type or to
   * primitive_numeric_adapter.
   *
   * @return const edge_id_to_edge_t& Map from edge id to edge_t.
   */
  [[nodiscard]] const edge_id_to_edge_t& get_edges() const noexcept {
    return edges_;
  }

  /**
   * Checks whether a vertex with a given ID is contained in the graph.
   *
   * @param  vertex_id The ID of the vertex we want to check
   * @return boolean - This returns True to indicate the vertex is contained in
   * the graph otherwise False
   */
  [[nodiscard]] bool has_vertex(vertex_id_t vertex_id) const noexcept;

  /**
   * Checks whether two vertices are connected
   *
   * @param  vertex_id_lhs The ID of the first vertex
   * @param  vertex_id_rhs The ID of the second vertex
   * @return boolean - This returns True to indicate there is an edge between
   * the two vertices otherwise False
   */

  [[nodiscard]] bool has_edge(vertex_id_t vertex_id_lhs,
                              vertex_id_t vertex_id_rhs) const noexcept;

  /**
   * Get a reference to the vertex using its vertex_id
   *
   * @param vertex_id The ID of the vertex
   * @return vertex_t - A reference to the vertex
   * @throws std::invalid_argument - If vertex_id does not exist within the
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
   * Get edge between two vertices with their vertex IDs
   *
   * @param  vertex_id_lhs The ID of the first vertex
   * @param  vertex_id_rhs The ID of the second vertex
   * @return edge_t - Shared pointer to either the provided edge or to
   * primitive_numeric_adapter.
   * @throws std::invalid_argument - If no edge exists between the two vertices
   */
  [[nodiscard]] edge_t& get_edge(vertex_id_t vertex_id_lhs,
                                 vertex_id_t vertex_id_rhs);

  /**
   * Get const version of edge between two vertices with their vertex IDs by
   * calling get_edge()
   *
   * @see    graph#get_edge()
   * @param  vertex_id_lhs The ID of the first vertex
   * @param  vertex_id_rhs The ID of the second vertex
   * @return edge_t - Shared pointer to either the provided edge or to
   * primitive_numeric_adapter.
   */
  [[nodiscard]] const edge_t& get_edge(vertex_id_t vertex_id_lhs,
                                       vertex_id_t vertex_id_rhs) const;

  /**
   * Get edge between two vertices with their edge ID
   *
   * @param  edge_id The ID of the edge.
   * @return edge_t - Shared pointer to either the provided edge or to
   * primitive_numeric_adapter.
   * @throws std::invalid_argument - If no edge exists between the two vertices
   */
  [[nodiscard]] edge_t& get_edge(const edge_id_t& edge_id);

  /**
   * Const version to get an edge between two vertices with their edge ID
   *
   * @param  edge_id The ID of the edge.
   * @return edge_t - Shared pointer to either the provided edge or to
   * primitive_numeric_adapter.
   * @throws std::invalid_argument - If no edge exists between the two vertices
   */
  [[nodiscard]] const edge_t& get_edge(const edge_id_t& edge_id) const;

  /**
   * Get a list of neighbour vertices
   *
   * For a directed graph, this returns the out-neighbors (successors) only,
   * i.e. the vertices reachable via an outgoing edge from vertex_id - matching
   * the vertices you'd find in Adj[vertex_id] in an adjacency-list
   * representation. It does not include predecessors (in-neighbors). For an
   * undirected graph, out- and in-neighbors coincide, so this returns all
   * adjacent vertices.
   *
   * @param  vertex_id The ID of the vertex
   * @return neighbors_t - A list of neighboring vertices
   */
  [[nodiscard]] const neighbors_t& get_neighbors(vertex_id_t vertex_id) const;

  /**
   * Add a vertex to the graph
   *
   * IDs are not permanently retired once assigned: a previously removed
   * vertex's ID may be handed out again to a later vertex. Do not hold on to
   * an ID past the removal of the vertex it identifies.
   *
   * @param  vertex The vertex to be added
   * @return vertices_id_t - The ID of the new vertex
   */
  [[nodiscard]] vertex_id_t add_vertex(auto&& vertex);

  /**
   * Remove a vertex from the graph and update all its neighbors
   *
   * The removed ID may be reassigned to a vertex added afterwards - see
   * add_vertex().
   *
   * @param  vertex_id - The ID of the vertex
   */
  void remove_vertex(vertex_id_t vertex_id);

  /**
   * Add a new edge between two existing vertices
   *
   * @param  vertex_id The ID of the vertex
   * @throws std::invalid_argument - If either of the vertices do not exist in
   * graph
   * @throws std::invalid_argument - If an edge already exists between the two
   * vertices. Use get_edge() and modify the returned edge in place, or call
   * remove_edge() first, to update an existing edge.
   */
  void add_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs,
                auto&& edge);

  /**
   * Remove the edge between two vertices
   *
   * @param  vertex_id_lhs The ID of the first vertex
   * @param  vertex_id_rhs The ID of the second vertex
   * @throws invalid_argument exception - If no edge exists between the two
   * vertices
   */
  void remove_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs);

 private:
  template <typename V, typename E>
  friend directed_graph<V, E> get_transposed_graph(
      const directed_graph<V, E>& graph);

  // Only reachable by befriended algorithms: the public API deliberately
  // does not let callers pick a vertex's id, so that the graph stays free to
  // optimize how it assigns them.
  vertex_id_t add_vertex_with_id(auto&& vertex, vertex_id_t id);

  std::unordered_map<vertex_id_t, neighbors_t> adjacency_list_{};

  // Indexed directly by vertex_id_t. A vertex_id_t below vertices_.size()
  // with no value is a tombstone left by remove_vertex(), pending reuse in
  // free_vertex_ids_.
  std::vector<std::optional<VERTEX_T>> vertices_{};
  std::size_t vertex_count_{0};

  edge_id_to_edge_t edges_{};

  // IDs freed by remove_vertex(), handed out again by add_vertex() before
  // growing vertex_id_supplier_. Keeps ids bounded by the high-water mark of
  // concurrently live vertices rather than the total ever created.
  std::vector<vertex_id_t> free_vertex_ids_{};

  size_t vertex_id_supplier_{0};
};

}  // namespace graaf

#include "graph.tpp"
