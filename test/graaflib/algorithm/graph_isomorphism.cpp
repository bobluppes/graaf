#include <gtest/gtest.h>
#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <graaflib/algorithm/graph_isomorphism.h>
#include <optional>
#include <vector>
#include <random>
#include <string>

namespace graaf :: algorithm {

class GraphIsomorphismTests : public testing::Test{
};

class GraphIsomorphismTestsVf2TerminalSets: public testing::Test{
};
	
TEST_F(GraphIsomorphismTestsVf2TerminalSets, testUpdatingAndRestoringTerminalSetsAndMappingsForTout){
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
	
	struct vf2_state * state = init_vf2_state(G1, G1);
	
 	for(int i = 0; i < state -> tout_1.size(); i++){
		ASSERT_EQ(-1, state -> tout_1[i]);
	}	
	
	size_t depth = 1;
	update_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(three),
		state -> lhs_node_order.at(three),
		depth
	); 
	ASSERT_EQ(state -> tout_1[state -> lhs_node_order.at(three)], 1);
	ASSERT_EQ(state -> tout_1_len, 0);
	
	
	update_terminal_sets(
		G1, 
		G1, 
		state,
		state -> lhs_node_order.at(three),
		state -> lhs_node_order.at(three),
		depth
	);
	
	ASSERT_EQ(state -> tout_1[state -> lhs_node_order.at(one)], 1);
	ASSERT_EQ(state -> tout_1[state -> lhs_node_order.at(two)], 1);
	ASSERT_NE(state -> lhs_core[state -> lhs_node_order.at(three)], -1);
	ASSERT_EQ(state -> tout_1_len, 2);
	
	depth += 1;
	update_mappings(G1, G1, state, state -> lhs_node_order.at(two), state -> lhs_node_order.at(two), depth);
	ASSERT_NE(state -> lhs_core[state -> lhs_node_order.at(two)], -1);
	ASSERT_EQ(state -> tout_1_len, 1);
	
	update_terminal_sets(G1, G1, state, state -> lhs_node_order.at(two), state -> lhs_node_order.at(two), depth);
	ASSERT_EQ(state -> tout_1[state -> lhs_node_order.at(one)], 1);
	
	
	depth += 1;
	update_mappings(G1, G1, state, state -> lhs_node_order.at(four), state -> lhs_node_order.at(four), depth);
	ASSERT_NE(state -> lhs_core[state -> lhs_node_order.at(four)], -1);
	ASSERT_EQ(state -> tout_1_len, 1);
	
	update_terminal_sets(G1, G1, state, state -> lhs_node_order.at(four), state -> lhs_node_order.at(four), depth);
	ASSERT_EQ(state -> tout_1_len, 1);
	
	depth += 1;
	update_mappings(G1, G1, state, state -> lhs_node_order.at(six), state -> lhs_node_order.at(six), depth);
	ASSERT_NE(state -> tout_1[state -> lhs_node_order.at(six)], -1);
	ASSERT_EQ(state -> tout_1_len, 1);
	
	update_terminal_sets(G1, G1, state, state -> lhs_node_order.at(six), state -> lhs_node_order.at(six), depth);
	ASSERT_NE(state -> tout_1[state -> lhs_node_order.at(six)], -1);
	ASSERT_EQ(state -> tout_1[state -> lhs_node_order.at(seven)], depth);
	ASSERT_EQ(state -> tout_1_len, 2);
	
	ASSERT_EQ(state -> tin_1_len, 2);
	ASSERT_EQ(state -> tin_2_len, 2);
	ASSERT_EQ(state -> tout_2_len, 2);
	
	ASSERT_EQ(state -> lhs_core_len, 4);			
	ASSERT_EQ(state -> rhs_core_len, 4);
	
	// RESTORE the mapping
	// to simulate the recursion we will get rid of 6 from the mapping
	
	restore_mappings(G1, G1, state, state -> lhs_node_order.at(six), state -> lhs_node_order.at(six), depth);
	ASSERT_EQ(state -> lhs_core[state -> lhs_node_order.at(six)], -1);
	ASSERT_EQ(state -> tout_1[state -> lhs_node_order.at(six)], -1);
	ASSERT_EQ(state -> tout_1_len, 2);
	
