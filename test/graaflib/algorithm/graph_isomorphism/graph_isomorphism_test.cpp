#include <graaflib/algorithm/graph_isomorphism/graph_isomorphism.h>
#include <graaflib/algorithm/graph_isomorphism/graph_isomorphism_util.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

#include <optional>
#include <string>
#include <vector>

namespace graaf::algorithm{

class GraphIsomorphismTests : public testing::Test {};

TEST_F(GraphIsomorphismTests, testIfGraphsWithNoIsomorphismAndSelfLoopsReturnNoIsomorphism){
	//GIVEN
	graph<int, int, graph_type::DIRECTED> G1;
	vertex_id_t zero = G1.add_vertex(0);
	vertex_id_t two = G1.add_vertex(2);
	vertex_id_t three = G1.add_vertex(3);
	
	//WHEN
	G1.add_edge(zero, three, 1);

	graph<int, int, graph_type::DIRECTED> G2;
	vertex_id_t one = G2.add_vertex(1);
	vertex_id_t two_2 = G2.add_vertex(2);
	vertex_id_t three_2 = G2.add_vertex(3);
	
	//WHEN
	G2.add_edge(one, two_2, 1);
	G2.add_edge(one, three_2, 1);
		
	//THEN
	ASSERT_EQ(std::nullopt, check_isomorphism(G1, G2));

}

TEST_F(GraphIsomorphismTests, testIfLargeIsomorphicGraphsAreDeemedIsomorphic) {
  // GIVEN
  graph<int, int, graph_type::UNDIRECTED> G1;
  graph<int, int, graph_type::UNDIRECTED> G2;

  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);
  vertex_id_t five = G1.add_vertex(5);
  vertex_id_t six = G1.add_vertex(6);
  vertex_id_t seven = G1.add_vertex(7);
  vertex_id_t eight = G1.add_vertex(8);
  vertex_id_t nine = G1.add_vertex(9);
  vertex_id_t ten = G1.add_vertex(10);

  G1.add_edge(one, two, -1);
  G1.add_edge(one, five, -1);
  G1.add_edge(one, three, -1);
  G1.add_edge(two, four, -1);
  G1.add_edge(two, six, -1);
  G1.add_edge(three, nine, -1);
  G1.add_edge(three, eight, -1);
  G1.add_edge(eight, ten, -1);
  G1.add_edge(eight, four, -1);
  G1.add_edge(ten, five, -1);
  G1.add_edge(six, nine, -1);
  G1.add_edge(six, ten, -1);
  G1.add_edge(seven, nine, -1);
  G1.add_edge(four, seven, -1);
  G1.add_edge(five, seven, -1);
  
  vertex_id_t one_2 = G2.add_vertex(1);
  vertex_id_t two_2 = G2.add_vertex(2);
  vertex_id_t three_2 = G2.add_vertex(3);
  vertex_id_t four_2 = G2.add_vertex(4);
  vertex_id_t five_2 = G2.add_vertex(5);
  vertex_id_t six_2 = G2.add_vertex(6);
  vertex_id_t seven_2 = G2.add_vertex(7);
  vertex_id_t eight_2 = G2.add_vertex(8);
  vertex_id_t nine_2 = G2.add_vertex(9);
  vertex_id_t ten_2 = G2.add_vertex(10);
  
  G2.add_edge(one_2, two_2, -1);
  G2.add_edge(two_2, five_2, -1);
  G2.add_edge(five_2, four_2, -1);
  G2.add_edge(four_2, three_2, -1);
  G2.add_edge(three_2, one_2, -1);

  G2.add_edge(one_2, nine_2, -1);
  G2.add_edge(three_2, eight_2, -1);
  G2.add_edge(four_2, seven_2, -1);
  G2.add_edge(five_2, six_2, -1);
  G2.add_edge(two_2, ten_2, -1);

  G2.add_edge(ten_2, eight_2, -1);
  G2.add_edge(ten_2, seven_2, -1);
  G2.add_edge(six_2, nine_2, -1);
  G2.add_edge(six_2, eight_2, -1);
  G2.add_edge(seven_2, nine_2, -1);
	
