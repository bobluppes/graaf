#pragma once

namespace graaf::algorithm {
// Type aliases
using Mapping = std::unordered_map<vertex_id_t, vertex_id_t>;
using Candidate_pairs = std::vector<std::pair<vertex_id_t, vertex_id_t>>;
using Core_set = std::vector<int>;
using Terminal_set = std::vector<int>;

using vertex_mapping = std::unordered_map<vertex_id_t, vertex_id_t>; //used to map vertex id's to value analogous to vector indices
using candidate_pairs = std::vector<std::pair<vertex_id_t, vertex_id_t>>; //used to hold possible vertex pairs for final mapping
using core_set = std::vector<int>; //used to map a vertex's id in graph LHS to a vertex's id in graph RHS
using terminal_set = std::vector<int>; //used to hold information on each graph's terminal sets (tout and tin)
using node_set = std::unordered_set<vertex_id_t>;

struct vf2_state {
	terminal_set tin_1;
	terminal_set tout_1;
	terminal_set tin_2;
	terminal_set tout_2;
	vertex_mapping lhs_node_order;  
	vertex_mapping rhs_node_order;  
	vertex_mapping lhs_reverse_node_order;  
	vertex_mapping rhs_reverse_node_order;  
	core_set lhs_core;
	core_set rhs_core;
	size_t lhs_core_len = 0;
	size_t rhs_core_len = 0;
	size_t tin_1_len = 0;
	size_t tout_1_len = 0;
	size_t tin_2_len = 0;
	size_t tout_2_len = 0;
};

template <typename V, typename E, graph_type T>
std::unordered_set<vertex_id_t> get_predecessors(const graph <V, E, T>&, const vertex_mapping&, const vertex_mapping&, vertex_id_t);

template <typename V, typename E, graph_type T>
std::unordered_set<vertex_id_t> get_successors(const graph <V, E, T>&, const vertex_mapping&, const vertex_mapping&, vertex_id_t);

template <typename V, typename E, graph_type T>
bool check_for_possibility_of_isomorphism( const graph <V, E, T> &, const graph <V, E, T> & );

template <typename V, typename E, graph_type T>
vf2_state * init_vf2_state(const graph <V, E, T>& lhs, const graph <V, E, T>& rhs);

template <typename V, typename E, graph_type T>
bool check_isomorphism_helper(const graph <V, E, T>&, const graph <V, E, T>&, struct vf2_state *, size_t);

void update_terminal_set(const node_set& vertices, terminal_set& _terminal_set, size_t depth, size_t& _terminal_set_length);

template <typename V, typename E, graph_type T>
void update_terminal_sets(const graph <V, E, T>&, const graph <V, E, T>&, struct vf2_state *, vertex_id_t, vertex_id_t, size_t depth);

void restore_terminal_set(terminal_set& _terminal_set, size_t depth, size_t& _terminal_set_length);

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
void update_mappings(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs,
	size_t depth
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

template <typename V, typename E, graph_type T>
bool feasibility_rules(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);


template <typename V, typename E, graph_type T>
candidate_pairs generate_candidate_pairs(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs,
	const struct vf2_state& state
);

template <typename V, typename E, graph_type T>
bool r_pred(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs,
	struct vf2_state* state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);


template <typename V, typename E, graph_type T>
bool r_succ(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs,
	struct vf2_state* state,
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
bool r_in(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs,
	struct vf2_state* state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);

template <typename V, typename E, graph_type T>
bool r_new(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs,
	struct vf2_state* state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);

node_set set_intersection(
	const node_set& set_A, 
	const node_set& set_B
);

//Node to to id
template <typename V, typename E, graph_type T>
void create_node_ordering(
	vertex_mapping& map,
	const graph <V, E, T>& _graph
) {	
	vertex_id_t id_supplier = 0;
	for(const auto & [id, vertex] : _graph.get_vertices()){
		map[id] = id_supplier;
		id_supplier++;
	}

}

//Id to node
void create_reverse_node_ordering(
	vertex_mapping & map,
	vertex_mapping & reverse_map
) {
	for(const auto & [key, value] : map){
		reverse_map[value] = key;
	}
}

template <typename V, typename E, graph_type T>
std::optional<vertex_mapping>
check_isomorphism(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs
){
	if(!check_for_possibility_of_isomorphism(lhs, rhs))
		return std::nullopt;
		
	struct vf2_state * state = init_vf2_state(lhs, rhs);	
	bool valid_mapping_found = check_isomorphism_helper(lhs, rhs, state, 0);
	
	if(valid_mapping_found){
		vertex_mapping mapping;
		for(int i = 0; i < state->lhs_core.size(); i++)
			mapping[state->lhs_reverse_node_order.at(i)] = state->rhs_reverse_node_order.at(state->lhs_core[i]);
		
		delete state;
		std::optional<vertex_mapping> _optional = mapping;
		return _optional;	
	} else {
		delete state;
		return std::nullopt;
	}
}

template <typename V, typename E, graph_type T>
bool check_isomorphism_helper(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs,
	struct vf2_state * state,
	size_t depth
){
	if(state->lhs_core_len == state->lhs_node_order.size())
		return true;
		
	candidate_pairs candid_pairs = generate_candidate_pairs(lhs, rhs , *state);
	for(const auto & [node_from_lhs, node_from_rhs] : candid_pairs){	
		if(feasibility_rules(lhs, rhs, state, node_from_lhs, node_from_rhs)){				
			update_mappings(lhs, rhs, state, node_from_lhs, node_from_rhs, depth);
			update_terminal_sets(lhs, rhs, state, node_from_lhs, node_from_rhs, depth);
			
			if(check_isomorphism_helper(lhs, rhs, state, depth + 1) == true)
				return true;
		
			restore_terminal_sets(lhs, rhs, state, node_from_lhs, node_from_rhs ,depth);
			restore_mappings(lhs, rhs, state, node_from_lhs, node_from_rhs, depth);	
		}
	}
	return false;
}

void update_terminal_set(
	const node_set& vertices,
	terminal_set& _terminal_set,
	size_t depth,
	size_t& _terminal_set_length
){
	for(const auto& node : vertices){
		if(_terminal_set[node] == -1){
			_terminal_set[node] = int(depth);
			_terminal_set_length++;
		}
	}	
}

template <typename V, typename E, graph_type T>
void update_terminal_sets(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs,
	struct vf2_state* state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs,
	size_t depth
){
	node_set node_lhs_predecessors = get_predecessors(lhs, state->lhs_node_order, state->lhs_reverse_node_order, node_lhs);
	node_set node_rhs_predecessors = get_predecessors(rhs, state->rhs_node_order, state->rhs_reverse_node_order, node_rhs);
	node_set node_lhs_successors = get_successors(lhs, state->lhs_node_order, state->lhs_reverse_node_order, node_lhs);
	node_set node_rhs_successors = get_successors(rhs, state->rhs_node_order, state->rhs_reverse_node_order, node_rhs);
	// UPDATING TOUT_1 
	update_terminal_set(node_lhs_successors, state->tout_1, depth, state->tout_1_len);
	
	// UPDATING TOUT_2
	update_terminal_set(node_rhs_successors, state->tout_2, depth, state->tout_2_len);
	
	// UPDATING TIN_1
	update_terminal_set(node_lhs_predecessors, state->tin_1, depth, state->tin_1_len);
	
	// UPDATING TIN_2
	update_terminal_set(node_rhs_predecessors, state->tin_2, depth, state->tin_2_len);
	
}

template <typename V, typename E, graph_type T>
void update_mappings(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_from_lhs,
	vertex_id_t node_from_rhs,
	size_t depth
){
	// tout_1
	if(state -> tout_1[node_from_lhs] != -1) 
		state -> tout_1_len--;
	else
		state -> tout_1[node_from_lhs] = int(depth);
		
	// tout_2
	if(state -> tout_2[node_from_rhs] != -1)
		state -> tout_2_len--;
	else
		state -> tout_2[node_from_rhs] = int(depth);
		
	// tin_1
	if(state -> tin_1[node_from_lhs] != -1)
		state -> tin_1_len--;
	else
		state -> tin_1[node_from_lhs] = int(depth);
	
	// tin_2
	if(state -> tin_2[node_from_rhs] != -1)
		state -> tin_2_len--;
	else
		state -> tin_2[node_from_rhs] = int(depth);
	
	state -> lhs_core[node_from_lhs] = node_from_rhs;
	state -> rhs_core[node_from_rhs] = node_from_lhs;
	state -> lhs_core_len++;
	state -> rhs_core_len++;
	
}

template <typename V, typename E, graph_type T>
void restore_mappings(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_from_lhs,
	vertex_id_t node_from_rhs,
	size_t depth
){

	// tout_1
	if (state -> tout_1[node_from_lhs] != depth)
		state -> tout_1_len++;
	else
		state -> tout_1[node_from_lhs] = -1;
	
	//tin_1
	if (state -> tin_1[node_from_lhs] != depth)
		state -> tin_1_len++;
	else
		state -> tin_1[node_from_lhs] = -1;
		
	// tout_2
	if (state -> tout_2[node_from_rhs] != depth)
		state -> tout_2_len++;
	else
		state -> tout_2[node_from_rhs] = -1;
	
	//tin_2
	if (state -> tin_2[node_from_rhs] != depth)
		state -> tin_2_len++;
	else
		state -> tin_2[node_from_rhs] = -1;
		
	state -> lhs_core[node_from_lhs] = -1;
	state -> rhs_core[node_from_rhs] = -1;
	state -> lhs_core_len--;
	state -> rhs_core_len--;
	
}

void restore_terminal_set(
	terminal_set& _terminal_set,
	size_t depth,
	size_t& _terminal_set_length
){
	for(int i = 0; i < _terminal_set.size();i++){
		if(_terminal_set[i] == depth){
			_terminal_set[i] = -1;
			_terminal_set_length--;
		}
	}
}

template <typename V, typename E, graph_type T>
void restore_terminal_sets(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs,
	struct vf2_state* state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs,
	int depth
){	
	// RESTORING TOUT_1
	restore_terminal_set(state->tout_1, depth, state->tout_1_len);
	// RESTORING TOUT_2
	restore_terminal_set(state->tout_2, depth, state->tout_2_len);
	// RESTORING TIN_1
	restore_terminal_set(state->tin_1, depth, state->tin_1_len);
	// RESTORING TIN_2
	restore_terminal_set(state->tin_2, depth, state->tin_2_len);
}



template <typename V, typename E, graph_type T>
bool feasibility_rules(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
){
	return r_pred(lhs, rhs, state, node_lhs, node_rhs)
	&& r_succ(lhs, rhs, state, node_lhs, node_rhs)
	&& r_in(lhs, rhs, state, node_lhs, node_rhs)
	&& r_out(lhs, rhs, state, node_lhs, node_rhs)
	&& r_new(lhs, rhs, state, node_lhs, node_rhs);
	// TODO ADD A SEMANTIC CHECK	
}

template <typename V, typename E, graph_type T>
vf2_state* init_vf2_state(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs
){
	struct vf2_state* state = new vf2_state;	
	create_node_ordering(state->lhs_node_order, lhs); 
	create_node_ordering(state->rhs_node_order, rhs); 
	create_reverse_node_ordering(state->lhs_node_order, state->lhs_reverse_node_order);
	create_reverse_node_ordering(state->rhs_node_order, state->rhs_reverse_node_order);

	core_set lhs_core(lhs.get_vertices().size(), -1);
	core_set rhs_core(rhs.get_vertices().size(), -1);
	terminal_set tin_1(lhs.get_vertices().size(), -1);
	terminal_set tout_1(lhs.get_vertices().size(), -1);
	terminal_set tin_2(rhs.get_vertices().size(), -1);
	terminal_set tout_2(rhs.get_vertices().size(), -1);
	
	state->lhs_core = std::move(lhs_core);
	state->rhs_core = std::move(rhs_core);
	state->tin_1 = std::move(tin_1);
	state->tin_2 = std::move(tin_2);
	state->tout_1 = std::move(tout_1);
	state->tout_2 = std::move(tout_2);
	return state;
}



template <typename V, typename E, graph_type T>
candidate_pairs generate_candidate_pairs(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs,
	const struct vf2_state& state
){
	candidate_pairs pairs;
	//generate pairs based on tout
	if(!(state.tout_1_len == 0 || state.tout_2_len == 0)){
		for(int i = 0; i < state.tout_1.size(); i++){
			// in tout and core then continue, because if it is in core then we consider it not in tout
			if(state.tout_1[i] == -1)
				continue;
			if(state.lhs_core[i] != -1)
				continue;
			for(int j = 0; j < state.tout_2.size(); j++){
				if(state.tout_2[j] == -1)
					continue;
				if(state.rhs_core[j] != -1)
					continue;
				pairs.push_back(std::make_pair(i,j));
			}	
		}
		return pairs;
	}
	
	//generate pairs based on tin	
	if(!(state.tin_1_len == 0 || state.tin_2_len == 0)){
		for(int i = 0; i < state.tout_1.size(); i++){
			if(state.tin_1[i] == -1)
				continue;
			if(state.tin_1[i] != -1 && state.lhs_core[i] != -1)
				continue;
			for(int j = 0; j < state.tout_2.size(); j++){
				if(state.tin_2[j] == -1)
					continue;
				if(state.tin_2[j] != -1 && state.rhs_core[j] != -1)
					continue;
				pairs.push_back(std::make_pair(i,j));
			}	
		}
		return pairs;
	}	
	// generate pairs from P_D -> all the nodes not in G1(s) or G2(s)
	for(int i = 0; i < state.lhs_core.size(); i++){
		if(state.lhs_core[i] != -1)
			continue;
		for(int j = 0; j < state.rhs_core.size(); j++){
			if(state.rhs_core[j] != -1)
				continue;
			pairs.push_back(std::make_pair(i,j));
		}
	}
	return pairs;
}

// node will be an id in the node ordering
template <typename V, typename E, graph_type T>
std::unordered_set<vertex_id_t> get_successors(
	const graph <V, E, T> & _graph,
	const vertex_mapping & mapping,
	const vertex_mapping & reverse_mapping,
	vertex_id_t node
){
	node_set successors;
	vertex_id_t original_node_id = reverse_mapping.at(node);
	node_set neighbors = _graph.get_neighbors(original_node_id);
	for(const vertex_id_t & vertex: neighbors)
		successors.insert(mapping.at(vertex));
				
	return std::move(successors);
}


template <typename V, typename E, graph_type T>
std::unordered_set<vertex_id_t> get_predecessors(
	const graph <V, E, T> & _graph,
	const vertex_mapping & mapping,
	const vertex_mapping & reverse_mapping,
	vertex_id_t node
){	
	node_set predecessors; 
	vertex_id_t original_graph_id = reverse_mapping.at(node);
	for(const auto & pair : _graph.get_vertices()){	
		if(pair.first != original_graph_id && _graph.has_edge(pair.first, original_graph_id)){
			predecessors.insert(mapping.at(pair.first));
		}
	}
	return std::move(predecessors);
}


template <typename V, typename E, graph_type T>
bool r_pred(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
){
	node_set lhs_pred_set = get_predecessors(lhs, state->lhs_node_order, state->lhs_reverse_node_order, node_lhs);		
	node_set rhs_pred_set = get_predecessors(rhs, state->rhs_node_order, state->rhs_reverse_node_order, node_rhs);	
	node_set lhs_pred_common_set;
	node_set rhs_pred_common_set;
	
	for(const auto & item : lhs_pred_set){
		if(state -> lhs_core[item] != -1) {
			lhs_pred_common_set.insert(item); // the n' primes
		}
	}
	
	for(const auto & item : rhs_pred_set){
		if(state -> rhs_core[item] != -1) {
			rhs_pred_common_set.insert(item); // the m' primes
		}
	}
	
	
	// first part of R_pred condition before the ^, refer to the paper to remind myself
	for(const auto & item : lhs_pred_common_set){
		if( !(state -> lhs_core[item] != -1 &&  rhs_pred_set.count(state -> lhs_core[item]) > 0)){
			return false;
		}
	}
	
	// second part of R_pred condition after the ^, refer to the paper to remind myself
	for(const auto & item : rhs_pred_common_set){
		// check if the m is mapped to an n and then if the m is mapped to an n in predeccsors of G1(lhs)
		if( !(state -> rhs_core[item] != -1 &&  lhs_pred_set.count(state -> rhs_core[item]) > 0)){
			return false;
		}
	}
	
	return true;
}

template <typename V, typename E, graph_type T>
bool r_succ(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs,
	struct vf2_state* state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
){
	std::unordered_set<vertex_id_t> lhs_succ_set = get_successors(lhs, state->lhs_node_order, state->lhs_reverse_node_order, node_lhs);
	std::unordered_set<vertex_id_t> rhs_succ_set = get_successors(rhs, state->rhs_node_order, state->rhs_reverse_node_order, node_rhs);
	
	std::unordered_set<vertex_id_t> lhs_succ_common_set;
	std::unordered_set<vertex_id_t> rhs_succ_common_set;
	
	for(const auto & item : lhs_succ_set){
		if(state -> lhs_core[item] != -1) {
			lhs_succ_common_set.insert(item); //the n' primes
		}
	}
	
	for(const auto & item : rhs_succ_set){
		if(state -> rhs_core[item] != -1) {
			rhs_succ_common_set.insert(item); //the m' primes
		}
	}
	
	for(const auto & item : lhs_succ_common_set){
		// item is in the mapping and the node item is mapped to is in the successor set of rhs
		if(!(state -> lhs_core[item] != -1 && rhs_succ_set.count(state -> lhs_core[item]) > 0 ) ){
			return false;
		}
	}
	
	for(const auto & item : rhs_succ_common_set){
		if(!(state -> rhs_core[item] != -1 && lhs_succ_set.count(state -> rhs_core[item]) > 0 ) ){
			return false;
		}
	}
	
	return true;
}

template <typename V, typename E, graph_type T>
bool r_in(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs,
	struct vf2_state* state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
){
	node_set lhs_pred_set = get_predecessors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	node_set rhs_pred_set = get_predecessors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);
	node_set lhs_succ_set = get_successors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	node_set rhs_succ_set = get_successors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);
	
	size_t tin_1_lhs_pred_common_len = 0;
	size_t tin_2_rhs_pred_common_len = 0;
	size_t tin_1_lhs_succ_common_len = 0;
	size_t tin_2_rhs_succ_common_len = 0;

	for(const auto & item : lhs_pred_set){
		if(state -> tin_1[item] != -1 && state -> lhs_core[item] == -1){
			tin_1_lhs_pred_common_len++;
		}
	}
	
	for(const auto & item : rhs_pred_set){
		if(state -> tin_2[item] != -1 && state -> rhs_core[item] == -1){
			tin_2_rhs_pred_common_len++;
		}
	}
	
	if(tin_1_lhs_pred_common_len != tin_2_rhs_pred_common_len){
		return false;
	}
		
	for(const auto & item : lhs_succ_set ){
		if(state -> tin_1[item] != -1 && state -> lhs_core[item] == -1){
			tin_1_lhs_succ_common_len++;	
		}	
	}
	
	for(const auto & item : rhs_succ_set ){
		if(state -> tin_2[item] != -1 && state -> rhs_core[item] == -1){
			tin_2_rhs_succ_common_len++;	
		}	
	}
	
	if(tin_1_lhs_succ_common_len != tin_2_rhs_succ_common_len){
		return false;
	}
		
	return true;
}

template <typename V, typename E, graph_type T>
bool r_out(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs,
	struct vf2_state* state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
){
	node_set lhs_pred_set = get_predecessors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	node_set rhs_pred_set = get_predecessors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);
	node_set lhs_succ_set = get_successors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	node_set rhs_succ_set = get_successors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);
	size_t tout1_lhs_pred_common = 0;
	size_t tout2_rhs_pred_common = 0;
	size_t tout1_lhs_succ_common = 0;
	size_t tout2_rhs_succ_common = 0;
	
	for(const auto & item : lhs_pred_set){
		if(state -> tout_1[item] != -1 && state -> lhs_core[item] == -1){
			tout1_lhs_pred_common++;
		}
	}
	
	for(const auto & item : rhs_pred_set){
		if(state -> tout_2[item] != -1 && state -> rhs_core[item] == -1){
			tout2_rhs_pred_common++;
		}
	}	
	
	if(tout1_lhs_pred_common != tout2_rhs_pred_common){
		return false;
	}
	 	
	for(const auto & item : lhs_succ_set){
		if(state -> tout_1[item] != -1 && state -> lhs_core[item] == -1){
			tout1_lhs_succ_common++;
		}
	}
	
	for(const auto & item : rhs_succ_set){
		if(state -> tout_2[item] != -1 && state -> rhs_core[item] == -1){
			tout2_rhs_succ_common++;
		}
	}
	
	if(tout1_lhs_succ_common != tout2_rhs_succ_common){
		return false;
	}
	
	return true;
}