	restore_terminal_sets(G1, G1, state, state -> lhs_node_order.at(six), state -> lhs_node_order.at(six), depth);
	ASSERT_EQ(state -> tout_1[state -> lhs_node_order.at(seven)], -1);
	ASSERT_EQ(state -> tout_1_len, 1);
	depth -= 1;
	
	// eliminating 4 from mapping
	restore_mappings(G1, G1, state, state -> lhs_node_order.at(four), state -> lhs_node_order.at(four), depth);
	ASSERT_EQ(state -> lhs_core[state -> lhs_node_order.at(four)], -1);
	ASSERT_EQ(state -> tout_1[state -> lhs_node_order.at(four)], -1);
	ASSERT_EQ(state -> tout_1_len, 1);
	
	restore_terminal_sets(G1, G1, state, state -> lhs_node_order.at(four), state -> lhs_node_order.at(four), depth);
	ASSERT_EQ(state -> tout_1_len, 1);
	depth -= 1;
	
	// eliminating 2 from mapping
	restore_mappings(G1, G1, state, state -> lhs_node_order.at(two), state -> lhs_node_order.at(two), depth);
	ASSERT_EQ(state -> lhs_core[state -> lhs_node_order.at(two)], -1);
	ASSERT_EQ(state -> tout_1[state -> lhs_node_order.at(two)], 1);
	ASSERT_EQ(state -> tout_1_len, 2);
	
	restore_terminal_sets(G1, G1, state, state -> lhs_node_order.at(two), state -> lhs_node_order.at(two), depth);
	ASSERT_EQ(state -> tout_1_len, 2);
	depth -= 1;
	
	//eliminating 3 mapping
	restore_mappings(G1, G1, state, state -> lhs_node_order.at(three), state -> lhs_node_order.at(three), depth);
	ASSERT_EQ(state -> lhs_core[state -> lhs_node_order.at(three)], -1);
	ASSERT_EQ(state -> tout_1[state -> lhs_node_order.at(three)], -1);
	ASSERT_EQ(state -> tout_1_len, 2);
	
	restore_terminal_sets(G1, G1, state, state -> lhs_node_order.at(three), state -> lhs_node_order.at(three), depth);
	ASSERT_EQ(state -> tout_1[state -> lhs_node_order.at(one)], -1);
	ASSERT_EQ(state -> tout_1[state -> lhs_node_order.at(two)], -1);
	ASSERT_EQ(state -> tout_1_len, 0);
	depth -=1;
	
	ASSERT_EQ(state -> tin_1_len, 0);
	ASSERT_EQ(state -> tin_2_len, 0);
	ASSERT_EQ(state -> tout_2_len, 0);
	ASSERT_EQ(state -> lhs_core_len, 0);			
	ASSERT_EQ(state -> rhs_core_len, 0);			
	
	delete state;
				
}