	std::optional<std::unordered_map<vertex_id_t, vertex_id_t>> _optional = check_isomorphism(G1, G2).value();
	const auto mapping = _optional.value();
	
  // THEN
  ASSERT_NE(std::nullopt, _optional);
  
  //ASSERT CORRECTNESS OF MAPPING
  ASSERT_EQ(mapping.at(one), five_2);
  ASSERT_EQ(mapping.at(two), four_2);
  ASSERT_EQ(mapping.at(three), six_2);
  ASSERT_EQ(mapping.at(four), three_2);
  ASSERT_EQ(mapping.at(five), two_2);
  ASSERT_EQ(mapping.at(six), seven_2);
  ASSERT_EQ(mapping.at(seven), one_2);
  ASSERT_EQ(mapping.at(eight), eight_2);
  ASSERT_EQ(mapping.at(nine), nine_2);
  ASSERT_EQ(mapping.at(ten), ten_2);
  
  // WHEN
  G2.remove_edge(seven_2, nine_2);
  G2.add_edge(seven_2, eight_2, -1);
  // THEN
  ASSERT_EQ(std::nullopt, check_isomorphism(G1, G2));
}

TEST_F(GraphIsomorphismTests,
testToSeeIfTwoDirectedIsomorphicDisconnectedGraphsAreDeemedIsomorphic) {
  // this test tests isomorphism between disconnected directed graphs
  // GIVEN
  graph<float, int, graph_type::DIRECTED> G1;
  graph<float, int, graph_type::DIRECTED> G2;

  vertex_id_t one = G1.add_vertex(1.1);
  vertex_id_t two = G1.add_vertex(2.1);
  vertex_id_t three = G1.add_vertex(3.1);
  vertex_id_t four = G1.add_vertex(4.1);
  vertex_id_t five = G1.add_vertex(5.1);

  vertex_id_t one_2 = G2.add_vertex(1.1);
  vertex_id_t two_2 = G2.add_vertex(2.1);
  vertex_id_t three_2 = G2.add_vertex(3.1);
  vertex_id_t four_2 = G2.add_vertex(4.1);
  vertex_id_t five_2 = G2.add_vertex(5.1);

  G1.add_edge(one, two, 5);
  G2.add_edge(three_2, five_2, 5);
  
  // WHEN
  std::optional<vertex_mapping> _optional = check_isomorphism(G1, G2);
  const auto mapping = _optional.value();
  
  // THEN
  ASSERT_NE(_optional, std::nullopt);
  
  //ASSERT CORRECTNESS OF MAPPING
  ASSERT_EQ(mapping.at(one), three_2);
  ASSERT_EQ(mapping.at(two), five_2);
  
  // WHEN
  G2.remove_edge(three_2, five_2);
  // THEN
  ASSERT_EQ(check_isomorphism(G1, G2), std::nullopt);
  // WHEN
  G1.remove_edge(one, two);
  
  // THEN
  ASSERT_NE(check_isomorphism(G1, G2), std::nullopt);
  //NO CONNECTIONS EXIST IN EITHER GRAPH, SO THEY ARE BOTH ISOMORPHIC DUE TO THE NUMBER OF NODES
}

