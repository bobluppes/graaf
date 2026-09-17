#include <benchmark/benchmark.h>

#include <boost/graph/breadth_first_search.hpp>
#include <cstddef>

#include "utils/connected_subgraph.h"

namespace {

class count_examined_edges_visitor : public boost::default_bfs_visitor {
 public:
  explicit count_examined_edges_visitor(std::size_t& count) : count_{count} {}

  void examine_edge(const boost::graph_traits<utils::graph_t>::edge_descriptor&,
                    const utils::graph_t&) const {
    ++count_;
  }

 private:
  std::size_t& count_;
};

// graaf::algorithm::breadth_first_traverse() only marks a vertex as seen when
// it is popped from the queue, not when it is pushed, so a high-degree vertex
// can be enqueued (and its neighbors re-scanned) many times before it is
// finally marked seen - inflating its edge count well past a single, clean
// O(V+E) traversal. boost::breadth_first_search() doesn't share that quirk
// (it marks a vertex visited as soon as it's discovered, so each edge is
// examined at most once per direction), so the edge count reported here will
// be smaller than graaf's for the same subgraph - the wall-clock time is
// the fair comparison, not the edge count.
//
// The subgraph vertex cap is otherwise identical to the Graaf benchmark's,
// so both run a full traversal over the same-sized graph.
static void bm_breadth_first_search(benchmark::State& state,
                                    const utils::dataset& dataset_name,
                                    const std::size_t start_vertex,
                                    const std::size_t max_subgraph_vertices) {
  const auto subgraph{utils::construct_connected_subgraph(
      dataset_name, start_vertex, max_subgraph_vertices)};

  state.counters["subgraph_vertices_used"] =
      static_cast<double>(boost::num_vertices(subgraph.graph));

  for (auto _ : state) {
    std::size_t edges_examined{0};
    boost::breadth_first_search(
        subgraph.graph, subgraph.start_vertex,
        boost::visitor(count_examined_edges_visitor{edges_examined}));
    benchmark::DoNotOptimize(edges_examined);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_breadth_first_search, web_google,
                  utils::dataset::WEB_GOOGLE, 1, 7'500);
BENCHMARK_CAPTURE(bm_breadth_first_search, web_berkstan,
                  utils::dataset::WEB_BERK_STAN, 1, 1'050);