TEST_F(GraphIsomorphismTests, generatingCandidatePairsTest){
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
	
	struct vf2_state * state = init_vf2_state(G1, G1);
	
	std::vector<std::pair<vertex_id_t, vertex_id_t>> pairs;
	for(int i = 0; i < state -> lhs_core.size(); i++){	
		for(int j = 0; j < state -> rhs_core.size(); j++){
			pairs.push_back(std::make_pair(i,j));
		}
	}
	
	// generation of P_D 
	std::vector<std::pair<vertex_id_t, vertex_id_t>> _pairs = generate_candidate_pairs(G1, G1, *state);
	for(const auto & item : _pairs){
		bool found = false;
		for(int i = 0; i < pairs.size(); i++){
			if(pairs[i].first == item.first && pairs[i].second == item.second){
				found = true;
			}
		}
		ASSERT_EQ(found, true);
	}
	
	size_t depth = 1;
	// generation of tin sets
	update_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(two),
		state -> lhs_node_order.at(two),
		depth
	); 
	update_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(two),
		state -> lhs_node_order.at(two),
		depth
	); 
	
	ASSERT_EQ(state -> tout_1_len, 0);
	ASSERT_EQ(state -> tout_2_len, 0);
	ASSERT_EQ(state -> tin_1_len, 3);
	ASSERT_EQ(state -> tin_2_len, 3);
	
	std::vector<std::pair<vertex_id_t, vertex_id_t>> pairs_tin;
	pairs_tin.push_back(std::make_pair(state -> lhs_node_order.at(three), state -> rhs_node_order.at(three)));
	pairs_tin.push_back(std::make_pair(state -> lhs_node_order.at(three), state -> rhs_node_order.at(five)));
	pairs_tin.push_back(std::make_pair(state -> lhs_node_order.at(three), state -> rhs_node_order.at(six)));
	
	pairs_tin.push_back(std::make_pair(state -> lhs_node_order.at(five), state -> rhs_node_order.at(three)));
	pairs_tin.push_back(std::make_pair(state -> lhs_node_order.at(five), state -> rhs_node_order.at(five)));
	pairs_tin.push_back(std::make_pair(state -> lhs_node_order.at(five), state -> rhs_node_order.at(six)));
	
	pairs_tin.push_back(std::make_pair(state -> lhs_node_order.at(six), state -> rhs_node_order.at(six)));
	pairs_tin.push_back(std::make_pair(state -> lhs_node_order.at(six), state -> rhs_node_order.at(three)));
	pairs_tin.push_back(std::make_pair(state -> lhs_node_order.at(six), state -> rhs_node_order.at(five)));
	
	std::vector<std::pair<vertex_id_t, vertex_id_t>> _pairs_tin = generate_candidate_pairs(G1, G1, *state);
	for(const auto & item : _pairs_tin){
		bool found = false;
		for(int i = 0; i < pairs_tin.size(); i++){
			if(pairs_tin[i].first == item.first && pairs_tin[i].second == item.second){
				found = true;
			}
		}
		ASSERT_EQ(found, true);
	}	
	
	restore_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(two),
		state -> lhs_node_order.at(two),
		depth
	); 
	restore_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(two),
		state -> lhs_node_order.at(two),
		depth
	); 
	
	ASSERT_EQ(state -> tout_1_len, 0);
	ASSERT_EQ(state -> tout_2_len, 0);
	ASSERT_EQ(state -> tin_1_len, 0);
	ASSERT_EQ(state -> tin_2_len, 0);
	
	// testing tout sets

	depth = 1;
	update_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(three),
		state -> lhs_node_order.at(three),
		depth
	); 
	update_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(three),
		state -> lhs_node_order.at(three),
		depth
	); 
	
	std::vector<std::pair<vertex_id_t, vertex_id_t>> pairs_tout;
	pairs_tout.push_back(std::make_pair(state -> lhs_node_order.at(two), state -> rhs_node_order.at(two)));
	pairs_tout.push_back(std::make_pair(state -> lhs_node_order.at(two), state -> rhs_node_order.at(one)));
	
	pairs_tout.push_back(std::make_pair(state -> lhs_node_order.at(one), state -> rhs_node_order.at(two)));
	pairs_tout.push_back(std::make_pair(state -> lhs_node_order.at(one), state -> rhs_node_order.at(one)));
	
	std::vector<std::pair<vertex_id_t, vertex_id_t>> _pairs_tout = generate_candidate_pairs(G1, G1, *state);
	for(const auto & item : _pairs_tout){
		bool found = false;
		for(int i = 0; i < pairs_tout.size(); i++){
			if(pairs_tout[i].first == item.first && pairs_tout[i].second == item.second){
				found = true;
			}
		}
		ASSERT_EQ(found, true);
	}
	
	ASSERT_EQ(state -> tout_1_len, 2);
	ASSERT_EQ(state -> tout_2_len, 2);
	ASSERT_EQ(state -> tin_1_len, 2);
	ASSERT_EQ(state -> tin_2_len, 2);
	
	restore_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(two),
		state -> lhs_node_order.at(two),
		depth
	); 
	restore_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(two),
		state -> lhs_node_order.at(two),
		depth
	); 
	
	ASSERT_EQ(state -> tout_1_len, 0);
	ASSERT_EQ(state -> tout_2_len, 0);
	ASSERT_EQ(state -> tin_1_len, 0);
	ASSERT_EQ(state -> tin_2_len, 0);

	delete state;
}

