#include <fmt/core.h>
#include <graaflib/graph.h>
#include <gtest/gtest.h>
#include <utils/fixtures/fixtures.h>

/**
 * Tests which test the common functionality of the graph
 * class go here. Any test specific to a graph specification
 * should go in the respective test files.
 */

namespace graaf {

template <typename T>
struct GraphTest : public testing::Test {
  using graph_t = T;
};

TYPED_TEST_SUITE(GraphTest, utils::fixtures::minimal_graph_types);

TYPED_TEST(GraphTest, VertexCount) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  ASSERT_EQ(graph.vertex_count(), 0);

  // WHEN - THEN
  const auto vertex_id_1{graph.add_vertex(10)};
  ASSERT_EQ(graph.vertex_count(), 1);
  ASSERT_TRUE(graph.has_vertex(vertex_id_1));
  ASSERT_EQ(graph.get_vertex(vertex_id_1), 10);

  // WHEN - THEN
  const auto vertex_id_2{graph.add_vertex(20)};
  ASSERT_EQ(graph.vertex_count(), 2);
  ASSERT_TRUE(graph.has_vertex(vertex_id_2));
  ASSERT_EQ(graph.get_vertex(vertex_id_2), 20);

  // WHEN - THEN
  constexpr int specific_id = 2;
  const auto vertex_specific_id{graph.add_vertex(30, specific_id)};
  ASSERT_EQ(graph.vertex_count(), 3);
  ASSERT_TRUE(graph.has_vertex(specific_id));
  ASSERT_EQ(graph.get_vertex(specific_id), 30);
}

TYPED_TEST(GraphTest, RemoveVertex) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};
  const auto vertex_id_3{graph.add_vertex(30)};

  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  graph.add_edge(vertex_id_1, vertex_id_3, 200);

  ASSERT_EQ(graph.vertex_count(), 3);
  ASSERT_EQ(graph.edge_count(), 2);

  // WHEN - THEN
  graph.remove_vertex(vertex_id_1);
  ASSERT_EQ(graph.vertex_count(), 2);
  ASSERT_EQ(graph.edge_count(), 0);
  ASSERT_FALSE(graph.has_vertex(vertex_id_1));
  ASSERT_TRUE(graph.has_vertex(vertex_id_2));
  ASSERT_TRUE(graph.has_vertex(vertex_id_3));

  // WHEN - removing a vertex
  graph.remove_vertex(vertex_id_2);
  // THEN - verify the vertex and edge count, adjacency list, and edges
  ASSERT_EQ(graph.vertex_count(), 1);
  ASSERT_FALSE(graph.has_vertex(vertex_id_2));
  ASSERT_FALSE(graph.has_vertex(vertex_id_1));
  ASSERT_TRUE(graph.has_vertex(vertex_id_3));
  ASSERT_EQ(graph.edge_count(), 0);
  ASSERT_FALSE(graph.has_edge(vertex_id_1, vertex_id_2));
  ASSERT_FALSE(graph.has_edge(vertex_id_2, vertex_id_3));

  // WHEN - removing a non-existent vertex
  const auto invalid_vertex_id = vertex_id_1 + vertex_id_3 + 1;
  graph.remove_vertex(invalid_vertex_id);

  // THEN - verify the vertex and edge count
  ASSERT_EQ(graph.vertex_count(), 1);
  ASSERT_FALSE(graph.has_vertex(invalid_vertex_id));
  ASSERT_FALSE(graph.has_vertex(vertex_id_1));
  ASSERT_TRUE(graph.has_vertex(vertex_id_3));
  ASSERT_EQ(graph.edge_count(), 0);
  ASSERT_FALSE(graph.has_edge(vertex_id_1, invalid_vertex_id));
  ASSERT_FALSE(graph.has_edge(invalid_vertex_id, vertex_id_3));
}

