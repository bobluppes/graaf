# Kruskal's Algorithm

Kruskal's algorithm finds the minimum spanning forest of an undirected edge-weighted graph. If the graph is connected,
it finds a minimum spanning tree.
The algorithm is implemented with disjoint set union and finding minimum weighted edges.
Worst-case performance is `O(|E|log|V|)`, where `|E|` is the number of edges and `|V|` is the number of vertices in the
graph. Memory usage is `O(V+E)` for maintaining vertices (DSU) and edges.

[wikipedia](https://en.wikipedia.org/wiki/Kruskal%27s_algorithm)

## Syntax

Calculates the shortest path with the minimum edge sum.

```cpp
template <typename V, typename E>
[[nodiscard]] std::vector<edge_id_t> kruskal_minimum_spanning_tree(
    const graph<V, E, graph_type::UNDIRECTED>& graph);
```

- **graph** The graph to extract MST or MSF.
- **return** Returns a vector of edges that form MST if the graph is connected, otherwise it returns the minimum
  spanning forest.

### Special case

In case of multiply edges with same weight leading to a vertex, prioritizing vertices with lesser vertex number.

```cpp
std::sort(edges_to_process.begin(), edges_to_process.end(),
              [](detail::edge_to_process<E>& e1,
                 detail::edge_to_process<E>& e2) {
                       if (e1 != e2)
                           return e1.get_weight() < e2.get_weight();
          return e1.vertex_a < e2.vertex_a || e1.vertex_b < e2.vertex_b;
        });
```

For custom type edge, we should provide < and != operators

```cpp
struct custom_edge : public graaf::weighted_edge<int> {
 public:
  int weight_{};

  [[nodiscard]] int get_weight() const noexcept override { return weight_; }
 
  custom_edge(int weight): weight_{weight} {};
  custom_edge(){};
  ~custom_edge(){};

  // Providing '<' and '!=' operators for sorting edges
  bool operator<(const custom_edge& e) const noexcept {
    return this->weight_ < e.weight_;
  }
  bool operator!=(const custom_edge& e) const noexcept {
    return this->weight_ != e.weight_;
  }
};
```