TEST_F(GraphIsomorphismTests, testCheckForPossiblityGraphIsomorphism){
	graph <int, int, graph_type :: UNDIRECTED> G1;
	graph <int, int, graph_type :: UNDIRECTED> G2;
	ASSERT_TRUE(graaf::algorithm::check_for_possibility_of_isomorphism(G1, G2));
	
	vertex_id_t g1_vertex_one_id = G1.add_vertex(1);
	vertex_id_t g1_vertex_two_id = G1.add_vertex(2);
	
	ASSERT_FALSE(graaf::algorithm::check_for_possibility_of_isomorphism(G1, G2));
	
	vertex_id_t g2_vertex_one_id = G2.add_vertex(1);
	vertex_id_t g2_vertex_two_id = G2.add_vertex(2);
	
	ASSERT_TRUE(graaf::algorithm::check_for_possibility_of_isomorphism(G1, G2));
	
	G2.add_edge(g2_vertex_one_id, g2_vertex_two_id, 0);
	ASSERT_FALSE(graaf::algorithm::check_for_possibility_of_isomorphism(G1, G2));
	
	G1.add_edge(g1_vertex_one_id, g1_vertex_two_id, 0);
	ASSERT_TRUE(graaf::algorithm::check_for_possibility_of_isomorphism(G1, G2));
}

TEST_F(GraphIsomorphismTests, testTheFunctionsThatCreateNodeOrderings){
	graph<int, int, graph_type :: UNDIRECTED> G1;
	vertex_id_t one = G1.add_vertex(1);
	vertex_id_t two = G1.add_vertex(2);
	vertex_id_t three = G1.add_vertex(3);
	G1.remove_vertex(three);
	vertex_id_t four = G1.add_vertex(4);
	
	std::unordered_map<vertex_id_t, vertex_id_t> ordering;
	create_node_ordering(ordering, G1);

	std::unordered_map<vertex_id_t, vertex_id_t> reverse_ordering;
	create_reverse_node_ordering(ordering, reverse_ordering);

	for(const auto & pair: ordering){
		ASSERT_TRUE(pair.first == reverse_ordering[ordering[pair.first]]);
	}
}


TEST_F(GraphIsomorphismTests, testGetPredecessorsDirectedGraph){
	graph<int, int, graph_type :: DIRECTED> G1;
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
	
	struct vf2_state * state = init_vf2_state(G1, G1);
	std::unordered_set<vertex_id_t> ids = {two, four, three};
	for(const auto & item : get_predecessors(G1, state -> lhs_node_order, state -> lhs_reverse_node_order, state -> lhs_node_order.at(zero))){
		ASSERT_NE(ids.count(state -> lhs_reverse_node_order.at(item)), 0);	
	}
	
	ids.clear();
	ids.insert(two);
	ids.insert(zero);
	for(const auto & item : get_predecessors(G1, state -> lhs_node_order, state -> lhs_reverse_node_order, state -> lhs_node_order.at(four))){
		ASSERT_NE(ids.count( state -> lhs_reverse_node_order.at(item)), 0);	
	}
	
	ids.clear();
	ids.insert(zero);
	for(const auto & item : get_predecessors(G1, state -> lhs_node_order, state -> lhs_reverse_node_order, state -> lhs_node_order.at(two))){
		ASSERT_NE(ids.count( state -> lhs_reverse_node_order.at(item)), 0);	
	}
	
	
	delete state;
}

TEST_F(GraphIsomorphismTests, testGetSuccessorsDirectedGraph){
	graph<int, int, graph_type :: DIRECTED> G1;
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
	
	
	struct vf2_state * state = init_vf2_state(G1, G1);
	std::unordered_set<vertex_id_t> ids = {one, four, two};
	for(const auto & item : get_successors(G1, state -> lhs_node_order, state -> lhs_reverse_node_order, state -> lhs_node_order.at(zero))){
		ASSERT_NE(ids.count( state -> lhs_reverse_node_order.at(item)), 0);	
	}
	
	ids.clear();
	ids.insert(0);
	for(const auto & item : get_successors(G1, state -> lhs_node_order, state -> lhs_reverse_node_order, state -> lhs_node_order.at(3))){
		ASSERT_NE(ids.count( state -> lhs_reverse_node_order.at(item)), 0);	
	}
	
	ids.clear();
	ids.insert(4);
	ids.insert(0);
	for(const auto & item : get_successors(G1, state -> lhs_node_order, state -> lhs_reverse_node_order, state -> lhs_node_order.at(2))){
		ASSERT_NE(ids.count( state -> lhs_reverse_node_order.at(item)), 0);	
	}
	
	delete state;
}

