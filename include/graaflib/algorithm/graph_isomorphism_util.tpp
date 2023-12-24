#pragma once

namespace graaf::algorithm::vf2{

template <typename V, typename E, graph_type T>
vf2_vertex_id_mapper<V, E, T>::vf2_vertex_id_mapper(const graph<V, E, T>& _graph1, const graph<V, E, T>& _graph2){
	create_mapping(graph1_mapping, graph1);
	create_mapping(graph2_mapping, graph2);
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
/* DEFINITIONS DONE */
}

