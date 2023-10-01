// graaflib/algorithm/topological_sorting/kahn.h
#ifndef GRAAF_KAHN_H
#define GRAAF_KAHN_H

#include <vector>
#include <optional>
#include <graaf/include/graaflib/graph.h> // Include graph header
#include "graaf/properties/vertex_properties.h" // Include vertex properties header

namespace graaflib::algorithm::topological_sorting {

    template <typename V, typename E>
    std::optional<std::vector<vertex_id_t>> kahns_topological_sort(
        const graph<V, E, graph_type::DIRECTED>& graph
    );

} 

#endif 
