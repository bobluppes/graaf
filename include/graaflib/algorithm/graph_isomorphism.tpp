namespace graaf::algorithm {

template <typename V, typename E, graph_type T>
std::optional<Mapping>
check_isomorphism(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs
){
	if(!check_for_possibility_of_isomorphism(lhs, rhs))
		return std::nullopt;
		
	struct vf2_state * state = init_vf2_state(lhs, rhs);	
	
	bool valid_mapping_found = check_isomorphism_helper(
			lhs,
			rhs,
			state,
			0
	);
	
	if(valid_mapping_found){
		std::unordered_map<vertex_id_t, vertex_id_t> mapping;
		std::cout << "lhs core" << std::endl;
		int i = 0;
		for(const auto & item : state -> lhs_core){
			std::cout << i << ": " << item << std::endl;
			i++;
		}
		std::cout << "rhs core" << std::endl;
		i = 0;
		for(const auto & item : state -> rhs_core){
			std::cout << i << ": " << item << std::endl;
			i++;
		}
		
		std::cout << "lhs_core_len " << state -> lhs_core_len << std::endl;
		std::cout << "rhs_core_len " << state -> rhs_core_len << std::endl;
		
		for(int i = 0; i < state -> lhs_core.size(); i++){
			//mapping[state -> lhs_reverse_node_order.at(i)] = state -> rhs_reverse_node_order.at(state -> lhs_core[i]);
			//mapping[state -> lhs_reverse_node_order.at(state -> rhs_core[i])] = state -> rhs_reverse_node_order.at(state ->
			//lhs_core[i]);
			mapping[state -> lhs_reverse_node_order.at(i)] = state -> rhs_reverse_node_order.at(state -> lhs_core[i]);
		}
		delete state;
		std::optional<Mapping> _optional = mapping;
		return _optional;	
	} else {
		delete state;
		return std::nullopt;
	}
}


template <typename V, typename E, graph_type T>
bool check_isomorphism_helper(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	size_t depth
){
	
	if(state -> lhs_core_len == state -> lhs_node_order.size()){
		return true;
	}	
	
	Candidate_pairs candid_pairs = generate_candidate_pairs(lhs, rhs , *state);
	
	for (int i = 0 ; i < candid_pairs.size(); i++){
		std::cout << " pair: " << candid_pairs[i].first << " " << candid_pairs[i].second << std::endl;
	}
	
	
	for(int i = 0; i < candid_pairs.size(); i++){	
		std::cout << " pair: " << candid_pairs[i].first << " " << candid_pairs[i].second << std::endl;
		if(feasibility(lhs, rhs, state, candid_pairs[i].first, candid_pairs[i].second)){
			vertex_id_t node_from_lhs = candid_pairs[i].first;
			vertex_id_t node_from_rhs = candid_pairs[i].second;
				
			update_mappings(lhs, rhs, state, node_from_lhs, node_from_rhs, depth);
			update_terminal_sets(lhs, rhs, state, node_from_lhs, node_from_rhs, depth);
				
			if(check_isomorphism_helper(lhs, rhs, state, depth + 1) == true){
				return true;
			}
							
			// the backtracking 
			std::cout << "backtracking" << std::endl;
			restore_terminal_sets(lhs, rhs, state, node_from_lhs, node_from_rhs ,depth);
			restore_mappings(lhs, rhs, state, node_from_lhs, node_from_rhs, depth);
				
		}
	}
	
	return false;
}


template <typename V, typename E, graph_type T>
void update_terminal_sets(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs,
	size_t depth
){

	using node_set = std::unordered_set<vertex_id_t>;
	node_set node_lhs_predecessors = get_predecessors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	node_set node_rhs_predecessors = get_predecessors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);
	node_set node_lhs_successors = get_successors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	node_set node_rhs_successors = get_successors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);
	
	// tout_1
	for(const auto & item : node_lhs_successors) {
		if (state -> tout_1[item] == - 1){
			state -> tout_1[item] = int(depth);
			state -> tout_1_len++;
		}	
	}
	
	//tin_1	
	for(const auto & item: node_lhs_predecessors){
		if (state -> tin_1[item] == -1){
			state -> tin_1[item] = int(depth);
			state -> tin_1_len++;
		}	
	}
		
	// tout_2
	for(const auto & item : node_rhs_successors) {
		if (state -> tout_2[item] == - 1){
			state -> tout_2[item] = int(depth);
			state -> tout_2_len++;
		}	
	}

	//tin_2
	for(const auto & item: node_lhs_predecessors){
		if (state -> tin_2[item] == -1){
			state -> tin_2[item] = int(depth);
			state -> tin_2_len++;
		}	
	}
	
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

