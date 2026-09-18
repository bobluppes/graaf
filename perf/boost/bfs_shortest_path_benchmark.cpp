#include <benchmark/benchmark.h>

#include <boost/graph/breadth_first_search.hpp>
#include <cstddef>
#include <vector>

#include "utils/dataset_reader.h"

namespace {

using vertex_t = boost::graph_traits<utils::graph_t>::vertex_descriptor;

class track_last_examined_vertex_visitor : public boost::default_bfs_visitor {
 public:
  explicit track_last_examined_vertex_visitor(vertex_t& last) : last_{last} {}

  void examine_vertex(vertex_t vertex, const utils::graph_t&) const {
    last_ = vertex;
  }

 private:
  vertex_t& last_;
};

// Picks the vertex an exhaustive BFS over the graph examines last, so the
// shortest-path search below has to do close to the maximum possible amount
// of work before it can terminate early. An arbitrary vertex (e.g. the
// highest id) would give no such guarantee and can make the search
// terminate after visiting only a tiny, unrepresentative fraction of the
// graph.
[[nodiscard]] vertex_t find_last_examined_vertex(const utils::graph_t& graph,
                                                 vertex_t start_vertex) {
  vertex_t last{start_vertex};
  boost::breadth_first_search(
      graph, start_vertex,
      boost::visitor(track_last_examined_vertex_visitor{last}));
  return last;
}

// See the equivalent visitor in dijkstra_shortest_path_benchmark.cpp - same
// early-exit-via-exception technique, but examine_vertex fires here at the
// point boost::breadth_first_search would otherwise continue expanding the
// target's neighbors, matching where
// graaf::algorithm::bfs_shortest_path()'s search_termination_strategy stops
// the traversal.
struct target_reached {};

class stop_at_target_visitor : public boost::default_bfs_visitor {
 public:
  explicit stop_at_target_visitor(vertex_t target) : target_{target} {}

  void examine_vertex(vertex_t vertex, const utils::graph_t&) const {
    if (vertex == target_) {
      throw target_reached{};
    }
  }

 private:
  vertex_t target_;
};

static void bm_bfs_shortest_path(benchmark::State& state,
                                 const utils::dataset& dataset_name,
                                 const std::size_t start_vertex) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};
  const auto end_vertex{find_last_examined_vertex(graph, start_vertex)};

  std::vector<vertex_t> predecessors(boost::num_vertices(graph));

  for (auto _ : state) {
    try {
      boost::breadth_first_search(
          graph, start_vertex,
          boost::visitor(stop_at_target_visitor{end_vertex})
              .predecessor_map(boost::make_iterator_property_map(
                  predecessors.begin(),
                  boost::get(boost::vertex_index, graph))));
    } catch (const target_reached&) {
    }
    benchmark::DoNotOptimize(predecessors[end_vertex]);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_bfs_shortest_path, web_google, utils::dataset::WEB_GOOGLE,
                  1);
BENCHMARK_CAPTURE(bm_bfs_shortest_path, web_berkstan,
                  utils::dataset::WEB_BERK_STAN, 1);
