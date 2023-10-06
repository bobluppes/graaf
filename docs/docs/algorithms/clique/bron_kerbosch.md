---
sidebar_position: 1
---

# Bron-Kerbosch algorithm

Bron-Kerbosch algorithm finding all maximal cliques in an undirected graph. A clique is a subset of vertices such that
where every two distinct vertices are adjacent to each other.
The maximal clique is the subset of vertices of an undirected graph where no additional vertex can be added
due to the complete connectivity rule. The algorithm lists all maximum cliques of an undirected graph.

The worst-case run time of the algorithm is 3<sup>V/3</sup>.
[wikipedia](https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm#Worst-case_analysis)

## Syntax

```cpp
template <typename V, typename E>
std::vector<std::vector<vertex_id_t>> bron_kerbosch(
    const graph<V, E, graph_type::UNDIRECTED>& graph);
```

- **graph** The graph to extract maximal cliques.
- **return** Returns 2D vector of vertices each vector represent set of vertices that form clique.

