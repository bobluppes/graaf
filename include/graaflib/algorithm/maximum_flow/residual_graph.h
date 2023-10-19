#include <graaflib/graph.h>

#include <limits>
#include <queue>
#include <unordered_map>
#include <vector>

namespace graaf {

// Define an adapter class to hold residual capacities.
template <typename V, typename E, typename WEIGHT_T>
class residual_graph_adapter_t {
 public:
  using vertices_t = std::unordered_set<vertex_id_t>;
  residual_graph_adapter_t(
      const graph<V, E, graph_type::DIRECTED>& originalGraph)
      : original_graph(originalGraph) {
    // Initialize the residual capacities based on the original graph.
    for (const auto& [edge_id, edge] : original_graph.get_edges()) {
      residual_capacities[edge_id] = get_weight(edge);
    }
  }

  // Define functions to access the residual capacities.
  WEIGHT_T get_residual_capacity(vertex_id_t from, vertex_id_t to) const {
    const auto edge_id = std::make_pair(from, to);
    if (residual_capacities.count(edge_id)) {
      return residual_capacities.at(edge_id);
    }
    return 0;
  }

  void update_residual_capacity(vertex_id_t from, vertex_id_t to,
                                WEIGHT_T capacity) {
    const auto edge_id = std::make_pair(from, to);
    if (residual_capacities.count(edge_id)) {
      residual_capacities[edge_id] -= capacity;
    }
  }

  bool has_residual_capacity(vertex_id_t from, vertex_id_t to) const {
    return get_residual_capacity(from, to) > 0;
  }

  [[nodiscard]] vertices_t get_neighbors(vertex_id_t vertex_id) const {
    return original_graph.get_neighbors(vertex_id);
  }

 private:
  const graph<V, E, graph_type::DIRECTED>& original_graph;
  std::unordered_map<edge_id_t, WEIGHT_T, edge_id_hash> residual_capacities;
};

}  // namespace graaf