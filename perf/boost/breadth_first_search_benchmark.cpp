#include <benchmark/benchmark.h>

#include <boost/graph/breadth_first_search.hpp>
#include <cstddef>

#include "utils/dataset_reader.h"

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

// Note that graaf reports only the tree edges to its edge callback, while
// boost's examine_edge fires for every edge, so the edge counts differ; the
// wall-clock time is the fair comparison.
static void bm_breadth_first_search(benchmark::State& state,
                                    const utils::dataset& dataset_name,
                                    const std::size_t start_vertex) {
  const auto& graph{utils::construct_graph_from_file(dataset_name)};

  for (auto _ : state) {
    std::size_t edges_examined{0};
    boost::breadth_first_search(
        graph, start_vertex,
        boost::visitor(count_examined_edges_visitor{edges_examined}));
    benchmark::DoNotOptimize(edges_examined);
  }
}

}  // namespace

// Register the benchmarks
BENCHMARK_CAPTURE(bm_breadth_first_search, web_google,
                  utils::dataset::WEB_GOOGLE, 1);
BENCHMARK_CAPTURE(bm_breadth_first_search, web_berkstan,
                  utils::dataset::WEB_BERK_STAN, 1);