TYPED_TEST(GraphTest, RemoveEdge) {
  // GIVEN
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};

  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2{graph.add_vertex(20)};

  graph.add_edge(vertex_id_1, vertex_id_2, 100);
  ASSERT_EQ(graph.edge_count(), 1);
  ASSERT_TRUE(graph.has_edge(vertex_id_1, vertex_id_2));

  // WHEN
  graph.remove_edge(vertex_id_1, vertex_id_2);

  // THEN
  ASSERT_EQ(graph.edge_count(), 0);
  ASSERT_FALSE(graph.has_edge(vertex_id_1, vertex_id_2));

  // Removing an edge does not remove the vertices
  ASSERT_EQ(graph.vertex_count(), 2);
  ASSERT_TRUE(graph.has_vertex(vertex_id_1));
  ASSERT_TRUE(graph.has_vertex(vertex_id_2));
}

TYPED_TEST(GraphTest, AddEdge) {
  using graph_t = typename TestFixture::graph_t;

  graph_t graph{};
  const auto vertex_id_1{graph.add_vertex(10)};
  const auto vertex_id_2 = graph.vertex_count() + 1;

  ASSERT_THROW(
      {
        try {
          // Call the add_edge function with a non-existing vertex ID
          graph.add_edge(vertex_id_1, vertex_id_2, 100);
        } catch (const std::invalid_argument &ex) {
          // Verify that the exception message contains the expected error
          // message
          EXPECT_EQ(
              ex.what(),
              fmt::format("Vertices with ID [{}] and [{}] not found in graph.",
                          vertex_id_1, vertex_id_2));
          throw;
        }
      },
      std::invalid_argument);

  EXPECT_FALSE(graph.has_edge(vertex_id_1, vertex_id_2));
}

TYPED_TEST(GraphTest, VertexTests) {
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1{graph.add_vertex(1)};
  const auto vertex_id_2{graph.add_vertex(20)};

  // Verify that the graph has the first vertex with the given ID
  EXPECT_TRUE(graph.has_vertex(vertex_id_1));
  EXPECT_EQ(graph.get_vertex(vertex_id_1), 1);

  // The graph doesn't have the second vertex with the given ID
  const auto nonExistingVertexId = graph.vertex_count() + 1;

  ASSERT_THROW(
      {
        try {
          // Call the get_vertex function for a non-existing vertex
          [[maybe_unused]] const auto vertex{
              graph.get_vertex(nonExistingVertexId)};
          FAIL()
              << "Expected std::invalid_argument exception, but no exception "
                 "was thrown.";
        } catch (const std::invalid_argument &ex) {
          EXPECT_EQ(ex.what(),
                    fmt::format("Vertex with ID [{}] not found in graph.",
                                nonExistingVertexId));
          throw;
        }
      },
      std::invalid_argument);
  EXPECT_TRUE(graph.has_vertex(vertex_id_1));
  EXPECT_FALSE(graph.has_vertex(nonExistingVertexId));
  EXPECT_TRUE(graph.has_vertex(vertex_id_2));
  EXPECT_EQ(graph.get_vertex(vertex_id_2), 20);

  ASSERT_THROW(
      {
        try {
          // Add vertex to ID that already exists
          [[maybe_unused]] const auto duplicate_id{
              graph.add_vertex(50, vertex_id_1)};
          FAIL()
              << "Expected std::invalid_argument exception, but no exception "
                 "was thrown.";
        } catch (const std::invalid_argument &ex) {
          EXPECT_EQ(ex.what(), fmt::format("Vertex already exists at ID [{}]",
                                           vertex_id_1));
          throw;
        }
      },
      std::invalid_argument);
  EXPECT_EQ(graph.get_vertex(vertex_id_1), 1);
}