TEST_F(
    GraphIsomorphismTests, testToSeeIfTwoUndirectedIsomorphicDisconnectedGraphsAreDeemedIsomorphic) {
  //This test is the same as the last one but the graphs are undirected
  // GIVEN
  graph<float, int, graph_type::UNDIRECTED> G1;
  graph<float, int, graph_type::UNDIRECTED> G2;

  vertex_id_t one = G1.add_vertex(1.1);
  vertex_id_t two = G1.add_vertex(2.1);
  vertex_id_t three = G1.add_vertex(3.1);
  vertex_id_t four = G1.add_vertex(4.1);
  vertex_id_t five = G1.add_vertex(5.1);

  vertex_id_t one_2 = G2.add_vertex(1.1);
  vertex_id_t two_2 = G2.add_vertex(2.1);
  vertex_id_t three_2 = G2.add_vertex(3.1);
  vertex_id_t four_2 = G2.add_vertex(4.1);
  vertex_id_t five_2 = G2.add_vertex(5.1);

  G1.add_edge(one, two, 5);
  G2.add_edge(three_2, five_2, 5);
  
 std::optional<vertex_mapping> _optional = check_isomorphism(G1, G2);
  const auto mapping = _optional.value();
  
  // THEN
  ASSERT_NE(_optional, std::nullopt);
  
  //ASSERT CORRECTNESS OF MAPPING
  ASSERT_EQ(mapping.at(one), three_2);
  ASSERT_EQ(mapping.at(two), five_2);
  
  // WHEN
  G2.remove_edge(three_2, five_2);
  // THEN
  ASSERT_EQ(check_isomorphism(G1, G2), std::nullopt);
  // WHEN
  G1.remove_edge(one, two);
  // THEN
  ASSERT_NE(check_isomorphism(G1, G2), std::nullopt);
}

TEST_F(GraphIsomorphismTests, testIfDirectedSmallGraphIsIsomorphic) {
  // GIVEN
  graph<int, int, graph_type::DIRECTED> G1;
  graph<int, int, graph_type::DIRECTED> G2;

  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);
  vertex_id_t five = G1.add_vertex(5);

  G1.add_edge(four, three, -1);
  G1.add_edge(five, three, -1);
  G1.add_edge(three, one, -1);
  G1.add_edge(three, two, -1);

  vertex_id_t one_2 = G2.add_vertex(1);
  vertex_id_t two_2 = G2.add_vertex(2);
  vertex_id_t three_2 = G2.add_vertex(3);
  vertex_id_t four_2 = G2.add_vertex(4);
  vertex_id_t five_2 = G2.add_vertex(5);

  G2.add_edge(four_2, three_2, -1);
  G2.add_edge(five_2, three_2, -1);
  G2.add_edge(three_2, one_2, -1);
  G2.add_edge(three_2, two_2, -1);
  // WHEN
  auto _optional = check_isomorphism(G1, G2);
  const auto mapping = _optional.value();
  // THEN     
  ASSERT_NE(_optional, std::nullopt);
  
  ASSERT_EQ(mapping.at(three), three);
  ASSERT_TRUE(mapping.at(four) == four_2 || mapping.at(four) == five_2);
  ASSERT_TRUE(mapping.at(five) == five_2 || mapping.at(five) == four_2);
  ASSERT_TRUE(mapping.at(one) == two_2 || mapping.at(one) == one_2);
  ASSERT_TRUE(mapping.at(two) == one_2 || mapping.at(two) == two_2);
  
  
}

TEST_F(GraphIsomorphismTests, testIfUndirectedGraphIsIsomorphic) {
  // GIVEN
  graph<std::string, int, graph_type::UNDIRECTED> G1;
  graph<std::string, int, graph_type::UNDIRECTED> G2;

  vertex_id_t one = G1.add_vertex("1a");
  vertex_id_t two = G1.add_vertex("2a");
  vertex_id_t three = G1.add_vertex("3a");
  vertex_id_t four = G1.add_vertex("4a");
  vertex_id_t five = G1.add_vertex("5a");

  G1.add_edge(four, three, -1);
  G1.add_edge(five, three, -1);
  G1.add_edge(three, one, -1);
  G1.add_edge(three, two, -1);

  vertex_id_t one_2 = G2.add_vertex("6b");
  vertex_id_t two_2 = G2.add_vertex("7b");
  vertex_id_t three_2 = G2.add_vertex("8b");
  vertex_id_t four_2 = G2.add_vertex("9b");
  vertex_id_t five_2 = G2.add_vertex("10b");

  G2.add_edge(four_2, three_2, -1);
  G2.add_edge(five_2, three_2, -1);
  G2.add_edge(three_2, one_2, -1);
  G2.add_edge(three_2, two_2, -1);
  // WHEN
  auto _optional = check_isomorphism(G1, G2);
  const auto mapping = _optional.value();
  // THEN
  ASSERT_NE(_optional, std::nullopt);
  ASSERT_EQ(mapping.at(three), three);
  ASSERT_TRUE(mapping.at(four) == four_2 || mapping.at(four) == five_2);
  ASSERT_TRUE(mapping.at(five) == five_2 || mapping.at(five) == four_2);
  ASSERT_TRUE(mapping.at(one) == two_2 || mapping.at(one) == one_2);
  ASSERT_TRUE(mapping.at(two) == one_2 || mapping.at(two) == two_2);
  //ASSERTED CORRECTNESS OF VALUES IN MAPPING
}