TEST_F(GraphIsomorphismTests, testGetSuccessorsAndPredecessorsUndirectedGraph){
	graph<int, int, graph_type::UNDIRECTED> G1;
	vertex_id_t one = G1.add_vertex(4);
	vertex_id_t three = G1.add_vertex(6);	
	vertex_id_t two = G1.add_vertex(5);

	G1.add_edge(one, two, 0);
	G1.add_edge(two, three, 0);
	G1.add_edge(three, one, 0);
	
	std::set<vertex_id_t> ids = {two, three};
	std::set<vertex_id_t> ids_2 = {two, one};
	
	struct vf2_state * state = init_vf2_state(G1, G1);
	for(const auto & node : get_successors(G1, state -> lhs_node_order, state -> lhs_reverse_node_order, one))
		ASSERT_NE(ids.count(node), 0);
	
	for(const auto & node : get_predecessors(G1, state -> lhs_node_order, state -> lhs_reverse_node_order, one))
		ASSERT_NE(ids.count(node), 0);
	
	for(const auto & node : get_successors(G1, state -> lhs_node_order, state -> lhs_reverse_node_order, three))
		ASSERT_NE(ids_2.count(node), 0);
	
	for(const auto & node : get_predecessors(G1, state -> lhs_node_order, state -> lhs_reverse_node_order, three))
		ASSERT_NE(ids_2.count(node), 0);
	
	delete state;
	 
}


TEST_F(GraphIsomorphismTests, testRPredWithDirectedAndUndirectedGraph){
	graph<int,int,graph_type::DIRECTED> G1;
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
		
	struct vf2_state * state = init_vf2_state(G1, G1);
	
	size_t depth = 1;
	update_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(one),
		state -> lhs_node_order.at(one),
		depth
	); 
	update_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(one),
		state -> lhs_node_order.at(one),
		depth
	); 
	
	depth += 1;
	update_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(four),
		state -> lhs_node_order.at(four),
		depth
	); 
	update_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(four),
		state -> lhs_node_order.at(four),
		depth
	); 
	
	depth += 1;
	update_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(five),
		state -> lhs_node_order.at(five),
		depth
	); 
	update_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(five),
		state -> lhs_node_order.at(five),
		depth
	); 
	
	ASSERT_EQ(r_pred(G1, G1, state, state -> lhs_node_order.at(two), state -> lhs_node_order.at(two)), true);
	ASSERT_EQ(r_pred(G1, G1, state, state -> lhs_node_order.at(two), state -> lhs_node_order.at(five)), false);
	delete state;
}

TEST_F(GraphIsomorphismTests, testRPredWithDirectedGraph){
	graph<int,int,graph_type::UNDIRECTED> G1;
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
		
	struct vf2_state * state = init_vf2_state(G1, G1);
	
	size_t depth = 1;
	update_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(one),
		state -> lhs_node_order.at(one),
		depth
	); 
	update_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(one),
		state -> lhs_node_order.at(one),
		depth
	); 
	
	depth += 1;
	update_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(four),
		state -> lhs_node_order.at(four),
		depth
	); 
	update_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(four),
		state -> lhs_node_order.at(four),
		depth
	); 
	
	depth += 1;
	update_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(five),
		state -> lhs_node_order.at(five),
		depth
	); 
	update_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(five),
		state -> lhs_node_order.at(five),
		depth
	); 
	
	ASSERT_EQ(r_pred(G1, G1, state, state -> lhs_node_order.at(two), state -> rhs_node_order.at(two)), true);
	ASSERT_EQ(r_pred(G1, G1, state, state -> lhs_node_order.at(two), state -> rhs_node_order.at(five)), false);
	delete state;
}

TEST_F(GraphIsomorphismTests, testRSuccWithDirectedGraph){
	graph<int,int,graph_type::DIRECTED> G1;
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
	
	struct vf2_state * state = init_vf2_state(G1, G1);
	
	size_t depth = 1;
	update_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(zero),
		state -> lhs_node_order.at(zero),
		depth
	); 
	update_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(zero),
		state -> lhs_node_order.at(zero),
		depth
	);
	
	
	depth += 1;
	update_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(two),
		state -> lhs_node_order.at(two),
		depth
	); 
	update_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(two),
		state -> lhs_node_order.at(two),
		depth
	);
	
	ASSERT_EQ(r_succ(G1, G1, state, state -> lhs_node_order.at(two), state -> rhs_node_order.at(two)), true);
	ASSERT_EQ(r_succ(G1, G1, state, state -> lhs_node_order.at(two), state -> rhs_node_order.at(one)), false);
	delete state;
	
}

