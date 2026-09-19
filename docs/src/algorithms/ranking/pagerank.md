# PageRank

PageRank assigns every vertex of a directed graph a score that reflects how important it is, based on the structure of
its incoming edges. A vertex is important if many vertices point to it, and more so if those vertices are important
themselves. It was originally designed to rank web pages, but applies to any network where an edge can be read as an
endorsement.

The score can be understood through a *random surfer*. The surfer starts at a uniformly random vertex. At every step,
with probability `d` (the damping factor) they follow one of the outgoing edges of their current vertex, chosen
uniformly at random; with probability `1 - d` they jump to a uniformly random vertex instead. The PageRank of a vertex is
the long run fraction of time the surfer spends there. Consequently, the ranks of all vertices sum to one.

A vertex without outgoing edges (a *dangling* vertex) would trap the surfer. Graaf treats such a vertex as if it had an
edge to every vertex in the graph, so the surfer jumps to a uniformly random vertex from there.

The ranks are computed by power iteration. All vertices start with a rank of `1 / |V|`, and every iteration updates the
rank of each vertex `v` as

```
PR(v) = (1 - d) / |V| + d * ( sum over edges u -> v of PR(u) / out_degree(u)
                             + sum over dangling vertices u of PR(u) / |V| )
```

Iteration stops once the sum of the absolute changes in rank over all vertices drops to or below the tolerance.

Each iteration runs in `O(|V| + |E|)` time, so the total runtime is `O(k * (|V| + |E|))` where `k` is the number of
iterations performed. The memory consumption is `O(|V|)`. Where V is the number of vertices in the graph and E the
number of edges.

[wikipedia](https://en.wikipedia.org/wiki/PageRank)

## Convergence

For a damping factor below one, the total change in rank shrinks by at least a factor `d` every iteration, so the number
of iterations needed is roughly `log(tolerance / 2) / log(d)` regardless of the size of the graph. With the defaults
(`d = 0.85`, `tolerance = 1e-6`) this is at most around 90 iterations, comfortably within the default limit of 100. A
lower damping factor converges faster; a damping factor close to one converges slowly.

With a damping factor of exactly one there is no random jump, and the ranks may never settle, for example when the rank
keeps bouncing around a cycle. In that case, or whenever the iteration limit is reached first, `std::nullopt` is
returned.

## Syntax

```cpp
template <typename V, typename E>
[[nodiscard]] std::optional<std::unordered_map<vertex_id_t, double>> pagerank(
    const graph<V, E, graph_type::DIRECTED>& graph,
    double damping_factor = 0.85, double tolerance = 1.0e-6,
    std::size_t max_iterations = 100);
```

- **graph** The directed graph to rank.
- **damping_factor** Probability of following an outgoing edge, in the range `[0, 1]`. Defaults to `0.85`.
- **tolerance** Convergence threshold on the sum of the absolute changes in rank between two consecutive iterations.
  Must be positive. Defaults to `1e-6`.
- **max_iterations** Maximum number of iterations. Must be positive. Defaults to `100`.
- **return** Map from each vertex id to its PageRank. If the ranks did not converge within `max_iterations`, returns
  `std::nullopt`. The ranks of an empty graph are an empty map.

A `std::invalid_argument` is thrown if the damping factor lies outside `[0, 1]`, the tolerance is not positive, or
`max_iterations` is zero.

Edge weights are ignored: every outgoing edge of a vertex is equally likely to be followed.

## Use cases

- Ranking web pages or documents by their links.
- Citation analysis, ranking papers or authors by who cites them.
- Influence scoring in social and organizational networks.
- Recommendation systems, ranking items by how they are connected to other items.