TEST_F(GraphIsomorphismTests, testIfDirectedGraphIsIsomorphic) {
  // GIVEN
  graph<int, int, graph_type::DIRECTED> G1;
  graph<int, int, graph_type::DIRECTED> G2;
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);
  vertex_id_t five = G1.add_vertex(5);
  vertex_id_t six = G1.add_vertex(6);
  vertex_id_t seven = G1.add_vertex(7);

  G1.add_edge(one, two, -1);
  G1.add_edge(one, three, -1);
  G1.add_edge(four, two, -1);
  G1.add_edge(four, three, -1);
  G1.add_edge(four, one, -1);
  G1.add_edge(four, five, -1);
  G1.add_edge(four, seven, -1);

  vertex_id_t one_2 = G2.add_vertex(1);
  vertex_id_t two_2 = G2.add_vertex(2);
  vertex_id_t three_2 = G2.add_vertex(3);
  vertex_id_t four_2 = G2.add_vertex(4);
  vertex_id_t five_2 = G2.add_vertex(5);
  vertex_id_t six_2 = G2.add_vertex(6);
  vertex_id_t seven_2 = G2.add_vertex(7);

  G2.add_edge(one_2, two_2, -1);
  G2.add_edge(one_2, three_2, -1);
  G2.add_edge(four_2, two_2, -1);
  G2.add_edge(four_2, three_2, -1);
  G2.add_edge(four_2, one_2, -1);
  G2.add_edge(four_2, five_2, -1);
  G2.add_edge(four_2, seven_2, -1);
  // WHEN
  auto _optional = check_isomorphism(G1, G2);
  const auto mapping = _optional.value();

  // THEN
  ASSERT_NE(_optional, std::nullopt);
  ASSERT_EQ(mapping.at(one), one_2);
  ASSERT_EQ(mapping.at(two), two_2);
  ASSERT_EQ(mapping.at(three), three_2);
  ASSERT_EQ(mapping.at(four), four_2);
  ASSERT_EQ(mapping.at(five), five_2);
  ASSERT_EQ(mapping.at(six), six_2);
  ASSERT_EQ(mapping.at(seven), seven_2);
}

