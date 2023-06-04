#include <graaflib/directed_graph.h>
#include <graaflib/undirected_graph.h>
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

namespace graaf {

template <typename T>
class my_weighted_edge : public weighted_edge<T> {
 public:
  explicit my_weighted_edge(T weight) : weight_{weight} {}

  [[nodiscard]] T get_weight() const noexcept override { return weight_; }

 private:
  T weight_{};
};

template <typename T>
struct WeightedGraphTest : public testing::Test {
  using graph_t = T::first_type;
  using edge_t = T::second_type;
};

using weighted_graph_types = testing::Types<

    /**
     * Primitive edge type directed graph
     */
    std::pair<directed_graph<int, bool>, bool>,
    std::pair<directed_graph<int, int>, int>,
    std::pair<directed_graph<int, unsigned long>, unsigned long>,
    std::pair<directed_graph<int, float>, float>,
    std::pair<directed_graph<int, long double>, long double>,

    /**
     * Non primitive weighted edge type directed graph
     */
    std::pair<directed_graph<int, my_weighted_edge<bool>>,
              my_weighted_edge<bool>>,
    std::pair<directed_graph<int, my_weighted_edge<int>>,
              my_weighted_edge<int>>,
    std::pair<directed_graph<int, my_weighted_edge<unsigned long>>,
              my_weighted_edge<unsigned long>>,
    std::pair<directed_graph<int, my_weighted_edge<float>>,
              my_weighted_edge<float>>,
    std::pair<directed_graph<int, my_weighted_edge<long double>>,
              my_weighted_edge<long double>>,

    /**
     * Primitive edge type undirected graph
     */
    std::pair<undirected_graph<int, bool>, bool>,
    std::pair<undirected_graph<int, int>, int>,
    std::pair<undirected_graph<int, unsigned long>, unsigned long>,
    std::pair<undirected_graph<int, float>, float>,
    std::pair<undirected_graph<int, long double>, long double>,

    /**
     * Non primitive weighted edge type undirected graph
     */
    std::pair<undirected_graph<int, my_weighted_edge<bool>>,
              my_weighted_edge<bool>>,
    std::pair<undirected_graph<int, my_weighted_edge<int>>,
              my_weighted_edge<int>>,
    std::pair<undirected_graph<int, my_weighted_edge<unsigned long>>,
              my_weighted_edge<unsigned long>>,
    std::pair<undirected_graph<int, my_weighted_edge<float>>,
              my_weighted_edge<float>>,
    std::pair<undirected_graph<int, my_weighted_edge<long double>>,
              my_weighted_edge<long double>>>;

TYPED_TEST_CASE(WeightedGraphTest, weighted_graph_types);

// Type traits to extract the weight type from both classes and primitives
template <typename T>
struct extract_weight {
  using type = T;
};

template <typename T>
  requires requires { typename T::weight_t; }
struct extract_weight<T> {
  using type = typename T::weight_t;
};

TYPED_TEST(WeightedGraphTest, AddWeightedEdge) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = extract_weight<edge_t>::type;

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};

  // WHEN
  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{static_cast<weight_t>(3)});

  // THEN
  ASSERT_TRUE(graph.has_edge(vertex_id_1, vertex_id_2));
  ASSERT_EQ(graph.get_edge(vertex_id_1, vertex_id_2)->get_weight(),
            static_cast<weight_t>(3));
}

/**
 * We do not override the virtual get_weight method such that each edge has a
 * unit weight.
 */
template <typename T>
class my_unit_weighted_edge : public weighted_edge<T> {};

template <typename T>
struct UnitWeightedGraphTest : public testing::Test {
  using graph_t = T::first_type;
  using edge_t = T::second_type;
};