template <typename V, typename E, graph_type T>
void restore_terminal_sets(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs,
	int depth
){
	for(int i = 0; i < state -> tin_1.size(); i++){
		if(state -> tin_1[i] == depth){
			state -> tin_1[i] = -1;
			state -> tin_1_len--;
		}
		if(state -> tin_2[i] == depth){
			state -> tin_2[i] = -1;
			state -> tin_2_len--;
		}
		if(state -> tout_1[i] == depth){
			state -> tout_1[i] = -1;
			state -> tout_1_len--;
		}
		
		if(state -> tout_2[i] == depth){
			state -> tout_2[i] = -1;
			state -> tout_2_len--;
		}
	}

}



template <typename V, typename E, graph_type T>
bool feasibility(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
){
	std:: cout << "in feasability checking for " << node_lhs << " which is " << state -> lhs_reverse_node_order.at(node_lhs) << " and " <<
	node_rhs << " which is " << state -> rhs_reverse_node_order.at(node_rhs) << std::endl;
	return r_pred(lhs, rhs, state, node_lhs, node_rhs)
	&& r_succ(lhs, rhs, state, node_lhs, node_rhs)
	&& r_in(lhs, rhs, state, node_lhs, node_rhs)
	&& r_out(lhs, rhs, state, node_lhs, node_rhs)
	&& r_new(lhs, rhs, state, node_lhs, node_rhs);
	
	// need to add the check for semantic feasability to 
	
}




template <typename V, typename E, graph_type T>
vf2_state * init_vf2_state(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs
){
	struct vf2_state * state = new vf2_state;	
	create_node_ordering(state -> lhs_node_order, lhs); // will map the vertex id's to another id between 0, ... , [number of vertices in graph] - 1
	create_node_ordering(state -> rhs_node_order, rhs); 
	create_reverse_node_ordering(state -> lhs_node_order, state -> lhs_reverse_node_order);
	create_reverse_node_ordering(state -> rhs_node_order, state -> rhs_reverse_node_order);
	
	// Mapping sets to represent the final mapping
	Core_set lhs_core(lhs.get_vertices().size(), -1);
	Core_set rhs_core(rhs.get_vertices().size(), -1);
	
	Terminal_set tin_1(lhs.get_vertices().size(), -1);
	Terminal_set tout_1(lhs.get_vertices().size(), -1);
	Terminal_set tin_2(rhs.get_vertices().size(), -1);
	Terminal_set tout_2(rhs.get_vertices().size(), -1);
	
	state -> lhs_core = std::move(lhs_core);
	state -> rhs_core = std::move(rhs_core);
	
	state -> tin_1 = std::move(tin_1);
	state -> tin_2 = std::move(tin_2);
	state -> tout_1 = std::move(tout_1);
	state -> tout_2 = std::move(tout_2);
	return state;
}

//Node to to id
template <typename V, typename E, graph_type T>
void create_node_ordering(
	std::unordered_map<vertex_id_t, vertex_id_t> & map,
	const graph <V, E, T> & _graph
) {
	
	vertex_id_t id_supplier = 0;
	for(const auto & pair : _graph.get_vertices()){
		vertex_id_t vertex_id = pair.first;
		map[vertex_id] = id_supplier;
		id_supplier++;
	}

}

//Id to node
void create_reverse_node_ordering(
	std::unordered_map<vertex_id_t, vertex_id_t> & map,
	std::unordered_map<vertex_id_t, vertex_id_t> & reverse_map
) {
	for(const auto & pair : map){
		reverse_map[pair.second] = pair.first;
	}
}

