#pragma once

// BIG ERROR WITH THIS IS THAT I CANNOT PASS AROUND THE UNIQUE_PTR BECAUSE THERE ARE INSTANCES WHERE I NEED TO CHANGE DATA
// USE THE GET FUNCTION TO PASS IT AROUND TO SOME FUNCTIONS

namespace graaf::algorithm::vf2{

template <typename V, typename E, graph_type T>
vf2_vertex_id_mapper<V, E, T>::vf2_vertex_id_mapper(const graph<V, E, T>& _graph1, const graph<V, E, T>& _graph2){
	create_mapping(graph1_mapping, _graph1);
	create_mapping(graph2_mapping, _graph2);
	create_reverse_mapping(graph1_mapping, graph1_reverse_mapping);
	create_reverse_mapping(graph2_mapping, graph2_reverse_mapping);
	graph1 = &_graph1;
	graph2 = &_graph2;
	
}

template <typename V, typename E, graph_type T>
void vf2_vertex_id_mapper<V, E, T>::create_mapping(vertex_mapping& map, const graph<V, E, T>& _graph){
  vertex_id_t id_supplier = 0;
  for (const auto& [id, vertex] : _graph.get_vertices()) {
    map[id] = id_supplier;
    id_supplier++;
  }
}

template <typename V, typename E, graph_type T>
void vf2_vertex_id_mapper<V, E, T>::create_reverse_mapping(vertex_mapping& map, vertex_mapping& reverse_map) {
  for (const auto& [key, value] : map) {
    reverse_map[value] = key;
  }
}

template <typename V, typename E, graph_type T>
std::unordered_set<vertex_id_t> vf2_vertex_id_mapper<V, E, T>::get_predecessors(vertex_id_t vertex, WhichGraph graph){
	std::unordered_set<vertex_id_t> predecessors;
	if(graph == WhichGraph::GRAPH_1){
		vertex_id_t original_vertex_id = graph1_reverse_mapping.at(vertex);
		for(const auto& pair: graph1 -> get_vertices()){
			if(pair.first != original_vertex_id && graph1 -> has_edge(pair.first, original_vertex_id)){
				predecessors.insert(graph1_mapping.at(pair.first));
			}
		}
	} else {
		vertex_id_t original_vertex_id = graph2_reverse_mapping.at(vertex);
		for(const auto& pair: graph2 -> get_vertices()){
			if(pair.first != original_vertex_id && graph2 -> has_edge(pair.first, original_vertex_id)){
				predecessors.insert(graph2_mapping.at(pair.first));
			}
		}
	}
	return std::move(predecessors);
}

template <typename V, typename E, graph_type T>
std::unordered_set<vertex_id_t> vf2_vertex_id_mapper<V, E, T>::get_successors(vertex_id_t vertex, WhichGraph graph){
	std::unordered_set<vertex_id_t> successors;
	if(graph == WhichGraph::GRAPH_1){
		vertex_id_t original_vertex_id = graph1_reverse_mapping.at(vertex);
		std::unordered_set neighbors = graph1 -> get_neighbors(original_vertex_id);
		for(const vertex_id_t&vertex : neighbors){
			successors.insert(graph1_mapping.at(vertex));
		}
	} else {
		vertex_id_t original_vertex_id = graph2_reverse_mapping.at(vertex);
		std::unordered_set neighbors = graph2 -> get_neighbors(original_vertex_id);
		for(const vertex_id_t&vertex : neighbors){
			successors.insert(graph2_mapping.at(vertex));
		}
	}
	return std::move(successors);
}

/* DEFINITIONS FOR CLASS: vf2_target_sets */
vf2_target_sets::vf2_target_sets(size_t G1_size, size_t G2_size) {
	tin_1.assign(G1_size, -1);
	tout_1.assign(G1_size, -1);
	core_1.assign(G1_size, -1);
	
	tin_2.assign(G2_size, -1);
	tout_2.assign(G2_size, -1);
	core_2.assign(G2_size, -1);
}

std::size_t vf2_target_sets::get_tin_1_length(){
	return tin_1_length;
}
std::size_t vf2_target_sets::get_tin_2_length(){
	return tin_2_length;
}
std::size_t vf2_target_sets::get_tout_1_length(){
	return tout_1_length;
}
std::size_t vf2_target_sets::get_tout_2_length(){
	return tout_2_length;
}
std::size_t vf2_target_sets::get_core_1_length(){
	return core_1_length;
}
std::size_t vf2_target_sets::get_core_2_length(){
	return core_2_length;
}

void vf2_target_sets::update_target_sets(
	const predecessors_and_successors_of_vertex& G1_vertex, 
	const predecessors_and_successors_of_vertex& G2_vertex, 
	int depth
){
	// turn this into lambda?
	update_target_set(G1_vertex.predecessors, tin_1, depth, tin_1_length);
	update_target_set(G1_vertex.successors, tout_1, depth, tout_1_length);
	update_target_set(G2_vertex.predecessors, tin_2, depth, tin_2_length);
	update_target_set(G2_vertex.successors, tout_2, depth, tout_2_length);
}

void vf2_target_sets::update_target_set(const std::unordered_set<vertex_id_t>& vertices, target & target_set, int depth, size_t & length){
	for(const auto & vertex_id : vertices){
		if(target_set[vertex_id] == -1){
			target_set[vertex_id] = depth;
			length++;
		} 
	}
	
}

void vf2_target_sets:: restore_target_sets(int depth){
	restore_target_set(tin_1, depth, tin_1_length);
	restore_target_set(tout_1, depth, tout_1_length);
	restore_target_set(tin_2, depth, tin_2_length);
	restore_target_set(tout_2, depth, tout_2_length);
}

void vf2_target_sets:: restore_target_set(target& target_set, int depth, size_t& length){
	for(size_t i = 0; i < target_set.size(); i++){
		if(target_set[i] == depth){
			target_set[i] = -1;
			length--;
		}
	}
}

void vf2_target_sets::update_mappings(vertex_id_t node_from_graph_one, vertex_id_t node_from_graph_two, int depth){
	if (tout_1[node_from_graph_one] != -1)
		tout_1_length--;
	else
		tout_1[node_from_graph_one] = depth;

	if (tout_2[node_from_graph_two] != -1)
		tout_2_length--;
	else
		tout_2[node_from_graph_two] = depth;

	if (tin_1[node_from_graph_one] != -1)
		tin_1_length--;
	else
		tin_1[node_from_graph_one] = depth;

	if (tin_2[node_from_graph_two] != -1)
		tin_2_length--;
	else
		tin_2[node_from_graph_two] = depth;

	// updating core_sets
	core_1[node_from_graph_one] = node_from_graph_two;
	core_2[node_from_graph_two] = node_from_graph_one;
	core_1_length++;
	core_2_length++;
}

void vf2_target_sets::restore_mappings(vertex_id_t node_from_graph_one, vertex_id_t node_from_graph_two, int depth){
	if (tout_1[node_from_graph_one] != depth)
		tout_1_length++;
	else
		tout_1[node_from_graph_one] = -1;

	if (tin_1[node_from_graph_one] != depth)
		tin_1_length++;
	else
		tin_1[node_from_graph_one] = -1;

	if (tout_2[node_from_graph_two] != depth)
		tout_2_length++;
	else
		tout_2[node_from_graph_two] = -1;

	if (tin_2[node_from_graph_two] != depth)
		tin_2_length++;
	else
		tin_2[node_from_graph_two] = -1;

	// restore core_set
	core_1[node_from_graph_one] = -1;
	core_2[node_from_graph_two] = -1;
	core_1_length--;
	core_2_length--;
}

std::vector<std::pair<vertex_id_t, vertex_id_t>> vf2_target_sets:: generate_potential_vertex_pairings(){
	std::vector<std::pair<vertex_id_t, vertex_id_t>> pairs;
	if (!(tout_1_length == 0 || tout_2_length == 0)) {
    for (int i = 0; i < tout_1.size(); i++) {
      // if vertex in tout but also in the corresponding core_set then we
      // consider the vertex not apart of the tout set
      if (tout_1[i] == -1) continue;
      if (core_1[i] != -1) continue;
      for (int j = 0; j < tout_2.size(); j++) {
        if (tout_2[j] == -1) continue;
        if (core_2[j] != -1) continue;
        pairs.push_back(std::make_pair(i, j));
      }
    }
    return pairs;
  }

  // generate candidate pairs based on tin sets
  if (!((tin_1_length == 0 || tin_2_length == 0))) {
    for (int i = 0; i < tin_1.size(); i++) {
      // if vertex in tin but also in the corresponding core_set then we
      // consider the vertex not apart of the tin set
      if (tin_1[i] == -1) continue;
      if (tin_1[i] != -1 && core_1[i] != -1) continue;
      for (int j = 0; j < tin_2.size(); j++) {
        if (tin_2[j] == -1) continue;
        if (tin_2[j] != -1 && core_2[j] != -1) continue;
        pairs.push_back(std::make_pair(i, j));
      }
    }
    return pairs;
  }
  // generate candidate pairs from vertices not in lhs and rhs's corresponding
  // core_set
  for (int i = 0; i < core_1.size(); i++) {
    if (core_1[i] != -1) continue;
    for (int j = 0; j < core_2.size(); j++) {
      if (core_2[j] != -1) continue;
      pairs.push_back(std::make_pair(i, j));
    }
  }
	return std::move(pairs);
	
}
template <typename V, typename E, graph_type T>
vertex_mapping vf2_target_sets::generate_final_mapping(const vf2_vertex_id_mapper<V, E, T> & mapper){
	vertex_mapping final_mapping;
	for(int i = 0; i < core_1.size(); i++){
		final_mapping[mapper.graph1_reverse_mapping.at(i)] = mapper.graph2_reverse_mapping.at(core_1[i]);
	}
	return std::move(final_mapping);
}

/* DEFINITIONS DONE */


/* CLASS DEFINITONS FOR vf2_isomorphism_feasibility_checker*/
template <typename V, typename E, graph_type T>
bool vf2_isomorphism_feasibility_checker<V, E, T>::checkFeasibility(
	const std::unique_ptr<vf2_information<V,E,T>>& state,
	const std::pair<vertex_id_t, vertex_id_t>& vertex_pair
) const{
	struct predecessors_and_successors_of_vertex pred_and_succ_vertex1;
	struct predecessors_and_successors_of_vertex pred_and_succ_vertex2;
	
	pred_and_succ_vertex1.predecessors = state-> mapper -> get_predecessors(vertex_pair.first, WhichGraph::GRAPH_1);
	pred_and_succ_vertex1.successors = state-> mapper -> get_successors(vertex_pair.first, WhichGraph::GRAPH_1);
	
	pred_and_succ_vertex2.predecessors = state-> mapper -> get_predecessors(vertex_pair.second, WhichGraph::GRAPH_2);
	pred_and_succ_vertex2.successors = state-> mapper -> get_successors(vertex_pair.second, WhichGraph::GRAPH_2);
	
	bool result_1 = predecessors_consistency_rule(state, pred_and_succ_vertex1, pred_and_succ_vertex2);
	bool result_2 = successors_consistency_rule(state, pred_and_succ_vertex1, pred_and_succ_vertex2);
	bool result_3 = lookahead_tin_rule(state, pred_and_succ_vertex1, pred_and_succ_vertex2);
	bool result_4 = lookahead_tout_rule(state, pred_and_succ_vertex1, pred_and_succ_vertex2);
	bool result_5 = lookahead_new_rule(state, pred_and_succ_vertex1, pred_and_succ_vertex2);
	
	//std::cout << result_1 << " " << result_2 << " " << result_3 << " " << result_4 << " " << result_5 << " " << std::endl;
	
	return result_1 && result_2 && result_3 && result_4 && result_5;
}

template <typename V, typename E, graph_type T>
bool vf2_isomorphism_feasibility_checker<V, E, T>::predecessors_consistency_rule(
		const std::unique_ptr<vf2_information<V,E,T>>& state,
		const struct predecessors_and_successors_of_vertex& pred_succ_vertex1,
		const struct predecessors_and_successors_of_vertex& pred_succ_vertex2
) const{
	std::unordered_set<vertex_id_t> graph1_predecessors_in_the_mapping;
	std::unordered_set<vertex_id_t> graph2_predecessors_in_the_mapping;
	
	for(const auto& item: pred_succ_vertex1.predecessors)
		if(state-> sets -> core_1[item] != -1)
			graph1_predecessors_in_the_mapping.insert(item);
	
	for(const auto& item: pred_succ_vertex2.predecessors)
		if(state-> sets -> core_2[item] != -1)
			graph2_predecessors_in_the_mapping.insert(item);
		
	for (const auto& item : graph1_predecessors_in_the_mapping)
		if (!(state-> sets -> core_1[item] != -1 && graph2_predecessors_in_the_mapping.count(state-> sets -> core_1[item]) > 0)) 
		  return false;
	
  	for (const auto& item : graph2_predecessors_in_the_mapping) 
		if (!(state-> sets -> core_2[item] != -1 && graph1_predecessors_in_the_mapping.count(state-> sets -> core_2[item]) > 0)) 
		  return false;
		
	 return true;
	
}

template <typename V, typename E, graph_type T>
bool vf2_isomorphism_feasibility_checker<V, E, T>::successors_consistency_rule(
	const std::unique_ptr<vf2_information<V,E,T>>& state,
		const struct predecessors_and_successors_of_vertex& pred_succ_vertex1,
		const struct predecessors_and_successors_of_vertex& pred_succ_vertex2
)const {
	std::unordered_set<vertex_id_t> graph1_successors_in_the_mapping;
	std::unordered_set<vertex_id_t> graph2_successors_in_the_mapping;
	
	for(const auto& item: pred_succ_vertex1.successors)
		if(state-> sets -> core_1[item] != -1)
			graph1_successors_in_the_mapping.insert(item);
	
	for(const auto& item: pred_succ_vertex2.successors)
		if(state-> sets -> core_2[item] != -1)
			graph2_successors_in_the_mapping.insert(item);
		
	for (const auto& item : graph1_successors_in_the_mapping)
		if (!(state-> sets -> core_1[item] != -1 && graph2_successors_in_the_mapping.count(state-> sets -> core_1[item]) > 0)) 
		  return false;
	
  	for (const auto& item : graph2_successors_in_the_mapping) 
		if (!(state-> sets -> core_2[item] != -1 && graph1_successors_in_the_mapping.count(state-> sets -> core_2[item]) > 0)) 
		  return false;
		
	 return true;
}
template <typename V, typename E, graph_type T>
bool vf2_isomorphism_feasibility_checker<V, E, T>::lookahead_tin_rule(
	const std::unique_ptr<vf2_information<V,E,T>>& state,
		const struct predecessors_and_successors_of_vertex& pred_succ_vertex1,
		const struct predecessors_and_successors_of_vertex& pred_succ_vertex2
) const {
	size_t number_of_common_vertices_in_predecessor_set_and_tin1 = 0;
	size_t number_of_common_vertices_in_predecessor_set_and_tin2 = 0;
	
	for (const auto& vertex : pred_succ_vertex1.predecessors) {
    	if (state -> sets -> tin_1[vertex] != -1 && state -> sets -> core_1[vertex] == -1) {
    		number_of_common_vertices_in_predecessor_set_and_tin1++;
	    }
	}
	for (const auto& vertex : pred_succ_vertex2.predecessors) {
    	if (state -> sets -> tin_2[vertex] != -1 && state -> sets -> core_2[vertex] == -1) {
    		number_of_common_vertices_in_predecessor_set_and_tin2++;
	    }
	}
	
	if(number_of_common_vertices_in_predecessor_set_and_tin1 != number_of_common_vertices_in_predecessor_set_and_tin2){
		return false;
	}
	
	size_t number_of_common_vertices_in_successor_set_and_tin1 = 0;
	size_t number_of_common_vertices_in_successor_set_and_tin2 = 0;
	
	for (const auto& vertex : pred_succ_vertex1.successors) {
    	if (state -> sets -> tin_1[vertex] != -1 && state -> sets -> core_1[vertex] == -1) {
    		number_of_common_vertices_in_predecessor_set_and_tin1++;
	    }
	}
	for (const auto& vertex : pred_succ_vertex2.successors) {
    	if (state -> sets -> tin_2[vertex] != -1 && state -> sets -> core_2[vertex] == -1) {
    		number_of_common_vertices_in_predecessor_set_and_tin2++;
	    }
	}
	
	if(number_of_common_vertices_in_successor_set_and_tin1 != number_of_common_vertices_in_successor_set_and_tin2){
		return false;
	}
	
	return true;
	
}
template <typename V, typename E, graph_type T>
bool vf2_isomorphism_feasibility_checker<V, E, T>::lookahead_tout_rule(
	const std::unique_ptr<vf2_information<V,E,T>>& state,
		const struct predecessors_and_successors_of_vertex& pred_succ_vertex1,
		const struct predecessors_and_successors_of_vertex& pred_succ_vertex2
) const {
	size_t number_of_common_vertices_in_predecessor_set_and_tout1 = 0;
	size_t number_of_common_vertices_in_predecessor_set_and_tout2 = 0;
	
	for (const auto& vertex : pred_succ_vertex1.predecessors) {
    	if (state -> sets -> tout_1[vertex] != -1 && state -> sets -> core_1[vertex] == -1) {
    		number_of_common_vertices_in_predecessor_set_and_tout1++;
	    }
	}
	for (const auto& vertex : pred_succ_vertex2.predecessors) {
    	if (state -> sets -> tout_2[vertex] != -1 && state -> sets -> core_2[vertex] == -1) {
    		number_of_common_vertices_in_predecessor_set_and_tout2++;
	    }
	}
	
	if(number_of_common_vertices_in_predecessor_set_and_tout1 != number_of_common_vertices_in_predecessor_set_and_tout2){
		return false;
	}
	
	size_t number_of_common_vertices_in_successor_set_and_tout1 = 0;
	size_t number_of_common_vertices_in_successor_set_and_tout2 = 0;
	
	for (const auto& vertex : pred_succ_vertex1.successors) {
    	if (state -> sets -> tout_1[vertex] != -1 && state -> sets -> core_1[vertex] == -1) {
    		number_of_common_vertices_in_predecessor_set_and_tout1++;
	    }
	}
	for (const auto& vertex : pred_succ_vertex2.successors) {
    	if (state -> sets -> tout_2[vertex] != -1 && state -> sets -> core_2[vertex] == -1) {
    		number_of_common_vertices_in_predecessor_set_and_tout2++;
	    }
	}
	
	if(number_of_common_vertices_in_successor_set_and_tout1 != number_of_common_vertices_in_successor_set_and_tout2){
		return false;
	}
	
	return true;
}

template <typename V, typename E, graph_type T>
bool vf2_isomorphism_feasibility_checker<V, E, T>::lookahead_new_rule(
	const std::unique_ptr<vf2_information<V,E,T>>& state,
	const struct predecessors_and_successors_of_vertex& pred_succ_vertex1,
	const struct predecessors_and_successors_of_vertex& pred_succ_vertex2
) const {
	std::unordered_set<vertex_id_t> graph1_vertices_not_in_mapping_or_target_sets;
	std::unordered_set<vertex_id_t> graph2_vertices_not_in_mapping_or_target_sets;
	
	for (int i = 0; i < state-> sets -> core_1.size(); i++) {
    	if (state-> sets -> core_1[i] == -1 && state-> sets -> tin_1[i] == -1 && state-> sets -> tout_1[i] == -1) {
      		graph1_vertices_not_in_mapping_or_target_sets.insert(i);
	    }
	}

  	for (int i = 0; i < state-> sets -> core_2.size(); i++) {
	    if(state-> sets -> core_2[i] == -1 && state-> sets -> tin_2[i] == -1 && state-> sets -> tout_2[i] == -1) {
	      graph2_vertices_not_in_mapping_or_target_sets.insert(i);
    	}
	}
	
	std::unordered_set<vertex_id_t> graph1_intersection_with_predecessors = intersection_set(graph1_vertices_not_in_mapping_or_target_sets, pred_succ_vertex1.predecessors);
	std::unordered_set<vertex_id_t> graph2_intersection_with_predecessors = intersection_set(graph2_vertices_not_in_mapping_or_target_sets, pred_succ_vertex2.predecessors);;
	std::unordered_set<vertex_id_t> graph1_intersection_with_successors = intersection_set(graph1_vertices_not_in_mapping_or_target_sets, pred_succ_vertex1.successors);
	std::unordered_set<vertex_id_t> graph2_intersection_with_successors = intersection_set(graph2_vertices_not_in_mapping_or_target_sets, pred_succ_vertex2.successors);
	
	if(graph1_intersection_with_predecessors.size() == graph2_intersection_with_predecessors.size() &&
		graph1_intersection_with_successors.size() == graph2_intersection_with_successors.size()){
			return true;
	}
	return false;
}

/* DEFINITIONS DONE */
template <typename V, typename E, graph_type T>
bool check_isomorphism(const graph<V, E, T>& graph1, const graph<V, E, T>& graph2, const std::unique_ptr<vf2_information<V,E,T>> &state, const vf2_isomorphism_feasibility_checker<V,E,T>& checker, size_t depth){

	//std::cout << "ON DEPTH ["<< depth << "] " << "length of current mapping " << state -> sets -> get_core_1_length() << std::endl;
	if(state -> sets -> get_core_1_length() == graph1.vertex_count()) return true;
		
	std::vector<std::pair<vertex_id_t, vertex_id_t>> candidate_pairs = state -> sets -> generate_potential_vertex_pairings();
	
	// debugging
	//std::cout << "ON DEPTH ["<< depth << "] " << "enumerating all candidate pairs" << std::endl;
	/*
	for(const auto & pair : candidate_pairs){
		std::cout << pair.first << " : " << pair.second << std::endl;  
	}
	*/
	
	for(const auto & pair : candidate_pairs){
		//std::cout << "trying pair " << pair.first<<"," <<pair.second << std::endl;
		bool possible_valid_pair = checker.checkFeasibility(state, pair);
		if(possible_valid_pair){
			state -> sets -> update_mappings(pair.first, pair.second, depth);
			
			predecessors_and_successors_of_vertex graph1_vertex;
			predecessors_and_successors_of_vertex graph2_vertex;
			
			graph1_vertex.predecessors = state -> mapper -> get_predecessors(pair.first, WhichGraph::GRAPH_1);
			graph1_vertex.successors = state -> mapper -> get_successors(pair.first, WhichGraph::GRAPH_1);
			graph2_vertex.predecessors = state -> mapper -> get_predecessors(pair.second, WhichGraph::GRAPH_2);
			graph2_vertex.successors = state -> mapper -> get_successors(pair.second, WhichGraph::GRAPH_2);
			
			state -> sets -> update_target_sets(graph1_vertex, graph2_vertex, depth);
			
			if(check_isomorphism(graph1, graph2, state, checker, depth + 1) == true)
				return true;
				
			state -> sets -> restore_target_sets(depth);
			state -> sets -> restore_mappings(pair.first, pair.second, depth);
		}
	}
	
	return false;
	

}

}