TEST_F(GraphIsomorphismTests, testIfUndirectedGraphIsIsomorphic2) {
  // GIVEN
  graph<int, int, graph_type::UNDIRECTED> G1;
  graph<int, int, graph_type::UNDIRECTED> G2;

  vertex_id_t a = G1.add_vertex(1);
  vertex_id_t g = G1.add_vertex(2);
  vertex_id_t b = G1.add_vertex(3);
  vertex_id_t h = G1.add_vertex(4);
  vertex_id_t c = G1.add_vertex(5);
  vertex_id_t i = G1.add_vertex(6);
  vertex_id_t d = G1.add_vertex(7);
  vertex_id_t j = G1.add_vertex(8);

  G1.add_edge(a, g, -1);
  G1.add_edge(a, h, -1);
  G1.add_edge(a, i, -1);
  G1.add_edge(b, g, 5);
  G1.add_edge(b, h, 67);
  G1.add_edge(b, j, -1);
  G1.add_edge(h, d, -1);
  G1.add_edge(g, c, -1);
  G1.add_edge(c, i, -1);
  G1.add_edge(c, j, -1);
  G1.add_edge(i, d, -1);
  G1.add_edge(d, j, -1);

  vertex_id_t one = G2.add_vertex(11);
  vertex_id_t two = G2.add_vertex(12);
  vertex_id_t three = G2.add_vertex(13);
  vertex_id_t four = G2.add_vertex(14);
  vertex_id_t five = G2.add_vertex(15);
  vertex_id_t six = G2.add_vertex(16);
  vertex_id_t seven = G2.add_vertex(17);
  vertex_id_t eight = G2.add_vertex(18);

  G2.add_edge(one, two, -1);
  G2.add_edge(one, four, -1);
  G2.add_edge(two, three, -1);
  G2.add_edge(four, three, -1);
  G2.add_edge(one, five, -1);
  G2.add_edge(two, six, -1);
  G2.add_edge(three, seven, -1);
  G2.add_edge(four, eight, -1);
  G2.add_edge(five, six, -1);
  G2.add_edge(six, seven, -1);
  G2.add_edge(seven, eight, -1);
  G2.add_edge(eight, five, -1);
	
auto _optional = check_isomorphism(G1,G2);
const auto mapping = _optional.value();
	
  // THEN
  ASSERT_NE(std::nullopt, _optional);
  ASSERT_EQ(mapping.at(a), two);
  ASSERT_EQ(mapping.at(g), one);
  ASSERT_EQ(mapping.at(b),four);
  ASSERT_EQ(mapping.at(h), three);
  ASSERT_EQ(mapping.at(c), five);
  ASSERT_EQ(mapping.at(i), six);
  ASSERT_EQ(mapping.at(d), seven);
  ASSERT_EQ(mapping.at(j), eight);
  

  // WHEN
  G2.remove_edge(three, seven);
  G2.add_edge(three, six, -1);
  // THEN
  ASSERT_EQ(std::nullopt, check_isomorphism(G1, G2));
}

TEST_F(GraphIsomorphismTests, testIfVF2CanIdentityIfGraphsAreNotIsomorphic) {
  // GIVEN
  graph<int, int, graph_type::DIRECTED> G1;
  graph<int, int, graph_type::DIRECTED> G2;
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);

  vertex_id_t one_2 = G2.add_vertex(1);
  vertex_id_t two_2 = G2.add_vertex(2);
  vertex_id_t three_2 = G2.add_vertex(3);

  G1.add_edge(one, two, -1);
  G1.add_edge(two, three, -1);
  G1.add_edge(three, one, -1);

  G2.add_edge(one_2, two_2, -1);
  G2.add_edge(two_2, three_2, -1);
  G2.add_edge(three_2, two_2, -1);
  // THEN
  ASSERT_EQ(check_isomorphism(G1, G2), std::nullopt);
}

TEST_F(
    GraphIsomorphismTests,
    testIfGraphIsNonIsomorphic){
	//GIVEN 
	graph<int,int, graph_type::UNDIRECTED> G1;
	graph<int,int, graph_type::UNDIRECTED> G2;
	
	vertex_id_t g1_1 = G1.add_vertex(1);
	vertex_id_t g1_2 = G1.add_vertex(2);
	vertex_id_t g1_3 = G1.add_vertex(3);
	vertex_id_t g1_4 = G1.add_vertex(4);
	
	vertex_id_t g2_1 = G2.add_vertex(1);
	vertex_id_t g2_2 = G2.add_vertex(2);
	vertex_id_t g2_3 = G2.add_vertex(3);
	vertex_id_t g2_4 = G2.add_vertex(4);
	
	G1.add_edge(g1_1, g1_2, -1);
	G1.add_edge(g1_1, g1_3, -1);
	G1.add_edge(g1_1, g1_4, -1);
	G1.add_edge(g1_2, g1_3, -1);
	
	G2.add_edge(g2_2, g2_4, -1);
	G2.add_edge(g2_2, g2_3, -1);
	G2.add_edge(g2_2, g2_1, -1);
	G2.add_edge(g2_3, g2_2, -1);
	
	ASSERT_EQ(std::nullopt, check_isomorphism(G1,G2));	
}
}  // namespace graaf::algorithm
