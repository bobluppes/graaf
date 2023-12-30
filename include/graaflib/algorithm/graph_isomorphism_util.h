#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <cstddef>
#include <memory>
#include <optional>

// Delete later
#include <iostream>


/*Left off here: 
- work on feasability rules class, then the new vf2_state.
- vf2_state will contain info on vf2_target_sets and vf2_mapping, these can generate target, core, and pred and succ sets for feasibilty to use
- additionally we need a candiate_pair function this will also take in vf2_state
- for testing I will start by testing the isomorphism tests, then debug further
*/
/**
HELPER CLASSES
*/

namespace graaf::algorithm::vf2{

struct predecessors_and_successors_of_vertex {
	std::unordered_set<vertex_id_t> predecessors;
	std::unordered_set<vertex_id_t> successors;
};

using vertex_mapping = std::unordered_map<vertex_id_t, vertex_id_t>;

enum class WhichGraph {
	GRAPH_1,
	GRAPH_2
};

template <typename V, typename E, graph_type T>
class vf2_isomorphism_feasibility_checker;


// maps vertices in a graph to a value between [0,N] where N = number of vertices in a graph
template <typename V, typename E, graph_type T>
class vf2_vertex_id_mapper {
		public:
			vf2_vertex_id_mapper(const graph<V, E, T>& _graph1, const graph<V, E, T>& _graph2);
			std::unordered_set<vertex_id_t> get_predecessors(vertex_id_t, WhichGraph);
			std::unordered_set<vertex_id_t> get_successors(vertex_id_t, WhichGraph);

		private:
			void create_mapping(vertex_mapping&, const graph<V, E, T>& graph);
			void create_reverse_mapping(vertex_mapping& map, vertex_mapping& reverse_map);
						
			const graph<V, E, T>* graph1;
			const graph<V, E, T>* graph2; 
			
			vertex_mapping graph1_mapping;
			vertex_mapping graph1_reverse_mapping;
			vertex_mapping graph2_mapping;
			vertex_mapping graph2_reverse_mapping;
			
};

using target_in = std::vector<int>; // index corresponds to a node in the graph
using target_out = std::vector<int>; // index corresponds to a node in the graph
using target = std::vector<int>;
using graph1_to_graph2_mapping = std::vector<vertex_id_t>;
using graph2_to_graph1_mapping = std::vector<vertex_id_t>;

class vf2_target_sets{
	public:
	 	vf2_target_sets(size_t, size_t);
	 	void update_mappings(vertex_id_t, vertex_id_t, int);
	 	void restore_mappings(vertex_id_t, vertex_id_t, int);
		void update_target_sets(const predecessors_and_successors_of_vertex&, const predecessors_and_successors_of_vertex&, int);
		void restore_target_sets(int);
		std::vector<std::pair<vertex_id_t, vertex_id_t>> generate_potential_vertex_pairings();
		size_t get_tin_1_length();
		size_t get_tin_2_length();
		size_t get_tout_1_length();
		size_t get_tout_2_length();
		size_t get_core_1_length();
		size_t get_core_2_length();
		size_t read_tin_1(size_t);
		size_t read_tin_2(size_t);
		size_t read_tout_1(size_t);
		size_t read_tout_2(size_t);
		
		template <typename V, typename E, graph_type T>
		friend class vf2_isomorphism_feasibility_checker;

	private:
		void update_target_set(const std::unordered_set<vertex_id_t>&, target&, int, size_t&);
		void restore_target_set(target&, int, size_t&);
		
		target_in tin_1;
		target_in tin_2;
		target_out tout_1;
		target_out tout_2;
		graph1_to_graph2_mapping core_1;
		graph2_to_graph1_mapping core_2;
		
		size_t tin_1_length = 0;
		size_t tin_2_length = 0; 
		size_t tout_1_length = 0;
		size_t tout_2_length = 0;
		size_t core_1_length = 0;
		size_t core_2_length = 0;
};

// Utility Functions
std::unordered_set<vertex_id_t> intersection_set(const std::unordered_set<vertex_id_t>& set_A, const std::unordered_set<vertex_id_t>& set_B) {
  std::unordered_set<vertex_id_t> intersection;
  for (const auto& element : set_A) {
    if (set_B.count(element) > 0) intersection.insert(element);
  }
  return std::move(intersection);
}

template <typename V, typename E, graph_type T> 
struct vf2_information{
		std::unique_ptr<vf2_target_sets> sets;
		std::unique_ptr<vf2_vertex_id_mapper<V, E, T>> mapper;
		
		vf2_information(const graph<V, E, T>& graph1, const graph<V, E, T>& graph2){
			sets = std::make_unique<vf2_target_sets>(graph1.vertex_count(), graph2.vertex_count());
			mapper = std::make_unique<vf2_vertex_id_mapper<V,E,T>>(graph1, graph2);
		}	
};

template <typename V, typename E, graph_type T> 
class vf2_isomorphism_feasibility_checker {
	public:
		bool checkFeasibility(const std::unique_ptr<vf2_information<V,E,T>>&, const std::pair<vertex_id_t, vertex_id_t>&) const ;
		
	private:
		bool predecessors_consistency_rule(
			const std::unique_ptr<vf2_information<V,E,T>>&,
			const struct predecessors_and_successors_of_vertex&,
			const struct predecessors_and_successors_of_vertex&
		) const;
    	bool successors_consistency_rule(
    		const std::unique_ptr<vf2_information<V,E,T>>&,
			const struct predecessors_and_successors_of_vertex&,
			const struct predecessors_and_successors_of_vertex&
		) const;
		bool lookahead_tin_rule(
			const std::unique_ptr<vf2_information<V,E,T>>&,
			const struct predecessors_and_successors_of_vertex&,
			const struct predecessors_and_successors_of_vertex&
		) const;
		bool lookahead_tout_rule(
			const std::unique_ptr<vf2_information<V,E,T>>&,
			const struct predecessors_and_successors_of_vertex&,
			const struct predecessors_and_successors_of_vertex&
		) const;
		bool lookahead_new_rule(
			const std::unique_ptr<vf2_information<V,E,T>>&,
			const struct predecessors_and_successors_of_vertex&,
			const struct predecessors_and_successors_of_vertex&
		) const;
};

template <typename V, typename E, graph_type T>
bool check_isomorphism(const graph<V, E, T>& graph1, const graph<V, E, T>& graph2, const std::unique_ptr<vf2_information<V,E,T>>& state, const vf2_isomorphism_feasibility_checker<V,E,T>&, size_t depth); 
}//namespace graaf::algorithm::vf2


#include "graph_isomorphism_util.tpp"


