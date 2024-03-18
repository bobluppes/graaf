#pragma once

#include <graaflib/graph.h>
#include <graaflib/types.h>
#include <cstddef>
#include <memory>
#include <optional>


/**
HELPER CLASSES
*/

namespace graaf::algorithm{

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
			friend class vf2_target_sets;
			
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

/* 
alias for the target sets, which are responsible for narrowing the search space and vertex pairings 
based on existing vertex pairs in the current mapping
*/
using target = std::vector<int>; 
using graph_to_graph_mapping = std::vector<vertex_id_t>; // maps vertices' ids from one graph to another

class vf2_target_sets{
	public:
	 	vf2_target_sets(size_t, size_t);
	 	void update_mappings(vertex_id_t, vertex_id_t, int);
	 	void restore_mappings(vertex_id_t, vertex_id_t, int);
		void update_target_sets(const predecessors_and_successors_of_vertex&, const predecessors_and_successors_of_vertex&, int);
		void restore_target_sets(int);
		std::vector<std::pair<vertex_id_t, vertex_id_t>> generate_potential_vertex_pairings();
		size_t get_core_1_length();
		size_t get_core_2_length();
		
		template <typename V, typename E, graph_type T>
		vertex_mapping generate_final_mapping(const vf2_vertex_id_mapper<V,E,T>&);
		
		template <typename V, typename E, graph_type T>
		friend class vf2_isomorphism_feasibility_checker;
		
	private:		
		target tin_1;
		target tin_2;
		target tout_1;
		target tout_2;
		graph_to_graph_mapping core_1;
		graph_to_graph_mapping core_2;
		
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
    if (set_B.find(element)!= set_B.end()) {
    	intersection.insert(element);
	}
  }
  return intersection;
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
struct rule_parameters{
	const vf2_information<V,E,T>& vf2_info;
	const predecessors_and_successors_of_vertex& pred_succ_vertex1;
	const predecessors_and_successors_of_vertex& pred_succ_vertex2;
	rule_parameters(
		const vf2_information<V,E,T>& _vf2_info,
		const predecessors_and_successors_of_vertex& _pred_succ_vertex1, 
		const predecessors_and_successors_of_vertex& _pred_succ_vertex2
	): pred_succ_vertex1(_pred_succ_vertex1), pred_succ_vertex2(_pred_succ_vertex2), vf2_info(_vf2_info){}
};

template <typename V, typename E, graph_type T> 
class vf2_isomorphism_feasibility_checker {
	public:
		bool checkFeasibility(const std::unique_ptr<vf2_information<V,E,T>>&, const std::pair<vertex_id_t, vertex_id_t>&) const ;
		
	private:
		bool predecessors_consistency_rule(
			const struct rule_parameters<V,E,T>& params
		) const;
    	bool successors_consistency_rule(
    		const struct rule_parameters<V,E,T>& params
		) const;
		bool lookahead_tin_rule(
			const struct rule_parameters<V,E,T>& params
		) const;
		bool lookahead_tout_rule(
			const struct rule_parameters<V,E,T>& params
		) const;
		bool lookahead_new_rule(
			const struct rule_parameters<V,E,T>& params
		) const;
};

template <typename V, typename E, graph_type T>
bool check_isomorphism(const graph<V, E, T>& graph1, const graph<V, E, T>& graph2, const std::unique_ptr<vf2_information<V,E,T>>& state, const vf2_isomorphism_feasibility_checker<V,E,T>&, size_t depth); 
}//namespace graaf::algorithm::vf2


#include "graph_isomorphism_util.tpp"