TYPED_TEST(GraphTest, GetEdgeNonExistingEdge) {
  using vertex_id_t = std::size_t;
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1 = graph.add_vertex(1);
  const auto vertex_id_2 = graph.add_vertex(2);
  const auto nonExistingVertexId = graph.vertex_count() + 1;
  ASSERT_THROW(
      {
        try {
          // Call the get_edge function for non-existing vertices
          [[maybe_unused]] const auto edge{
              graph.get_edge(vertex_id_1, nonExistingVertexId)};
          // If the above line doesn't throw an exception, fail the test
          FAIL()
              << "Expected std::invalid_argument exception, but no exception "
                 "was thrown.";
        } catch (const std::invalid_argument &ex) {
          // Verify that the exception message contains the expected error
          // message
          EXPECT_EQ(ex.what(),
                    fmt::format("No edge found between vertices [{}] -> [{}].",
                                vertex_id_1, nonExistingVertexId));
          throw;
        }
      },
      std::invalid_argument);
}

TYPED_TEST(GraphTest, ConstGetter) {
  using vertex_id_t = std::size_t;
  using graph_t = typename TestFixture::graph_t;
  graph_t graph{};
  const auto vertex_id_1 = graph.add_vertex(1);
  const auto vertex_id_2 = graph.add_vertex(2);
  graph.add_edge(vertex_id_1, vertex_id_2, 100);

  const auto test_getters_on_const_graph{[vertex_id_1, vertex_id_2](
                                             const graph_t &const_graph) {
    EXPECT_EQ(const_graph.get_vertex(vertex_id_1), 1);
    EXPECT_EQ(const_graph.get_vertex(vertex_id_2), 2);
    EXPECT_EQ(get_weight(const_graph.get_edge(vertex_id_1, vertex_id_2)), 100);
  }};

  ASSERT_NO_THROW(test_getters_on_const_graph(graph));
}

/**
 * Class which records whether or not it was copy constructed. Can be used to
 * check whether copy/move semantics are correctly implemented.
 */
class copy_recorder {
 public:
  // Default ctor
  copy_recorder() : copied_{false} {}

  // Copy ctor
  copy_recorder(const copy_recorder &) : copied_{true} {}

  // Move ctor
  copy_recorder(copy_recorder &&) noexcept : copied_{false} {}

  [[nodiscard]] bool is_copy_constructed() const { return copied_; }

 private:
  bool copied_{false};
};

class MoveTest : public testing::Test {
 protected:
  using graph_t = directed_graph<copy_recorder, copy_recorder>;
  graph_t graph_{};
  copy_recorder moveable_{};
};

TEST_F(MoveTest, VertexLvalueShouldNotBeMoved) {
  // WHEN we pass in an l-value
  const auto id{graph_.add_vertex(moveable_)};

  // THEN the vertex in the graph should be copy constructed
  EXPECT_TRUE(graph_.get_vertex(id).is_copy_constructed());
}

TEST_F(MoveTest, VertexRvalueShouldBeMoved) {
  // WHEN we pass in an r-value
  const auto id{graph_.add_vertex(std::move(moveable_))};

  // THEN the vertex in the graph should be move constructed
  EXPECT_FALSE(graph_.get_vertex(id).is_copy_constructed());
}

TEST_F(MoveTest, EdgeLvalueShouldNotBeMoved) {
  // GIVEN
  using vertex_t = graph_t::vertex_t;
  const auto lhs_vertex{graph_.add_vertex(vertex_t{})};
  const auto rhs_vertex{graph_.add_vertex(vertex_t{})};

  // WHEN we pass in an l-value
  graph_.add_edge(lhs_vertex, rhs_vertex, moveable_);

  // THEN the edge in the graph should be copy constructed
  EXPECT_TRUE(graph_.get_edge(lhs_vertex, rhs_vertex).is_copy_constructed());
}

TEST_F(MoveTest, EdgeRvalueShouldBeMoved) {
  // GIVEN
  using vertex_t = graph_t::vertex_t;
  const auto lhs_vertex{graph_.add_vertex(vertex_t{})};
  const auto rhs_vertex{graph_.add_vertex(vertex_t{})};

  // WHEN we pass in an r-value
  graph_.add_edge(lhs_vertex, rhs_vertex, std::move(moveable_));

  // THEN the edge in the graph should be move constructed
  EXPECT_FALSE(graph_.get_edge(lhs_vertex, rhs_vertex).is_copy_constructed());
}

}  // namespace graaf