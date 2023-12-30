namespace graaf::algorithm::vf2{

template <typename V, typename E, graph_type T>
std::optional<std::unordered_map<vertex_id_t, vertex_id_t>> check_isomorphism(
	const graph<V, E, T>& graph1, 
	const graph<V, E, T>& graph2
){
	std::cout << "in here" << std::endl;
    std::unique_ptr<vf2_information<V,E,T>> state = std::make_unique<vf2_information<V,E,T>>(graph1, graph2);
    vf2_isomorphism_feasibility_checker<V,E,T> checker;
   	bool valid_mapping_found = check_isomorphism(graph1, graph2, state, checker, 0);
    
    return std::nullopt;
    
}


}
