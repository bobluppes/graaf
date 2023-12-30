#include <graaflib/algorithm/graph_isomorphism.h>
#include <graaflib/algorithm/graph_isomorphism_util.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <gtest/gtest.h>

#include <optional>
#include <random>
#include <string>
#include <vector>

// delete later
#include <iostream>
#include <fstream>

class NullStreamBuffer : public std::streambuf {
public:
    int overflow(int c) { return traits_type::not_eof(c); }
};

namespace graaf::algorithm::vf2 {

class GraphIsomorphismTests : public testing::Test {};

TEST_F(GraphIsomorphismTests, testVf2WithSelfLoop){
	graph<int, int, graph_type::DIRECTED> G1;
	vertex_id_t zero = G1.add_vertex(0);
	vertex_id_t two = G1.add_vertex(1);
	vertex_id_t three = G1.add_vertex(2);

	G1.add_edge(zero, three, 1);

	std::cout << zero << " " << two << " " << three << std::endl << std::endl;
	
	graph<int, int, graph_type::DIRECTED> G2;
	vertex_id_t one = G2.add_vertex(0);
	vertex_id_t two_2 = G2.add_vertex(1);
	vertex_id_t three_2 = G2.add_vertex(2);
	
	G2.add_edge(one, two_2, 1);
	G2.add_edge(one, three_2, 1);
	std::cout << one << " " << two_2 << " " << three_2 << std::endl << std::endl;
		
	ASSERT_EQ(std::nullopt, check_isomorphism(G1, G2));

}

TEST_F(GraphIsomorphismTests, testIfGraphIsIsomorphic4) {
	std::streambuf* oldCoutBuffer = std::cout.rdbuf();
	NullStreamBuffer nullStreamBuffer;
	std::cout.rdbuf(&nullStreamBuffer);

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

  // THEN
  ASSERT_NE(std::nullopt, check_isomorphism(G1, G2));
  // WHEN
  G2.remove_edge(seven_2, nine_2);
  G2.add_edge(seven_2, eight_2, -1);
  // THEN
  ASSERT_EQ(std::nullopt, check_isomorphism(G1, G2));
  std::cout.rdbuf(oldCoutBuffer);
}


/*
class GraphIsomorphismTestsVf2TerminalSets : public testing::Test {};

class SetIntersectionTests : public testing::Test {};

TEST_F(SetIntersectionTests, testSetIntersectionWithNonemptySets) {
  // GIVEN
  std::unordered_set<vertex_id_t> setA, setB, setC;
  setA.insert(1);
  setA.insert(2);
  setA.insert(3);

  setB.insert(2);
  setB.insert(3);
  setB.insert(5);

  setC = set_intersection(setA, setB);

  // THEN
  // Check for existence of elements in A intersect B
  ASSERT_NE(setC.count(2), 0);
  ASSERT_NE(setC.count(3), 0);
  ASSERT_EQ(setC.count(5), 0);
  ASSERT_EQ(setC.count(1), 0);
}

TEST_F(SetIntersectionTests, testSetIntersectionWithOneEmptySets) {
  // GIVEN
  std::unordered_set<vertex_id_t> setA, setB, setC;
  setA.insert(1);
  setA.insert(2);
  setA.insert(3);

  setC = set_intersection(setA, setB);

  // GIVEN
  ASSERT_EQ(setC.size(), 0);
}

TEST_F(SetIntersectionTests, testSetIntersectionWithTwoEmptySets) {
  // GIVEN
  std::unordered_set<vertex_id_t> setA, setB, setC;
  setC = set_intersection(setA, setB);

  // THEN
  ASSERT_EQ(setC.size(), 0);
}

TEST_F(GraphIsomorphismTestsVf2TerminalSets,
       testUpdatingAndRestoringTerminalSetsAndMappingsForTout) {

  // GIVEN
  graph<int, int, graph_type::DIRECTED> G1;
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);
  vertex_id_t five = G1.add_vertex(5);
  vertex_id_t six = G1.add_vertex(6);
  vertex_id_t seven = G1.add_vertex(7);

  G1.add_edge(one, three, -1);
  G1.add_edge(three, one, -1);
  G1.add_edge(three, two, -1);
  G1.add_edge(four, three, -1);
  G1.add_edge(four, one, -1);
  G1.add_edge(five, two, -1);
  G1.add_edge(six, two, -1);
  G1.add_edge(six, seven, -1);

  // initialize the vf2_state, which is passed to various functions
  struct vf2_state* state = init_vf2_state(G1, G1);
  for (int i = 0; i < state->tout_1.size(); i++) {
    ASSERT_EQ(-1, state->tout_1[i]);
  }
  // at depth 1 of the recursion we shall update the mappings to include vertex
  // three
  size_t depth = 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(three),
                  state->lhs_node_order.at(three), depth);
  // THEN
  // check that the tout_1 set is updated properly
  ASSERT_EQ(state->tout_1[state->lhs_node_order.at(three)], 1);
  ASSERT_EQ(state->tout_1_len, 0);

  // update terminal_sets based on addition of vertex three made to the
  // vertex_mapping
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(three),
                       state->lhs_node_order.at(three), depth);

  // THEN
  ASSERT_EQ(state->tout_1[state->lhs_node_order.at(one)], 1);
  ASSERT_EQ(state->tout_1[state->lhs_node_order.at(two)], 1);
  ASSERT_NE(state->lhs_core[state->lhs_node_order.at(three)], -1);
  ASSERT_EQ(state->tout_1_len, 2);

  
  depth += 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(two),
                  state->lhs_node_order.at(two), depth);
  // THEN
  ASSERT_NE(state->lhs_core[state->lhs_node_order.at(two)], -1);
  ASSERT_EQ(state->tout_1_len, 1);

  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(two),
                       state->lhs_node_order.at(two), depth);
  // THEN
  ASSERT_EQ(state->tout_1[state->lhs_node_order.at(one)], 1);

  depth += 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(four),
                  state->lhs_node_order.at(four), depth);
  // THEN
  ASSERT_NE(state->lhs_core[state->lhs_node_order.at(four)], -1);
  ASSERT_EQ(state->tout_1_len, 1);

  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(four),
                       state->lhs_node_order.at(four), depth);
  ASSERT_EQ(state->tout_1_len, 1);

  depth += 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(six),
                  state->lhs_node_order.at(six), depth);
  // THEN
  ASSERT_NE(state->tout_1[state->lhs_node_order.at(six)], -1);
  ASSERT_EQ(state->tout_1_len, 1);

  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(six),
                       state->lhs_node_order.at(six), depth);
  // THEN
  ASSERT_NE(state->tout_1[state->lhs_node_order.at(six)], -1);
  ASSERT_EQ(state->tout_1[state->lhs_node_order.at(seven)], depth);
  ASSERT_EQ(state->tout_1_len, 2);

  ASSERT_EQ(state->tin_1_len, 2);
  ASSERT_EQ(state->tin_2_len, 2);
  ASSERT_EQ(state->tout_2_len, 2);

  ASSERT_EQ(state->lhs_core_len, 4);
  ASSERT_EQ(state->rhs_core_len, 4);

  // now we will restore the vertex_mapping to each original state, by undoing
  // all of our actions eliminating vertex 6 from the mapping and its effect on
  // the terminal sets
  restore_mappings(G1, G1, state, state->lhs_node_order.at(six),
                   state->lhs_node_order.at(six), depth);
  // THEN
  ASSERT_EQ(state->lhs_core[state->lhs_node_order.at(six)], -1);
  ASSERT_EQ(state->tout_1[state->lhs_node_order.at(six)], -1);
  ASSERT_EQ(state->tout_1_len, 2);

  restore_terminal_sets(G1, G1, state, state->lhs_node_order.at(six),
                        state->lhs_node_order.at(six), depth);
  // THEN
  ASSERT_EQ(state->tout_1[state->lhs_node_order.at(seven)], -1);
  ASSERT_EQ(state->tout_1_len, 1);
  depth -= 1;

  // eliminating vertex 4 from the mapping and its effect on the terminal sets
  restore_mappings(G1, G1, state, state->lhs_node_order.at(four),
                   state->lhs_node_order.at(four), depth);
  ASSERT_EQ(state->lhs_core[state->lhs_node_order.at(four)], -1);
  ASSERT_EQ(state->tout_1[state->lhs_node_order.at(four)], -1);
  ASSERT_EQ(state->tout_1_len, 1);

  restore_terminal_sets(G1, G1, state, state->lhs_node_order.at(four),
                        state->lhs_node_order.at(four), depth);
  ASSERT_EQ(state->tout_1_len, 1);
  depth -= 1;

  // eliminating vertex 2 from the mapping and its effect on the terminal sets
  restore_mappings(G1, G1, state, state->lhs_node_order.at(two),
                   state->lhs_node_order.at(two), depth);
  ASSERT_EQ(state->lhs_core[state->lhs_node_order.at(two)], -1);
  ASSERT_EQ(state->tout_1[state->lhs_node_order.at(two)], 1);
  ASSERT_EQ(state->tout_1_len, 2);

  restore_terminal_sets(G1, G1, state, state->lhs_node_order.at(two),
                        state->lhs_node_order.at(two), depth);
  ASSERT_EQ(state->tout_1_len, 2);
  depth -= 1;

  // eliminating vertex 3 from the mapping and its effect on the terminal sets
  restore_mappings(G1, G1, state, state->lhs_node_order.at(three),
                   state->lhs_node_order.at(three), depth);
  // THEN
  ASSERT_EQ(state->lhs_core[state->lhs_node_order.at(three)], -1);
  ASSERT_EQ(state->tout_1[state->lhs_node_order.at(three)], -1);
  ASSERT_EQ(state->tout_1_len, 2);

  restore_terminal_sets(G1, G1, state, state->lhs_node_order.at(three),
                        state->lhs_node_order.at(three), depth);
  ASSERT_EQ(state->tout_1[state->lhs_node_order.at(one)], -1);
  ASSERT_EQ(state->tout_1[state->lhs_node_order.at(two)], -1);
  ASSERT_EQ(state->tout_1_len, 0);
  depth -= 1;

  ASSERT_EQ(state->tin_1_len, 0);
  ASSERT_EQ(state->tin_2_len, 0);
  ASSERT_EQ(state->tout_2_len, 0);
  ASSERT_EQ(state->lhs_core_len, 0);
  ASSERT_EQ(state->rhs_core_len, 0);

  delete state;
}

TEST_F(GraphIsomorphismTests, generatingCandidatePairsTest) {
  // GIVEN
  graph<int, int, graph_type::DIRECTED> G1;
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);
  vertex_id_t five = G1.add_vertex(5);
  vertex_id_t six = G1.add_vertex(6);
  vertex_id_t seven = G1.add_vertex(7);

  G1.add_edge(one, three, -1);
  G1.add_edge(three, one, -1);
  G1.add_edge(three, two, -1);
  G1.add_edge(four, three, -1);
  G1.add_edge(four, one, -1);
  G1.add_edge(five, two, -1);
  G1.add_edge(six, two, -1);
  G1.add_edge(six, seven, -1);

  struct vf2_state* state = init_vf2_state(G1, G1);

  // creating vector of expected vertex pairs for comparison
  std::vector<std::pair<vertex_id_t, vertex_id_t>> pairs;
  for (int i = 0; i < state->lhs_core.size(); i++) {
    for (int j = 0; j < state->rhs_core.size(); j++) {
      pairs.push_back(std::make_pair(i, j));
    }
  }

  // compare the pairs generated by generate_candidate_pairs to our expected
  // pairs WHEN
  std::vector<std::pair<vertex_id_t, vertex_id_t>> _pairs =
      generate_candidate_pairs(G1, G1, *state);
  for (const auto& item : _pairs) {
    bool found = false;
    for (int i = 0; i < pairs.size(); i++) {
      if (pairs[i].first == item.first && pairs[i].second == item.second) {
        found = true;
      }
    }
    // THEN
    ASSERT_EQ(found, true);
  }

  // update vertex_mapping to generate pairs from the tout_1 and tout_2 sets
  // WHEN
  size_t depth = 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(two),
                  state->lhs_node_order.at(two), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(two),
                       state->lhs_node_order.at(two), depth);

  // THEN
  ASSERT_EQ(state->tout_1_len, 0);
  ASSERT_EQ(state->tout_2_len, 0);
  ASSERT_EQ(state->tin_1_len, 3);
  ASSERT_EQ(state->tin_2_len, 3);

  // storing the expected pairs resulting from using the tin_1 and tin_2 sets
  std::vector<std::pair<vertex_id_t, vertex_id_t>> pairs_tin;
  pairs_tin.push_back(std::make_pair(state->lhs_node_order.at(three),
                                     state->rhs_node_order.at(three)));
  pairs_tin.push_back(std::make_pair(state->lhs_node_order.at(three),
                                     state->rhs_node_order.at(five)));
  pairs_tin.push_back(std::make_pair(state->lhs_node_order.at(three),
                                     state->rhs_node_order.at(six)));

  pairs_tin.push_back(std::make_pair(state->lhs_node_order.at(five),
                                     state->rhs_node_order.at(three)));
  pairs_tin.push_back(std::make_pair(state->lhs_node_order.at(five),
                                     state->rhs_node_order.at(five)));
  pairs_tin.push_back(std::make_pair(state->lhs_node_order.at(five),
                                     state->rhs_node_order.at(six)));

  pairs_tin.push_back(std::make_pair(state->lhs_node_order.at(six),
                                     state->rhs_node_order.at(six)));
  pairs_tin.push_back(std::make_pair(state->lhs_node_order.at(six),
                                     state->rhs_node_order.at(three)));
  pairs_tin.push_back(std::make_pair(state->lhs_node_order.at(six),
                                     state->rhs_node_order.at(five)));

  // comparing expected to returned vertex pairs
  // WHEN
  std::vector<std::pair<vertex_id_t, vertex_id_t>> _pairs_tin =
      generate_candidate_pairs(G1, G1, *state);
  for (const auto& item : _pairs_tin) {
    bool found = false;
    for (int i = 0; i < pairs_tin.size(); i++) {
      if (pairs_tin[i].first == item.first &&
          pairs_tin[i].second == item.second) {
        found = true;
      }
    }
    // THEN
    ASSERT_EQ(found, true);
  }

  // restore the additions made to the vertex_mappings
  // WHEN
  restore_mappings(G1, G1, state, state->lhs_node_order.at(two),
                   state->lhs_node_order.at(two), depth);
  restore_terminal_sets(G1, G1, state, state->lhs_node_order.at(two),
                        state->lhs_node_order.at(two), depth);

  // confirming that the restorations were successfull
  // THEN
  ASSERT_EQ(state->tout_1_len, 0);
  ASSERT_EQ(state->tout_2_len, 0);
  ASSERT_EQ(state->tin_1_len, 0);
  ASSERT_EQ(state->tin_2_len, 0);

  // updating vertex_mappings so generate_candidate_pairs generates pairs from
  // the tout_1 and tout_2 sets
  depth = 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(three),
                  state->lhs_node_order.at(three), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(three),
                       state->lhs_node_order.at(three), depth);

  // vector with expected vertex pairs from the function
  std::vector<std::pair<vertex_id_t, vertex_id_t>> pairs_tout;
  pairs_tout.push_back(std::make_pair(state->lhs_node_order.at(two),
                                      state->rhs_node_order.at(two)));
  pairs_tout.push_back(std::make_pair(state->lhs_node_order.at(two),
                                      state->rhs_node_order.at(one)));

  pairs_tout.push_back(std::make_pair(state->lhs_node_order.at(one),
                                      state->rhs_node_order.at(two)));
  pairs_tout.push_back(std::make_pair(state->lhs_node_order.at(one),
                                      state->rhs_node_order.at(one)));

  // comparing expected to returned vertex pairs
  // WHEN
  std::vector<std::pair<vertex_id_t, vertex_id_t>> _pairs_tout =
      generate_candidate_pairs(G1, G1, *state);
  for (const auto& item : _pairs_tout) {
    bool found = false;
    for (int i = 0; i < pairs_tout.size(); i++) {
      if (pairs_tout[i].first == item.first &&
          pairs_tout[i].second == item.second) {
        found = true;
      }
    }
    // THEN
    ASSERT_EQ(found, true);
  }

  // THEN
  ASSERT_EQ(state->tout_1_len, 2);
  ASSERT_EQ(state->tout_2_len, 2);
  ASSERT_EQ(state->tin_1_len, 2);
  ASSERT_EQ(state->tin_2_len, 2);

  // restoring additions made to mappings and then confirming that the
  // restorations were successfull WHEN
  restore_mappings(G1, G1, state, state->lhs_node_order.at(two),
                   state->lhs_node_order.at(two), depth);
  restore_terminal_sets(G1, G1, state, state->lhs_node_order.at(two),
                        state->lhs_node_order.at(two), depth);

  // THEN
  ASSERT_EQ(state->tout_1_len, 0);
  ASSERT_EQ(state->tout_2_len, 0);
  ASSERT_EQ(state->tin_1_len, 0);
  ASSERT_EQ(state->tin_2_len, 0);
  // cleanup dynamically allocated memory
  delete state;
}

TEST_F(GraphIsomorphismTests, testCheckForPossiblityGraphIsomorphism) {
  // GIVEN
  graph<int, int, graph_type ::UNDIRECTED> G1;
  graph<int, int, graph_type ::UNDIRECTED> G2;

  // THEN
  ASSERT_TRUE(graaf::algorithm::vf2::check_for_possibility_of_isomorphism(G1, G2));

  // WHEN
  vertex_id_t g1_vertex_one_id = G1.add_vertex(1);
  vertex_id_t g1_vertex_two_id = G1.add_vertex(2);
  // THEN
  ASSERT_FALSE(graaf::algorithm::vf2::check_for_possibility_of_isomorphism(G1, G2));
  // WHEN
  vertex_id_t g2_vertex_one_id = G2.add_vertex(1);
  vertex_id_t g2_vertex_two_id = G2.add_vertex(2);
  // THEN
  ASSERT_TRUE(graaf::algorithm::vf2::check_for_possibility_of_isomorphism(G1, G2));
  // WHEN
  G2.add_edge(g2_vertex_one_id, g2_vertex_two_id, 0);
  // THEN
  ASSERT_FALSE(graaf::algorithm::vf2::check_for_possibility_of_isomorphism(G1, G2));
  // WHEN
  G1.add_edge(g1_vertex_one_id, g1_vertex_two_id, 0);
  // THEN
  ASSERT_TRUE(graaf::algorithm::vf2::check_for_possibility_of_isomorphism(G1, G2));
}

TEST_F(GraphIsomorphismTests, testTheFunctionsThatCreateNodeOrderings) {
  // GIVEN
  graph<int, int, graph_type ::UNDIRECTED> G1;
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  // WHEN
  G1.remove_vertex(three);
  vertex_id_t four = G1.add_vertex(4);

  std::unordered_map<vertex_id_t, vertex_id_t> ordering;
  create_node_ordering(ordering, G1);

  std::unordered_map<vertex_id_t, vertex_id_t> reverse_ordering;
  create_reverse_node_ordering(ordering, reverse_ordering);

  for (const auto& pair : ordering) {
    // THEN
    ASSERT_TRUE(pair.first == reverse_ordering[ordering[pair.first]]);
  }
}

TEST_F(GraphIsomorphismTests, testGetPredecessorsDirectedGraph) {
  // GIVEN
  graph<int, int, graph_type ::DIRECTED> G1;
  vertex_id_t zero = G1.add_vertex(0);
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);

  G1.add_edge(three, zero, -1);
  G1.add_edge(four, zero, -1);
  G1.add_edge(zero, one, -1);
  G1.add_edge(zero, two, -1);
  G1.add_edge(zero, four, -1);
  G1.add_edge(two, zero, -1);
  G1.add_edge(two, four, -1);

  struct vf2_state* state = init_vf2_state(G1, G1);
  // set contains expected vertex id's from the function call
  std::unordered_set<vertex_id_t> ids = {two, four, three};
  // WHEN
  for (const auto& item : get_predecessors(G1, state->lhs_node_order,
                                           state->lhs_reverse_node_order,
                                           state->lhs_node_order.at(zero))) {
    // THEN
    ASSERT_NE(ids.count(state->lhs_reverse_node_order.at(item)), 0);
  }

  ids.clear();
  ids.insert(two);
  ids.insert(zero);
  // WHEN
  for (const auto& item : get_predecessors(G1, state->lhs_node_order,
                                           state->lhs_reverse_node_order,
                                           state->lhs_node_order.at(four))) {
    // THEN
    ASSERT_NE(ids.count(state->lhs_reverse_node_order.at(item)), 0);
  }

  ids.clear();
  ids.insert(zero);
  // WHEN
  for (const auto& item : get_predecessors(G1, state->lhs_node_order,
                                           state->lhs_reverse_node_order,
                                           state->lhs_node_order.at(two))) {
    // THEN
    ASSERT_NE(ids.count(state->lhs_reverse_node_order.at(item)), 0);
  }
  delete state;
}

TEST_F(GraphIsomorphismTests, testGetSuccessorsDirectedGraph) {
  // GIVEN
  graph<int, int, graph_type ::DIRECTED> G1;
  vertex_id_t zero = G1.add_vertex(0);
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);

  G1.add_edge(three, zero, -1);
  G1.add_edge(four, zero, -1);
  G1.add_edge(zero, one, -1);
  G1.add_edge(zero, two, -1);
  G1.add_edge(zero, four, -1);
  G1.add_edge(two, zero, -1);
  G1.add_edge(two, four, -1);

  struct vf2_state* state = init_vf2_state(G1, G1);
  // set contains expected vertex id's from the function call
  std::unordered_set<vertex_id_t> ids = {one, four, two};
  // WHEN
  for (const auto& item :
       get_successors(G1, state->lhs_node_order, state->lhs_reverse_node_order,
                      state->lhs_node_order.at(zero))) {
    // THEN
    ASSERT_NE(ids.count(state->lhs_reverse_node_order.at(item)), 0);
  }

  ids.clear();
  ids.insert(0);
  // WHEN
  for (const auto& item :
       get_successors(G1, state->lhs_node_order, state->lhs_reverse_node_order,
                      state->lhs_node_order.at(3))) {
    // THEN
    ASSERT_NE(ids.count(state->lhs_reverse_node_order.at(item)), 0);
  }

  ids.clear();
  ids.insert(4);
  ids.insert(0);
  // WHEN
  for (const auto& item :
       get_successors(G1, state->lhs_node_order, state->lhs_reverse_node_order,
                      state->lhs_node_order.at(2))) {
    // THEN
    ASSERT_NE(ids.count(state->lhs_reverse_node_order.at(item)), 0);
  }
  delete state;
}

TEST_F(GraphIsomorphismTests, testGetSuccessorsAndPredecessorsUndirectedGraph) {
  // GIVEN
  graph<int, int, graph_type::UNDIRECTED> G1;
  vertex_id_t one = G1.add_vertex(4);
  vertex_id_t three = G1.add_vertex(6);
  vertex_id_t two = G1.add_vertex(5);

  G1.add_edge(one, two, 0);
  G1.add_edge(two, three, 0);
  G1.add_edge(three, one, 0);

  // holds expected vertex ids from function calls
  std::set<vertex_id_t> ids = {
      two, three};  // the sucessors and predecessors of vertex one
  std::set<vertex_id_t> ids_2 = {
      two, one};  // the sucessors and predecessors of vertex three

  struct vf2_state* state = init_vf2_state(G1, G1);
  // WHEN
  for (const auto& node : get_successors(G1, state->lhs_node_order,
                                         state->lhs_reverse_node_order, one)) {
    // THEN
    ASSERT_NE(ids.count(node), 0);
  }
  for (const auto& node : get_predecessors(
           G1, state->lhs_node_order, state->lhs_reverse_node_order, one)) {
    // THEN
    ASSERT_NE(ids.count(node), 0);
  }

  for (const auto& node : get_successors(
           G1, state->lhs_node_order, state->lhs_reverse_node_order, three)) {
    // THEN
    ASSERT_NE(ids_2.count(node), 0);
  }
  for (const auto& node : get_predecessors(
           G1, state->lhs_node_order, state->lhs_reverse_node_order, three)) {
    // THEN
    ASSERT_NE(ids_2.count(node), 0);
  }
  delete state;
}

TEST_F(GraphIsomorphismTests, testRPredWithDirectedAndUndirectedGraph) {
  // GIVEN
  graph<int, int, graph_type::DIRECTED> G1;
  vertex_id_t zero = G1.add_vertex(0);
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);
  vertex_id_t five = G1.add_vertex(5);
  vertex_id_t six = G1.add_vertex(6);
  vertex_id_t seven = G1.add_vertex(7);
  G1.add_edge(one, two, -1);
  G1.add_edge(four, two, -1);
  G1.add_edge(five, two, -1);

  struct vf2_state* state = init_vf2_state(G1, G1);
  
  // WHEN
  size_t depth = 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(one),
                  state->lhs_node_order.at(one), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(one),
                       state->lhs_node_order.at(one), depth);

  depth += 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(four),
                  state->lhs_node_order.at(four), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(four),
                       state->lhs_node_order.at(four), depth);

  depth += 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(five),
                  state->lhs_node_order.at(five), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(five),
                       state->lhs_node_order.at(five), depth);
  // THEN
  ASSERT_EQ(r_pred(G1, G1, state, state->lhs_node_order.at(two),
                   state->lhs_node_order.at(two)),
            true);
  ASSERT_EQ(r_pred(G1, G1, state, state->lhs_node_order.at(two),
                   state->lhs_node_order.at(five)),
            false);
  delete state;
}

TEST_F(GraphIsomorphismTests, testRPredWithDirectedGraph) {
  // GIVEN
  graph<int, int, graph_type::UNDIRECTED> G1;
  vertex_id_t zero = G1.add_vertex(0);
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);
  vertex_id_t five = G1.add_vertex(5);
  vertex_id_t six = G1.add_vertex(6);
  vertex_id_t seven = G1.add_vertex(7);
  G1.add_edge(one, two, -1);
  G1.add_edge(four, two, -1);
  G1.add_edge(five, two, -1);

  struct vf2_state* state = init_vf2_state(G1, G1);

  // WHEN
  size_t depth = 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(one),
                  state->lhs_node_order.at(one), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(one),
                       state->lhs_node_order.at(one), depth);

  depth += 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(four),
                  state->lhs_node_order.at(four), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(four),
                       state->lhs_node_order.at(four), depth);

  depth += 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(five),
                  state->lhs_node_order.at(five), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(five),
                       state->lhs_node_order.at(five), depth);
  // THEN
  ASSERT_EQ(r_pred(G1, G1, state, state->lhs_node_order.at(two),
                   state->rhs_node_order.at(two)),
            true);
  ASSERT_EQ(r_pred(G1, G1, state, state->lhs_node_order.at(two),
                   state->rhs_node_order.at(five)),
            false);
  delete state;
}

TEST_F(GraphIsomorphismTests, testRSuccWithDirectedGraph) {
  // GIVEN
  graph<int, int, graph_type::DIRECTED> G1;
  vertex_id_t zero = G1.add_vertex(0);
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);
  vertex_id_t five = G1.add_vertex(5);
  vertex_id_t six = G1.add_vertex(6);
  vertex_id_t seven = G1.add_vertex(7);

  G1.add_edge(one, two, -1);
  G1.add_edge(one, zero, -1);

  struct vf2_state* state = init_vf2_state(G1, G1);
  
  // WHEN
  size_t depth = 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(zero),
                  state->lhs_node_order.at(zero), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(zero),
                       state->lhs_node_order.at(zero), depth);

  depth += 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(two),
                  state->lhs_node_order.at(two), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(two),
                       state->lhs_node_order.at(two), depth);
  // THEN
  ASSERT_EQ(r_succ(G1, G1, state, state->lhs_node_order.at(two),
                   state->rhs_node_order.at(two)),
            true);
  ASSERT_EQ(r_succ(G1, G1, state, state->lhs_node_order.at(two),
                   state->rhs_node_order.at(one)),
            false);
  delete state;
}

TEST_F(GraphIsomorphismTests, testRSuccWithUndirectedGraph) {
  // GIVEN
  graph<int, int, graph_type::UNDIRECTED> G1;
  vertex_id_t zero = G1.add_vertex(0);
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);
  vertex_id_t five = G1.add_vertex(5);
  vertex_id_t six = G1.add_vertex(6);
  vertex_id_t seven = G1.add_vertex(7);

  G1.add_edge(one, two, -1);
  G1.add_edge(one, zero, -1);

  struct vf2_state* state = init_vf2_state(G1, G1);
  
  // WHEN
  size_t depth = 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(zero),
                  state->lhs_node_order.at(zero), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(zero),
                       state->lhs_node_order.at(zero), depth);

  depth += 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(two),
                  state->lhs_node_order.at(two), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(two),
                       state->lhs_node_order.at(two), depth);
  // THEN
  ASSERT_EQ(r_succ(G1, G1, state, state->lhs_node_order.at(two),
                   state->rhs_node_order.at(two)),
            true);
  ASSERT_EQ(r_succ(G1, G1, state, state->lhs_node_order.at(two),
                   state->rhs_node_order.at(one)),
            false);
  delete state;
}

TEST_F(GraphIsomorphismTests, testRoutWithDirectedGraph) {
  // GIVEN
  graph<std::string, std::string, graph_type::DIRECTED> G1;
  vertex_id_t zero = G1.add_vertex("0");
  vertex_id_t one = G1.add_vertex("1");
  vertex_id_t two = G1.add_vertex("2");
  vertex_id_t three = G1.add_vertex("3");
  vertex_id_t four = G1.add_vertex("4");
  vertex_id_t five = G1.add_vertex("5");
  vertex_id_t six = G1.add_vertex("6");
  vertex_id_t seven = G1.add_vertex("7");

  G1.add_edge(one, zero, "");
  G1.add_edge(one, two, "");
  G1.add_edge(seven, zero, "");
  G1.add_edge(five, two, "");
  G1.add_edge(seven, six, "");

  struct vf2_state* state = init_vf2_state(G1, G1);
  
  // WHEN
  size_t depth = 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(seven),
                  state->rhs_node_order.at(seven), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(seven),
                       state->rhs_node_order.at(seven), depth);
  depth += 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(five),
                  state->rhs_node_order.at(five), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(five),
                       state->rhs_node_order.at(five), depth);
  // THEN
  ASSERT_EQ(r_out(G1, G1, state, state->lhs_node_order.at(one),
                  state->rhs_node_order.at(one)),
            true);
  delete state;
}

TEST_F(GraphIsomorphismTests, testRoutWithUndirectedGraph) {
  // GIVEN
  graph<std::string, std::string, graph_type::UNDIRECTED> G1;
  vertex_id_t zero = G1.add_vertex("0");
  vertex_id_t one = G1.add_vertex("1");
  vertex_id_t two = G1.add_vertex("2");
  vertex_id_t three = G1.add_vertex("3");
  vertex_id_t four = G1.add_vertex("4");
  vertex_id_t five = G1.add_vertex("5");
  vertex_id_t six = G1.add_vertex("6");
  vertex_id_t seven = G1.add_vertex("7");

  G1.add_edge(one, zero, "");
  G1.add_edge(one, two, "");
  G1.add_edge(seven, zero, "");
  G1.add_edge(five, two, "");
  G1.add_edge(seven, six, "");

  struct vf2_state* state = init_vf2_state(G1, G1);
 
  // WHEN
  size_t depth = 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(seven),
                  state->rhs_node_order.at(seven), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(seven),
                       state->rhs_node_order.at(seven), depth);
  depth += 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(five),
                  state->rhs_node_order.at(five), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(five),
                       state->rhs_node_order.at(five), depth);
  // THEN
  ASSERT_EQ(r_out(G1, G1, state, state->lhs_node_order.at(one),
                  state->rhs_node_order.at(one)),
            true);
  delete state;
}

TEST_F(GraphIsomorphismTests, testRinWithDirectedGraph) {
  // GIVEN
  graph<int, int, graph_type::DIRECTED> G1;
  vertex_id_t zero = G1.add_vertex(0);
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);
  vertex_id_t five = G1.add_vertex(5);
  vertex_id_t six = G1.add_vertex(6);
  vertex_id_t seven = G1.add_vertex(7);

  G1.add_edge(four, two, -1);
  G1.add_edge(five, two, -1);
  G1.add_edge(one, two, -1);
  G1.add_edge(two, six, -1);
  G1.add_edge(two, seven, -1);
  G1.add_edge(one, six, -1);
  G1.add_edge(two, seven, -1);
  struct vf2_state* state = init_vf2_state(G1, G1);
  
  // WHEN
  size_t depth = 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(one),
                  state->rhs_node_order.at(one), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(one),
                       state->rhs_node_order.at(one), depth);

  ASSERT_EQ(r_in(G1, G1, state, state->lhs_node_order.at(one),
                 state->rhs_node_order.at(one)),
            true);
  // THEN
  delete state;
}

TEST_F(GraphIsomorphismTests, testRinWithUndirectedGraph) {
  // GIVEN
  graph<int, int, graph_type::UNDIRECTED> G1;
  vertex_id_t zero = G1.add_vertex(0);
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);
  vertex_id_t five = G1.add_vertex(5);
  vertex_id_t six = G1.add_vertex(6);
  vertex_id_t seven = G1.add_vertex(7);

  G1.add_edge(four, two, -1);
  G1.add_edge(five, two, -1);
  G1.add_edge(one, two, -1);
  G1.add_edge(two, six, -1);
  G1.add_edge(two, seven, -1);
  G1.add_edge(one, six, -1);
  G1.add_edge(two, seven, -1);
  struct vf2_state* state = init_vf2_state(G1, G1);
 
  // WHEN
  size_t depth = 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(one),
                  state->rhs_node_order.at(one), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(one),
                       state->rhs_node_order.at(one), depth);
  // THEN
  ASSERT_EQ(r_in(G1, G1, state, state->lhs_node_order.at(one),
                 state->rhs_node_order.at(one)),
            true);
  delete state;
}

TEST_F(GraphIsomorphismTests, testRnewWithDirectedGraph) {
  // GIVEN
  graph<int, int, graph_type::DIRECTED> G1;
  vertex_id_t zero = G1.add_vertex(0);
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);
  vertex_id_t five = G1.add_vertex(5);
  vertex_id_t six = G1.add_vertex(6);
  vertex_id_t seven = G1.add_vertex(7);

  G1.add_edge(one, three, -1);
  G1.add_edge(three, one, -1);
  G1.add_edge(three, two, -1);
  G1.add_edge(four, three, -1);
  G1.add_edge(four, one, -1);
  G1.add_edge(five, two, -1);
  G1.add_edge(six, two, -1);
  G1.add_edge(seven, six, -1);

  struct vf2_state* state = init_vf2_state(G1, G1);
 
  // WHEN
  size_t depth = 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(one),
                  state->rhs_node_order.at(one), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(one),
                       state->rhs_node_order.at(one), depth);
  ASSERT_EQ(r_new(G1, G1, state, state->lhs_node_order.at(seven),
                  state->rhs_node_order.at(seven)),
            true);
  ASSERT_EQ(r_new(G1, G1, state, state->lhs_node_order.at(one),
                  state->rhs_node_order.at(two)),
            false);
  ASSERT_EQ(r_new(G1, G1, state, state->lhs_node_order.at(five),
                  state->rhs_node_order.at(five)),
            true);
  // THEN
  delete state;
}

TEST_F(GraphIsomorphismTests, testRnewWithUndirectedGraph) {
  // GIVEN
  graph<int, int, graph_type::UNDIRECTED> G1;
  vertex_id_t zero = G1.add_vertex(0);
  vertex_id_t one = G1.add_vertex(1);
  vertex_id_t two = G1.add_vertex(2);
  vertex_id_t three = G1.add_vertex(3);
  vertex_id_t four = G1.add_vertex(4);
  vertex_id_t five = G1.add_vertex(5);
  vertex_id_t six = G1.add_vertex(6);
  vertex_id_t seven = G1.add_vertex(7);

  G1.add_edge(one, three, -1);
  G1.add_edge(three, one, -1);
  G1.add_edge(three, two, -1);
  G1.add_edge(four, three, -1);
  G1.add_edge(four, one, -1);
  G1.add_edge(five, two, -1);
  G1.add_edge(six, two, -1);
  G1.add_edge(seven, six, -1);

  struct vf2_state* state = init_vf2_state(G1, G1);
 
  // WHEN
  size_t depth = 1;
  update_mappings(G1, G1, state, state->lhs_node_order.at(one),
                  state->rhs_node_order.at(one), depth);
  update_terminal_sets(G1, G1, state, state->lhs_node_order.at(one),
                       state->rhs_node_order.at(one), depth);
  ASSERT_EQ(r_new(G1, G1, state, state->lhs_node_order.at(seven),
                  state->rhs_node_order.at(seven)),
            true);
  ASSERT_EQ(r_new(G1, G1, state, state->lhs_node_order.at(one),
                  state->rhs_node_order.at(two)),
            false);
  ASSERT_EQ(r_new(G1, G1, state, state->lhs_node_order.at(five),
                  state->rhs_node_order.at(five)),
            true);
  // THEN
  delete state;
}

TEST_F(GraphIsomorphismTests,
       testToSeeIfIsomorphicDisconnectedDirectedGraphsAreLabeledAsIsomorphic) {
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
  // THEN
  ASSERT_NE(_optional, std::nullopt);
  // WHEN
  G2.remove_edge(three_2, five_2);
  // THEN
  ASSERT_EQ(check_isomorphism(G1, G2), std::nullopt);
  // WHEN
  G1.remove_edge(one, two);
  // THEN
  ASSERT_NE(check_isomorphism(G1, G2), std::nullopt);
}

TEST_F(
    GraphIsomorphismTests,
    testToSeeIfIsomorphicDisconnectedUndirectedGraphsAreLabeledAsIsomorphic) {
  // this test tests isomorphism between disconnected undirected graphs
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
  // THEN
  ASSERT_NE(_optional, std::nullopt);
  // WHEN
  G2.remove_edge(three_2, five_2);
  // THEN
  ASSERT_EQ(check_isomorphism(G1, G2), std::nullopt);
  // WHEN
  G1.remove_edge(one, two);
  // THEN
  ASSERT_NE(check_isomorphism(G1, G2), std::nullopt);
}

TEST_F(GraphIsomorphismTests, testIfGraphisIsomorphic) {
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
  std::optional<std::unordered_map<vertex_id_t, vertex_id_t>> _optional =
      check_isomorphism(G1, G2);
  // THEN
  ASSERT_NE(_optional, std::nullopt);
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
  std::optional<std::unordered_map<vertex_id_t, vertex_id_t>> _optional =
      check_isomorphism(G1, G2);
  // THEN
  ASSERT_NE(_optional, std::nullopt);
}

TEST_F(GraphIsomorphismTests, testIfGraphIsIsomorphic2) {
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
  std::optional<std::unordered_map<vertex_id_t, vertex_id_t>> _optional =
      check_isomorphism(G1, G2);
  // THEN
  ASSERT_NE(_optional, std::nullopt);
}

TEST_F(GraphIsomorphismTests, testIfGraphIsIsomorphic3) {
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

  // THEN
  ASSERT_NE(std::nullopt, check_isomorphism(G1, G2));

  // WHEN
  G2.remove_edge(three, seven);
  G2.add_edge(three, six, -1);
  // THEN
  ASSERT_EQ(std::nullopt, check_isomorphism(G1, G2));
}

TEST_F(GraphIsomorphismTests, testIfGraphIsIsomorphic4) {
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

  // THEN
  ASSERT_NE(std::nullopt, check_isomorphism(G1, G2));
  // WHEN
  G2.remove_edge(seven_2, nine_2);
  G2.add_edge(seven_2, eight_2, -1);
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
*/
}  // namespace graaf::algorithm
