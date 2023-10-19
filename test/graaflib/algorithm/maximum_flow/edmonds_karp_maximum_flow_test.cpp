#include <graaflib/algorithm/maximum_flow/edmonds_karp.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

namespace graaf::algorithm {

namespace {
template <typename T>
struct TypedMaximumFlowTest : public testing::Test {
  using graph_t = T;
};

using graph_types =
    testing::Types<directed_graph<int, int>, undirected_graph<int, int>>;

TYPED_TEST_SUITE(TypedMaximumFlowTest, graph_types);

}  // namespace

template <typename T>
class my_weighted_edge : public weighted_edge<T> {
 public:
  explicit my_weighted_edge(T weight) : weight_{weight} {}

  [[nodiscard]] T get_weight() const noexcept override { return weight_; }

 private:
  T weight_{};
};

template <typename T>
struct EdmondsKarpMaximumFlowTest : public testing::Test {
  using graph_t = typename T::first_type;
  using edge_t = typename T::second_type;
};

using weighted_graph_types = testing::Types<

    /**
     * Primitive edge type directed graph
     */
    std::pair<directed_graph<int, int>, int>,
    std::pair<directed_graph<int, unsigned long>, unsigned long>,
    std::pair<directed_graph<int, float>, float>,
    std::pair<directed_graph<int, long double>, long double>,

    /**
     * Non primitive weighted edge type directed graph
     */

    std::pair<directed_graph<int, my_weighted_edge<int>>,
              my_weighted_edge<int>>,
    std::pair<directed_graph<int, my_weighted_edge<unsigned long>>,
              my_weighted_edge<unsigned long>>,
    std::pair<directed_graph<int, my_weighted_edge<float>>,
              my_weighted_edge<float>>,
    std::pair<directed_graph<int, my_weighted_edge<long double>>,
              my_weighted_edge<long double>>>;

TYPED_TEST_SUITE(EdmondsKarpMaximumFlowTest, weighted_graph_types);

TYPED_TEST(EdmondsKarpMaximumFlowTest, EdmondsKarpGraphWithoutFlowTest) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  const auto source = graph.add_vertex(10);
  const auto v1 = graph.add_vertex(20);
  const auto sink = graph.add_vertex(30);

  // All capacities are zero.
  graph.add_edge(source, v1, edge_t{static_cast<weight_t>(0)});
  graph.add_edge(v1, sink, edge_t{static_cast<weight_t>(0)});

  // Calculate manually the expected maximum flow value
  weight_t expected_max_flow = static_cast<weight_t>(0);  // No feasible flow

  // WHEN
  auto max_flow_value = edmonds_karp_max_flow(graph, source, sink);

  // THEN
  ASSERT_EQ(max_flow_value, expected_max_flow);
}

// Example from Baeldung
// https://www.baeldung.com/cs/network-flow-edmonds-karp-algorithm
TYPED_TEST(EdmondsKarpMaximumFlowTest, EdmondsKarpFlowNetworkTest) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  const auto source{graph.add_vertex(10)};
  const auto v1{graph.add_vertex(20)};
  const auto v2{graph.add_vertex(30)};
  const auto v3{graph.add_vertex(40)};
  const auto v4{graph.add_vertex(50)};
  const auto sink{graph.add_vertex(60)};

  graph.add_edge(source, v1, edge_t{static_cast<weight_t>(15)});
  graph.add_edge(source, v2, edge_t{static_cast<weight_t>(12)});
  graph.add_edge(v2, v1, edge_t{static_cast<weight_t>(10)});
  graph.add_edge(v1, v3, edge_t{static_cast<weight_t>(10)});
  graph.add_edge(v2, v3, edge_t{static_cast<weight_t>(5)});
  graph.add_edge(v4, v2, edge_t{static_cast<weight_t>(6)});
  graph.add_edge(v3, v4, edge_t{static_cast<weight_t>(8)});
  graph.add_edge(v3, sink, edge_t{static_cast<weight_t>(8)});
  graph.add_edge(v4, sink, edge_t{static_cast<weight_t>(13)});

  // Calculate manually the expected maximum flow value
  weight_t expected_max_flow = static_cast<weight_t>(15);

  // WHEN
  auto max_flow_value = edmonds_karp_max_flow(graph, source, sink);

  // THEN
  ASSERT_EQ(max_flow_value, expected_max_flow);
}

// Example from wikipedia article on Edmonds-Karp
TYPED_TEST(EdmondsKarpMaximumFlowTest, EdmondsKarpFlowNetwork2Test) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = decltype(get_weight(std::declval<edge_t>()));

  graph_t graph{};

  const auto a{graph.add_vertex(10)};
  const auto b{graph.add_vertex(20)};
  const auto c{graph.add_vertex(30)};
  const auto d{graph.add_vertex(40)};
  const auto e{graph.add_vertex(50)};
  const auto f{graph.add_vertex(60)};
  const auto g{graph.add_vertex(70)};

  graph.add_edge(a, b, edge_t{static_cast<weight_t>(3)});
  graph.add_edge(a, d, edge_t{static_cast<weight_t>(3)});
  graph.add_edge(b, c, edge_t{static_cast<weight_t>(4)});
  graph.add_edge(c, a, edge_t{static_cast<weight_t>(3)});
  graph.add_edge(c, d, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(c, e, edge_t{static_cast<weight_t>(2)});
  graph.add_edge(e, b, edge_t{static_cast<weight_t>(1)});
  graph.add_edge(d, e, edge_t{static_cast<weight_t>(2)});
  graph.add_edge(d, f, edge_t{static_cast<weight_t>(6)});
  graph.add_edge(f, g, edge_t{static_cast<weight_t>(9)});
  graph.add_edge(e, g, edge_t{static_cast<weight_t>(1)});

  // Calculate manually the expected maximum flow value
  weight_t expected_max_flow = static_cast<weight_t>(5);

  // WHEN
  auto max_flow_value = edmonds_karp_max_flow(graph, a, g);

  // THEN
  ASSERT_EQ(max_flow_value, expected_max_flow);
}

}  // namespace graaf::algorithm