#pragma once

#include <algorithm>
#include <graaflib/types.h>
#include <graaflib/graph.h>
#include <vector>
#include <unordered_map>
#include <optional>
#include <unordered_set>
#include <array>

namespace graaf::algorithm {

using Mapping = std::unordered_map<vertex_id_t, vertex_id_t>;
using Candidate_pairs = std::vector<std::pair<vertex_id_t, vertex_id_t>>;
using Core_set = std::vector<int>;
using Terminal_set = std::vector<int>;


struct vf2_state {
	Terminal_set tin_1;
	size_t tin_1_len = 0;
	Terminal_set tout_1;
	size_t tout_1_len = 0;
	Terminal_set tin_2;
	size_t tin_2_len = 0;
	Terminal_set tout_2;
	size_t tout_2_len = 0;
	Mapping lhs_node_order;  
	Mapping rhs_node_order;  
	Mapping lhs_reverse_node_order;  
	Mapping rhs_reverse_node_order;  
	Core_set lhs_core;
	size_t lhs_core_len = 0;
	Core_set rhs_core;
	size_t rhs_core_len = 0;
};	

template <typename V, typename E, graph_type T>
std::optional<Mapping>
check_isomorphism(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs
);

template <typename V, typename E, graph_type T>
bool check_isomorphism_helper(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state & state,
	size_t depth
);

template <typename V, typename E, graph_type T>
vf2_state * init_vf2_state(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs
);


template <typename V, typename E, graph_type T>
std::unordered_set<vertex_id_t> get_successors(
	const graph <V, E, T> & _graph,
	const Mapping & mapping,
	const Mapping & reverse_mapping,
	vertex_id_t node
);

template <typename V, typename E, graph_type T>
std::unordered_set<vertex_id_t> get_predecessors(
	const graph <V, E, T> & _graph,
	const Mapping & mapping,
	const Mapping & reverse_mapping,
	vertex_id_t node
);

template <typename V, typename E, graph_type T>
Candidate_pairs generate_candidate_pairs(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	const struct vf2_state & state
);

template <typename V, typename E, graph_type T>
bool check_for_possibility_of_isomorphism(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs
);

template <typename V, typename E, graph_type T>
void create_node_ordering(
	std::unordered_map<vertex_id_t, vertex_id_t> & map,
	const graph <V, E, T> & _graph
);


void create_reverse_node_ordering(
	std::unordered_map<vertex_id_t, vertex_id_t> & map,
	std::unordered_map<vertex_id_t, vertex_id_t> & reverse_map
);

template <typename V, typename E, graph_type T>
bool feasibility(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);

template <typename V, typename E, graph_type T>
bool r_pred(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);

template <typename V, typename E, graph_type T>
bool r_succ(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);

template <typename V, typename E, graph_type T>
bool r_in(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);

template <typename V, typename E, graph_type T>
bool r_out(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);

template <typename V, typename E, graph_type T>
bool r_new(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);


template <typename V, typename E, graph_type T>
void update_terminal_sets(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state & state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs,
	size_t depth
);

template <typename V, typename E, graph_type T>
void update_mappings(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs,
	size_t depth
);

template <typename V, typename E, graph_type T>
void restore_terminal_sets(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs,
	int depth
);

template <typename V, typename E, graph_type T>
void restore_mappings(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs,
	size_t depth
);

void printMapping(const Mapping & mapping);



} // namespace graaf::algorithm




#include "graph_isomorphism.tpp"