template <typename V, typename E, graph_type T>
Candidate_pairs generate_candidate_pairs(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	const struct vf2_state & state
){
	// alias for std::vector<std::pair<vertex_id_t, vertex_id_t>>
	Candidate_pairs pairs;
	if(!(state.tout_1_len == 0 || state.tout_2_len == 0)){
		std::cout << "generating pairs from tout" << std::endl;
		//generate pairs based on tout
		for(int i = 0; i < state.tout_1.size(); i++){
			// in tout and core then continue, because if it is in core then we consider it not in tout
			if(state.tout_1[i] == -1)
				continue;
			
			/*
			if(state.tout_1[i] != -1 && state.lhs_core[i] != -1){
			
				std::cout << "continuting" << std::endl;
				std::cout << state.tout_1[i] << " " << state.lhs_core[i] << std::endl;
				continue;
			}
			*/
			if(state.lhs_core[i] != -1){
				std::cout << "continuting" << std::endl;
				std::cout << state.tout_1[i] << " " << state.lhs_core[i] << std::endl;
				continue;
			}
			
			
			for(int j = 0; j < state.tout_2.size(); j++){
				if(state.tout_2[j] == -1)
					continue;
				/*
				if(state.tout_2[j] != -1 && state.rhs_core[j] != -1)
					continue;			
				*/
				if(state.rhs_core[j] != -1)
					continue;
				pairs.push_back(std::make_pair(i,j));
				
			}	
		}
		return pairs;
	}
	
	if(!(state.tin_1_len == 0 || state.tin_2_len == 0)){
			std::cout << "generating pairs from tin" << std::endl;
		//generate pairs based on tin
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
	std::cout << "generating pairs from P_d" << std::endl;
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
	const Mapping & mapping,
	const Mapping & reverse_mapping,
	vertex_id_t node
){
	std::unordered_set<vertex_id_t> successors;
	
	vertex_id_t node_in_graph_id = reverse_mapping.at(node);
	std::unordered_set<vertex_id_t> _set = _graph.get_neighbors(node_in_graph_id);
	for(const vertex_id_t & vertex: _set){
		successors.insert(mapping.at(vertex));
	}
	
	return successors;
}


// NEED TO TEST MORE
// node param is the id of the vertex in the node ordering
template <typename V, typename E, graph_type T>
std::unordered_set<vertex_id_t> get_predecessors(
	const graph <V, E, T> & _graph,
	const Mapping & mapping,
	const Mapping & reverse_mapping,
	vertex_id_t node
){
	
	/*std::cout << std::endl  << "get_predecessors for node_id in the node order:" << node 
	<< " which is: " << reverse_mapping.at(node) << " in the graph" << std::endl;*/
	std::unordered_set<vertex_id_t> predecessors; 
	
	// std::cout << "printing the predecessors" << std::endl;
	vertex_id_t node_in_graph_id = reverse_mapping.at(node);
	for(const auto & pair : _graph.get_vertices()){
		
		if(pair.first != node_in_graph_id && _graph.has_edge(pair.first, node_in_graph_id)){
	//		std::cout << "id: " << pair.first << "value: " << _graph.get_vertex(pair.first) <<",";
			//std::cout << std::endl << "right before point of failure" << std::endl;
			predecessors.insert(mapping.at(pair.first));
			//std::cout << "passed at" << std::endl;
		}
	
	}
	//std::cout << std::endl;
	
	return predecessors;

}

/*

*/
template <typename V, typename E, graph_type T>
bool r_pred(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
){
	//std::cout << "in r_pred" << std::endl;
	std::unordered_set<vertex_id_t> lhs_pred_set = get_predecessors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);		
	std::unordered_set<vertex_id_t> rhs_pred_set = get_predecessors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);	
	std::unordered_set<vertex_id_t> lhs_pred_common_set;
	std::unordered_set<vertex_id_t> rhs_pred_common_set;
	
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
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
){
	std::cout << "in r_succ" << std::endl;
	std::unordered_set<vertex_id_t> lhs_succ_set = get_successors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	std::unordered_set<vertex_id_t> rhs_succ_set = get_successors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);
	
	std::unordered_set<vertex_id_t> lhs_succ_common_set;
	std::unordered_set<vertex_id_t> rhs_succ_common_set;
	
	for(const auto & item : lhs_succ_set){
		if(state -> lhs_core[item] != -1) {
			lhs_succ_common_set.insert(item); // the n' primes
		}
	}
	
	for(const auto & item : rhs_succ_set){
		if(state -> rhs_core[item] != -1) {
			rhs_succ_common_set.insert(item); // the m' primes
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
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
){
	std::cout << "in r_in" << std::endl;
	std::unordered_set<vertex_id_t> lhs_pred_set = get_predecessors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);;
	std::unordered_set<vertex_id_t> rhs_pred_set = get_predecessors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);
	std::unordered_set<vertex_id_t> lhs_succ_set = get_successors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	std::unordered_set<vertex_id_t> rhs_succ_set = get_successors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);
	
	
	size_t tin_1_lhs_pred_common_len = 0;
	size_t tin_2_rhs_pred_common_len = 0;
	
	for(const auto & item : lhs_pred_set){
		std::cout << "item: " << item << " actual id: " << state -> lhs_reverse_node_order.at(item) << " its actual value " << lhs.get_vertex(state -> lhs_reverse_node_order.at(item)) << std::endl;
		std::cout << "state ->tin_1[item]: " <<state -> tin_1[item] << "state -> lhs_core[item]: " << state -> lhs_core[item] << std::endl;
		if(state -> tin_1[item] != -1 && state -> lhs_core[item] == -1){
			tin_1_lhs_pred_common_len++;
		}
	}
	
	for(const auto & item : rhs_pred_set){
		if(state -> tin_2[item] != -1 && state -> rhs_core[item] == -1){
			tin_2_rhs_pred_common_len++;
		}
	}
	
	std ::cout << "tin_1_lhs_pred_common_len: " << tin_1_lhs_pred_common_len << std::endl;
	std ::cout << "tin_2_rhs_pred_common_len: " << tin_2_rhs_pred_common_len << std::endl;
	if( tin_1_lhs_pred_common_len != tin_2_rhs_pred_common_len){
		std::cout << "failing on checking pred intersec " << std::endl;
		return false;
	}
	
	
	// check succs first
	size_t tin_1_lhs_succ_common_len = 0;
	size_t tin_2_rhs_succ_common_len = 0;
	
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
		std::cout << "failing on checking succ intersec " << std::endl;
		return false;
	}
	
	
		
	return true;
}