node_set set_intersection(
	const node_set& set_A, 
	const node_set& set_B
){
	node_set intersection;
	for(const auto & element : set_A){
		if(set_B.count(element) > 0)
			intersection.insert(element);
	}
	return std::move(intersection);
}

template <typename V, typename E, graph_type T>
bool r_new(
	const graph <V, E, T>& lhs,
	const graph <V, E, T>& rhs,
	struct vf2_state* state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
){
	node_set lhs_n_set;
	node_set rhs_n_set;
	
	for(int i = 0; i < state -> lhs_core.size(); i++){
		if(state -> lhs_core[i] == -1 && state -> tin_1[i] == -1 && state -> tout_1[i] == -1){
			lhs_n_set.insert(i); // N prime
		}		
	}
	
	for(int i = 0; i < state -> rhs_core.size(); i++){
		if(state -> rhs_core[i] == -1 && state -> tin_2[i] == -1 && state -> tout_2[i] == -1){
			rhs_n_set.insert(i); // N_2 prime
		}		
	}
	
	node_set lhs_pred = get_predecessors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	node_set rhs_pred = get_predecessors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);
	node_set lhs_succ = get_successors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	node_set rhs_succ = get_successors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);

	// intersection of sets	
	node_set lhs_n_pred_common = set_intersection(lhs_n_set, lhs_pred);
	node_set rhs_n_pred_common = set_intersection(rhs_n_set, rhs_pred);
	node_set lhs_n_succ_common = set_intersection(lhs_n_set, lhs_succ);
	node_set rhs_n_succ_common = set_intersection(rhs_n_set, rhs_succ);
	
	/*
	for(const auto & item : lhs_pred){
		if(lhs_n_set.count(item) > 0){
			lhs_n_pred_common.insert(item);
		}
	}
	
	for(const auto & item : rhs_pred){
		if(rhs_n_set.count(item) > 0){
			rhs_n_pred_common.insert(item);
		}
	}	
	
	for(const auto & item : lhs_succ){
		if(lhs_n_set.count(item) > 0){
			lhs_n_succ_common.insert(item);
		}
	}
	
	for(const auto & item : rhs_succ){
		if(rhs_n_set.count(item) > 0){
			rhs_n_succ_common.insert(item);
		}
	}
	*/
	
	if(lhs_n_pred_common.size() == rhs_n_pred_common.size() && lhs_n_succ_common.size() == rhs_n_succ_common.size()){
		return true;
	}
	return false;
};


template <typename V, typename E, graph_type T>
bool check_for_possibility_of_isomorphism(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs
) {
	if (lhs.vertex_count() != rhs.vertex_count() || lhs.edge_count() != rhs.edge_count()) 
		return false;		
	std::vector<std::size_t> lhs_node_degrees, rhs_node_degrees;
	for (const auto& vertex : lhs.get_vertices()){
		std::size_t number_of_conn = lhs.get_neighbors(vertex.first).size();
		lhs_node_degrees.push_back(number_of_conn);	
	}	
	for (const auto& vertex : rhs.get_vertices()){
		std::size_t number_of_conn = rhs.get_neighbors(vertex.first).size();
		rhs_node_degrees.push_back(number_of_conn);	
	}
	std::sort(lhs_node_degrees.begin(), lhs_node_degrees.end());
	std::sort(rhs_node_degrees.begin(), rhs_node_degrees.end());
	for(int i = 0; i < lhs_node_degrees.size(); i++)
		if (lhs_node_degrees[i] != rhs_node_degrees[i]) 
			return false;
	return true;		
}	

} // namespace graaf :: algorithm

