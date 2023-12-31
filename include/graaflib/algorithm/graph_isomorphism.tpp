namespace graaf::algorithm::vf2{


template <typename V, typename E, graph_type T>
bool check_for_possibility_of_isomorphism(const graph<V,E,T>& lhs, const graph<V,E,T>& rhs){
	if (lhs.vertex_count() != rhs.vertex_count() ||
	  lhs.edge_count() != rhs.edge_count())
	return false;
	std::vector<std::size_t> lhs_node_degrees, rhs_node_degrees;
	for (const auto& vertex : lhs.get_vertices()) {
	std::size_t number_of_conn = lhs.get_neighbors(vertex.first).size();
	lhs_node_degrees.push_back(number_of_conn);
	}
	for (const auto& vertex : rhs.get_vertices()) {
	std::size_t number_of_conn = rhs.get_neighbors(vertex.first).size();
	rhs_node_degrees.push_back(number_of_conn);
	}
	std::sort(lhs_node_degrees.begin(), lhs_node_degrees.end());
	std::sort(rhs_node_degrees.begin(), rhs_node_degrees.end());
	for (int i = 0; i < lhs_node_degrees.size(); i++)
	if (lhs_node_degrees[i] != rhs_node_degrees[i]) return false;
	return true;
}


template <typename V, typename E, graph_type T>
std::optional<std::unordered_map<vertex_id_t, vertex_id_t>> check_isomorphism(
	const graph<V, E, T>& graph1, 
	const graph<V, E, T>& graph2
){
	if(!check_for_possibility_of_isomorphism(graph1, graph2)) return std::nullopt;
	

    std::unique_ptr<vf2_information<V,E,T>> state = std::make_unique<vf2_information<V,E,T>>(graph1, graph2);
    std::cout << "FOR DEBUGGING Listing the values of the vertices" << std::endl;
	std::cout << "graph 1" << std::endl << "format actual val: mapping val " << std::endl;
	for(const auto&[id, mapped_id] : state -> mapper -> graph1_mapping){
		std::cout << id << ":" << mapped_id << std::endl;
	}	
	
	std::cout << "graph 2" << std::endl << "format actual val: mapping val " << std::endl;
	for(const auto&[id, mapped_id] : state -> mapper -> graph2_mapping){
		std::cout << id << ":" << mapped_id << std::endl;
	}	
	  
	    
    vf2_isomorphism_feasibility_checker<V,E,T> checker;
   	bool valid_mapping_found = check_isomorphism(graph1, graph2, state, checker, 0);
	if(valid_mapping_found){
		vertex_mapping isomorphic_mapping;
		for(int i = 0; i < graph1.vertex_count(); i++){
			isomorphic_mapping = state -> sets -> generate_final_mapping(*(state -> mapper)); 		
		}
		return isomorphic_mapping;
	}
	return std::nullopt;    
    
}


}