template <typename V, typename E, graph_type T>
bool r_out(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
){
	std::cout << "in r_out" << std::endl;
	std::unordered_set<vertex_id_t> lhs_pred_set = get_predecessors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	std::unordered_set<vertex_id_t> rhs_pred_set = get_predecessors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);
	std::unordered_set<vertex_id_t> lhs_succ_set = get_successors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	std::unordered_set<vertex_id_t> rhs_succ_set = get_successors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);
	size_t tout1_lhs_pred_common = 0;
	size_t tout2_rhs_pred_common = 0;
	
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
	 
	size_t tout1_lhs_succ_common = 0;
	size_t tout2_rhs_succ_common = 0;
	
	
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


template <typename V, typename E, graph_type T>
bool r_new(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
){
	std::cout << "in r_new" << std::endl;
	std::unordered_set<vertex_id_t> lhs_n_set;
	for(int i = 0; i < state -> lhs_core.size(); i++){
		if(state -> lhs_core[i] == -1 && state -> tin_1[i] == -1 && state -> tout_1[i] == -1){
			lhs_n_set.insert(i); // N prime
		}		
	}
	
	std::unordered_set<vertex_id_t> rhs_n_set;
	for(int i = 0; i < state -> rhs_core.size(); i++){
		if(state -> rhs_core[i] == -1 && state -> tin_2[i] == -1 && state -> tout_2[i] == -1){
			rhs_n_set.insert(i); // N_2 prime
		}		
	}
	
	std::unordered_set<vertex_id_t> lhs_pred = get_predecessors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	std::unordered_set<vertex_id_t> rhs_pred = get_predecessors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);
	std::unordered_set<vertex_id_t> lhs_succ = get_successors(lhs, state -> lhs_node_order, state -> lhs_reverse_node_order, node_lhs);
	std::unordered_set<vertex_id_t> rhs_succ = get_successors(rhs, state -> rhs_node_order, state -> rhs_reverse_node_order, node_rhs);

	// intersection of sets	
	std::unordered_set<vertex_id_t> lhs_n_pred_common;
	std::unordered_set<vertex_id_t> rhs_n_pred_common;
	std::unordered_set<vertex_id_t> lhs_n_succ_common;
	std::unordered_set<vertex_id_t> rhs_n_succ_common;

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
	
	if(lhs_n_pred_common.size() == rhs_n_pred_common.size() && lhs_n_succ_common.size() == rhs_n_succ_common.size()){
		std::cout << "exiting r_new, it passed" << std::endl;
		return true;
	}
	std::cout << "exiting r_new, it failed" << std::endl;
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

// FOR DEBUGGING PURPOSES
void printMapping(
	const Mapping & mapping
){
	std::cout << "format id (value of id) -> id (value of id)" << std::endl;
	for(const auto & key_val : mapping){
		std::cout << key_val.first << " : " << key_val.second << std::endl;
	}
}
} // namespace graaf :: algorithm