using unit_weighted_graph_types = testing::Types<

    /**
     * Unit weighted edge type directed graph
     */
    std::pair<directed_graph<int, my_unit_weighted_edge<bool>>,
              my_unit_weighted_edge<bool>>,
    std::pair<directed_graph<int, my_unit_weighted_edge<int>>,
              my_unit_weighted_edge<int>>,
    std::pair<directed_graph<int, my_unit_weighted_edge<unsigned long>>,
              my_unit_weighted_edge<unsigned long>>,
    std::pair<directed_graph<int, my_unit_weighted_edge<float>>,
              my_unit_weighted_edge<float>>,
    std::pair<directed_graph<int, my_unit_weighted_edge<long double>>,
              my_unit_weighted_edge<long double>>,

    /**
     * Unit weighted edge type undirected graph
     */
    std::pair<undirected_graph<int, my_unit_weighted_edge<bool>>,
              my_unit_weighted_edge<bool>>,
    std::pair<undirected_graph<int, my_unit_weighted_edge<int>>,
              my_unit_weighted_edge<int>>,
    std::pair<undirected_graph<int, my_unit_weighted_edge<unsigned long>>,
              my_unit_weighted_edge<unsigned long>>,
    std::pair<undirected_graph<int, my_unit_weighted_edge<float>>,
              my_unit_weighted_edge<float>>,
    std::pair<undirected_graph<int, my_unit_weighted_edge<long double>>,
              my_unit_weighted_edge<long double>>>;

TYPED_TEST_CASE(UnitWeightedGraphTest, unit_weighted_graph_types);

TYPED_TEST(UnitWeightedGraphTest, AddUnitWeightedEdge) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = extract_weight<edge_t>::type;

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};

  // WHEN
  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{});

  // THEN
  ASSERT_TRUE(graph.has_edge(vertex_id_1, vertex_id_2));

  // By default each edge has a unit weight
  ASSERT_EQ(graph.get_edge(vertex_id_1, vertex_id_2)->get_weight(),
            static_cast<weight_t>(1));
}

/**
 * We do not derive from weighted edge, so we do not have the default provided
 * get_weight method.
 */
template <typename T>
struct my_unweighted_edge {
  using weight_t = T;
  T val{};
};

template <typename T>
struct UnweightedGraphTest : public testing::Test {
  using graph_t = T::first_type;
  using edge_t = T::second_type;
};

using unweighted_graph_types = testing::Types<

    /**
     * Unweighted edge type directed graph
     */
    std::pair<directed_graph<int, my_unweighted_edge<bool>>,
              my_unweighted_edge<bool>>,
    std::pair<directed_graph<int, my_unweighted_edge<int>>,
              my_unweighted_edge<int>>,
    std::pair<directed_graph<int, my_unweighted_edge<unsigned long>>,
              my_unweighted_edge<unsigned long>>,
    std::pair<directed_graph<int, my_unweighted_edge<float>>,
              my_unweighted_edge<float>>,
    std::pair<directed_graph<int, my_unweighted_edge<long double>>,
              my_unweighted_edge<long double>>,

    /**
     * Unweighted edge type undirected graph
     */
    std::pair<undirected_graph<int, my_unweighted_edge<bool>>,
              my_unweighted_edge<bool>>,
    std::pair<undirected_graph<int, my_unweighted_edge<int>>,
              my_unweighted_edge<int>>,
    std::pair<undirected_graph<int, my_unweighted_edge<unsigned long>>,
              my_unweighted_edge<unsigned long>>,
    std::pair<undirected_graph<int, my_unweighted_edge<float>>,
              my_unweighted_edge<float>>,
    std::pair<undirected_graph<int, my_unweighted_edge<long double>>,
              my_unweighted_edge<long double>>>;

TYPED_TEST_CASE(UnweightedGraphTest, unweighted_graph_types);

TYPED_TEST(UnweightedGraphTest, AddUnweightedEdge) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  using edge_t = typename TestFixture::edge_t;
  using weight_t = extract_weight<edge_t>::type;

  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};

  // WHEN
  graph.add_edge(vertex_id_1, vertex_id_2, edge_t{static_cast<weight_t>(42)});

  // THEN
  ASSERT_TRUE(graph.has_edge(vertex_id_1, vertex_id_2));

  // By default each edge has a unit weight
  ASSERT_EQ(graph.get_edge(vertex_id_1, vertex_id_2)->val,
            static_cast<weight_t>(42));
}

}  // namespace graaf