TEST_F(GraphIsomorphismTests, testRSuccWithUndirectedGraph){
	graph<int,int,graph_type::UNDIRECTED> G1;
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
	
	struct vf2_state * state = init_vf2_state(G1, G1);
	
	size_t depth = 1;
	update_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(zero),
		state -> lhs_node_order.at(zero),
		depth
	); 
	update_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(zero),
		state -> lhs_node_order.at(zero),
		depth
	);
	
	
	depth += 1;
	update_mappings(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(two),
		state -> lhs_node_order.at(two),
		depth
	); 
	update_terminal_sets(
		G1, 
		G1, 
		state, 
		state -> lhs_node_order.at(two),
		state -> lhs_node_order.at(two),
		depth
	);
	
	ASSERT_EQ(r_succ(G1, G1, state, state -> lhs_node_order.at(two), state -> rhs_node_order.at(two)), true);
	ASSERT_EQ(r_succ(G1, G1, state, state -> lhs_node_order.at(two), state -> rhs_node_order.at(one)), false);
	delete state;
		
}

TEST_F(GraphIsomorphismTests, testRoutWithDirectedGraph){
	graph<std::string,std::string,graph_type::DIRECTED> G1;
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
	G1.add_edge(seven, zero, "" );
	G1.add_edge(five, two, "");
	G1.add_edge(seven, six, "" );
	
	struct vf2_state * state = init_vf2_state(G1, G1);
	size_t depth = 1;
	update_mappings(G1, G1, state, state -> lhs_node_order.at(seven), state -> rhs_node_order.at(seven), depth);
	update_terminal_sets(G1, G1, state, state -> lhs_node_order.at(seven), state -> rhs_node_order.at(seven), depth);
	depth += 1;
	update_mappings(G1, G1, state, state -> lhs_node_order.at(five), state -> rhs_node_order.at(five), depth);
	update_terminal_sets(G1, G1, state, state -> lhs_node_order.at(five), state -> rhs_node_order.at(five), depth);
	
	ASSERT_EQ(r_out(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(one)), true);
	delete state;
	
}

TEST_F(GraphIsomorphismTests, testRoutWithUndirectedGraph){
	graph<std::string,std::string,graph_type::UNDIRECTED> G1;
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
	G1.add_edge(seven, zero, "" );
	G1.add_edge(five, two, "");
	G1.add_edge(seven, six, "" );
	
	struct vf2_state * state = init_vf2_state(G1, G1);
	size_t depth = 1;
	update_mappings(G1, G1, state, state -> lhs_node_order.at(seven), state -> rhs_node_order.at(seven), depth);
	update_terminal_sets(G1, G1, state, state -> lhs_node_order.at(seven), state -> rhs_node_order.at(seven), depth);
	depth += 1;
	update_mappings(G1, G1, state, state -> lhs_node_order.at(five), state -> rhs_node_order.at(five), depth);
	update_terminal_sets(G1, G1, state, state -> lhs_node_order.at(five), state -> rhs_node_order.at(five), depth);
	
	ASSERT_EQ(r_out(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(one)), true);
	delete state;
}

TEST_F(GraphIsomorphismTests, testRinWithDirectedGraph){
	graph<int,int,graph_type::DIRECTED> G1;
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
	struct vf2_state * state = init_vf2_state(G1, G1);
	
	size_t depth = 1;
	update_mappings(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(one), depth);
	update_terminal_sets(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(one), depth);
	
	ASSERT_EQ(r_in(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(one)), true);
	
	delete state;
	
	
}

TEST_F(GraphIsomorphismTests, testRinWithUndirectedGraph){
	graph<int,int,graph_type::UNDIRECTED> G1;
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
	struct vf2_state * state = init_vf2_state(G1, G1);
	
	size_t depth = 1;
	update_mappings(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(one), depth);
	update_terminal_sets(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(one), depth);
	
	ASSERT_EQ(r_in(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(one)), true);
	
	delete state;

}

