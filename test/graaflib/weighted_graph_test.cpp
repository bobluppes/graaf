#include <graaflib/directed_graph.h>
#include <graaflib/undirected_graph.h>
#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

namespace graaf {

// TODO: push this into the base class
template <typename T>
class my_edge : public weighted_edge<T> {
 public:
  using type = T;
  explicit my_edge(T weight) : weight_{weight} {}

  [[nodiscard]] T get_weight() const noexcept override { return weight_; }

 private:
  T weight_{};
};

template <typename T>
struct WeightedGraphTest : public testing::Test {
  using graph_t = T::first_type;
  using edge_t = T::second_type;
};

using graph_types = testing::Types<

    /**
     * Primitive edge type directed graph
     */
    std::pair<directed_graph<int, bool>, bool>,
    std::pair<directed_graph<int, int>, int>,
    std::pair<directed_graph<int, unsigned long>, unsigned long>,
    std::pair<directed_graph<int, float>, float>,
    std::pair<directed_graph<int, long double>, long double>,

    /**
     * Non primitive edge type directed graph
     */
    std::pair<directed_graph<int, my_edge<bool>>, my_edge<bool>>,
    std::pair<directed_graph<int, my_edge<int>>, my_edge<int>>,
    std::pair<directed_graph<int, my_edge<unsigned long>>,
              my_edge<unsigned long>>,
    std::pair<directed_graph<int, my_edge<float>>, my_edge<float>>,
    std::pair<directed_graph<int, my_edge<long double>>, my_edge<long double>>,

    /**
     * Primitive edge type undirected graph
     */
    std::pair<undirected_graph<int, bool>, bool>,
    std::pair<undirected_graph<int, int>, int>,
    std::pair<undirected_graph<int, unsigned long>, unsigned long>,
    std::pair<undirected_graph<int, float>, float>,
    std::pair<undirected_graph<int, long double>, long double>,

    /**
     * Non primitive edge type undirected graph
     */
    std::pair<undirected_graph<int, my_edge<bool>>, my_edge<bool>>,
    std::pair<undirected_graph<int, my_edge<int>>, my_edge<int>>,
    std::pair<undirected_graph<int, my_edge<unsigned long>>,
              my_edge<unsigned long>>,
    std::pair<undirected_graph<int, my_edge<float>>, my_edge<float>>,
    std::pair<undirected_graph<int, my_edge<long double>>,
              my_edge<long double>>>;

TYPED_TEST_CASE(WeightedGraphTest, graph_types);

// Type traits to extract the weight type from both classes and primitives
template <typename T>
struct extract_weight {
  using type = T;
};

template <typename T>
  requires requires { typename T::type; }
struct extract_weight<T> {
  using type = typename T::type;
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

}  // namespace graaf