TEST_F(GraphIsomorphismTests, testRnewWithDirectedGraph){
	graph<int,int,graph_type::DIRECTED> G1;
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
		
	struct vf2_state * state = init_vf2_state(G1, G1);
	size_t depth = 1;
	update_mappings(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(one), depth);
	update_terminal_sets(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(one), depth);
	ASSERT_EQ(r_new(G1, G1, state, state -> lhs_node_order.at(seven), state -> rhs_node_order.at(seven)), true);
	ASSERT_EQ(r_new(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(two)), false);
	ASSERT_EQ(r_new(G1, G1, state, state -> lhs_node_order.at(five), state -> rhs_node_order.at(five)), true);
	
	delete state;
	
	
}

TEST_F(GraphIsomorphismTests, testRnewWithUndirectedGraph){
	graph<int,int,graph_type::UNDIRECTED> G1;
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
		
	struct vf2_state * state = init_vf2_state(G1, G1);
	size_t depth = 1;
	update_mappings(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(one), depth);
	update_terminal_sets(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(one), depth);
	ASSERT_EQ(r_new(G1, G1, state, state -> lhs_node_order.at(seven), state -> rhs_node_order.at(seven)), true);
	ASSERT_EQ(r_new(G1, G1, state, state -> lhs_node_order.at(one), state -> rhs_node_order.at(two)), false);
	ASSERT_EQ(r_new(G1, G1, state, state -> lhs_node_order.at(five), state -> rhs_node_order.at(five)), true);
	
	delete state;
}


TEST_F(GraphIsomorphismTests, randomlyGeneratingDirectedIsomorphicGraphsAndRunningItThroughVF2){
	graph<int,int, graph_type::DIRECTED> G1;
	graph<int,int, graph_type::DIRECTED> G2;
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution_1(1, 100);
	std::uniform_int_distribution<int> distribution_2(1, 8);
	
	/*
	size_t levels = distribution_2(gen);
	for(size_t i; i < levels; i++){
			
	
	}
	*/
	
	
	
}

TEST_F(GraphIsomorphismTests, testToSeeIfIsomorphicDisconnectedGraphsAreLabeledAsIsomorphic){
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
	std::cout << "G1" << std::endl;
	std::cout << "one " << one << " the value: " << G1.get_vertex(one) << std::endl; 
	std::cout << "two " << two << " the value: " << G1.get_vertex(two) << std::endl; 
	std::cout << std::endl;
	std::cout << "G2" << std::endl;
	std::cout << "three_2 " << three_2 << " the value: " << G2.get_vertex(three_2) << std::endl; 
	std::cout << "five_2 " << five_2 << " the value: " << G2.get_vertex(five_2) << std::endl; 
	
	

	std::optional<Mapping> _optional = check_isomorphism(G1, G2);
	ASSERT_NE(_optional, std::nullopt);
	// FOR DEBUGGING
	for(const auto & key_val: _optional.value()){
		std::cout << G1.get_vertex(key_val.first) <<  " : " << G2.get_vertex(key_val.second) << std::endl;
	}
}
TEST_F(GraphIsomorphismTests, isIsomorphic){
	graph<int, int, graph_type::DIRECTED> G1;
	graph<int, int, graph_type::DIRECTED> G2;
	
	vertex_id_t one = G1.add_vertex(1);
	vertex_id_t two = G1.add_vertex(2);	
	vertex_id_t three = G1.add_vertex(3);
	vertex_id_t four = G1.add_vertex(4);
	vertex_id_t five = G1.add_vertex(5);
	
	G1.add_edge(four, three , -1);	
	G1.add_edge(five, three , -1);
	G1.add_edge(three, one , -1);		
	G1.add_edge(three, two , -1);	
	
	vertex_id_t one_2 = G2.add_vertex(1);
	vertex_id_t two_2 = G2.add_vertex(2);	
	vertex_id_t three_2 = G2.add_vertex(3);
	vertex_id_t four_2 = G2.add_vertex(4);
	vertex_id_t five_2 = G2.add_vertex(5);
	
	G2.add_edge(four_2, three_2 , -1);	
	G2.add_edge(five_2, three_2 , -1);
	G2.add_edge(three_2, one_2 , -1);		
	G2.add_edge(three_2, two_2 , -1);
	
	std::optional<std::unordered_map<vertex_id_t, vertex_id_t>> _optional = check_isomorphism(G1, G2);
	ASSERT_NE(_optional, std::nullopt);
	
	for(const auto & pair : _optional.value()){
		std::cout << "id: " << pair.first << " value: " << G1.get_vertex(pair.first)
		<< "-> id: " << pair.second << " value: " << G2.get_vertex(pair.second) << std::endl;
	}
}

TEST_F(GraphIsomorphismTests, isIsomorphicGraphThree){
	graph<std::string, int, graph_type::UNDIRECTED> G1;
	graph<std::string, int, graph_type::UNDIRECTED> G2;
	
	vertex_id_t one = G1.add_vertex("1a");
	vertex_id_t two = G1.add_vertex("2a");	
	vertex_id_t three = G1.add_vertex("3a");
	vertex_id_t four = G1.add_vertex("4a");
	vertex_id_t five = G1.add_vertex("5a");
	
	G1.add_edge(four, three , -1);	
	G1.add_edge(five, three , -1);
	G1.add_edge(three, one , -1);		
	G1.add_edge(three, two , -1);	
	
	vertex_id_t one_2 = G2.add_vertex("6b");
	vertex_id_t two_2 = G2.add_vertex("7b");	
	vertex_id_t three_2 = G2.add_vertex("8b");
	vertex_id_t four_2 = G2.add_vertex("9b");
	vertex_id_t five_2 = G2.add_vertex("10b");
	
	G2.add_edge(four_2, three_2 , -1);	
	G2.add_edge(five_2, three_2 , -1);
	G2.add_edge(three_2, one_2 , -1);		
	G2.add_edge(three_2, two_2 , -1);
	
	std::optional<std::unordered_map<vertex_id_t, vertex_id_t>> _optional = check_isomorphism(G1, G2);
	ASSERT_NE(_optional, std::nullopt);
	
	for(const auto & pair : _optional.value()){
		std::cout << "id: " << pair.first << " value: " << G1.get_vertex(pair.first)
		<< "-> id: " << pair.second << " value: " << G2.get_vertex(pair.second) << std::endl;
	}
}

TEST_F(GraphIsomorphismTests, isIsomorphicGraphFour){
	graph<int, int, graph_type::DIRECTED> G1;
	graph<int, int, graph_type::DIRECTED> G2;
	vertex_id_t one = G1.add_vertex(1);
	vertex_id_t two = G1.add_vertex(2);
	vertex_id_t three = G1.add_vertex(3);
	vertex_id_t four = G1.add_vertex(4);
	vertex_id_t five = G1.add_vertex(5);
	vertex_id_t six = G1.add_vertex(6);
	vertex_id_t seven = G1.add_vertex(7);
	
	G1.add_edge(one, two ,-1);
	G1.add_edge(one, three, -1);
	G1.add_edge(four, two, -1);
	G1.add_edge(four, three, -1);
	G1.add_edge(four, one , -1);
	G1.add_edge(four, five , -1);
	G1.add_edge(four, seven , -1);
	
	vertex_id_t one_2 = G2.add_vertex(1);
	vertex_id_t two_2 = G2.add_vertex(2);
	vertex_id_t three_2 = G2.add_vertex(3);
	vertex_id_t four_2 = G2.add_vertex(4);
	vertex_id_t five_2 = G2.add_vertex(5);
	vertex_id_t six_2 = G2.add_vertex(6);
	vertex_id_t seven_2 = G2.add_vertex(7);
	
	G2.add_edge(one_2, two_2 ,-1);
	G2.add_edge(one_2, three_2, -1);
	G2.add_edge(four_2, two_2, -1);
	G2.add_edge(four_2, three_2, -1);
	G2.add_edge(four_2, one_2 , -1);
	G2.add_edge(four_2, five_2, -1);
	G2.add_edge(four_2, seven_2 , -1);
	
	std::optional<std::unordered_map<vertex_id_t, vertex_id_t>> _optional = check_isomorphism(G1, G2);
	ASSERT_NE(_optional, std::nullopt);
	
	for(const auto & pair : _optional.value()){
		std::cout << "id: " << pair.first << " value: " << G1.get_vertex(pair.first)
		<< "-> id: " << pair.second << " value: " << G2.get_vertex(pair.second) << std::endl;
	}
}

} // namespace graaf::algorithm
