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

// Type aliases
using Mapping = std::unordered_map<vertex_id_t, vertex_id_t>;
using Candidate_pairs = std::vector<std::pair<vertex_id_t, vertex_id_t>>;
using Core_set = std::vector<int>;
using Terminal_set = std::vector<int>;

/**
 * @brief Checks if two graphs are isomorphic.
 *
 * This function checks whether two given graphs are isomorphic, meaning
 * they are structurally identical up to vertex and edge relabeling.
 * If the graphs are isomorphic, the function returns an optional containing
 * a mapping from the vertices of the first graph to the vertices of the second graph.
 * If the graphs are not isomorphic, the function returns std::nullopt.
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to compare.
 * @param rhs The second graph to compare.
 * @return An optional containing a mapping from the vertices of lhs to those of rhs if isomorphic; otherwise std::nullopt.
 */
template <typename V, typename E, graph_type T>
std::optional<Mapping>
check_isomorphism(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs
);


/**
 * @brief struct represents the state information for the vf2 algorithm
 * 
 * Types aliases:
 * Mapping -> std::unordered_map<vertex_id_t, vertex_id_t>;
 * Candidate_pairs -> std::vector<std::pair<vertex_id_t, vertex_id_t>>;
 * Core_set ->  std::vector<int>;
 * Terminal_set -> std::vector<int>;
 * @param Terminal_set tin_1, the set of nodes in graph (G1) that have edges where the destination nodes are nodes in the mapping
 * @param Terminal_set tout_1,  the set of nodes in graph (G1) that have edges where the source nodes are nodes in the mapping
 * @param Terminal_set tin_2, the set of nodes in graph (G2) that have edges where the destination nodes are nodes in the mapping
 * @param Terminal_set tout_2, the set of nodes in graph (G2) that have edges where the source nodes are nodes in the mapping
 * @param Mapping lhs_node_order, maps vertex_id_t id of node in graph (G1) to an vertex_id_t to be easily indexed by a vector
 * @param Mapping rhs_node_order, maps vertex_id_t id of node in graph (G2) to an vertex_id_t to be easily indexed by a vector
 * @param Mapping lhs_reverse_node_order, reverses the mapping done by lhs_node_order for graph (G1)
 * @param Mapping rhs_reverse_node_order, reverses the mapping done by lhs_node_order for graph (G2)
 * @param Core_set lhs_core, a vector to map nodes from graph (G1) to graph (G2) 
 * @param Core_set rhs_core, a vector to map nodes from graph (G2) to graph (G1)
 * @param size_t lhs_core_len, tracks number of valid nodes in lhs_core
 * @param size_t rhs_core_len, tracks number of valid nodes in rhs_core
 * @param size_t tin_1_len, tracks number of valid nodes in tin_1
 * @param size_t tout_1_len, tracks number of valid nodes in tout_1
 * @param size_t tin_2_len, tracks number of valid nodes in tin_2
 * @param size_t tout_2_len, tracks number of valid nodes in tout_2
 */
struct vf2_state {
	Terminal_set tin_1;
	Terminal_set tout_1;
	Terminal_set tin_2;
	Terminal_set tout_2;
	Mapping lhs_node_order;  
	Mapping rhs_node_order;  
	Mapping lhs_reverse_node_order;  
	Mapping rhs_reverse_node_order;  
	Core_set lhs_core;
	Core_set rhs_core;
	size_t lhs_core_len = 0;
	size_t rhs_core_len = 0;
	size_t tin_1_len = 0;
	size_t tout_1_len = 0;
	size_t tin_2_len = 0;
	size_t tout_2_len = 0;
};	


/**
 * @brief a recursive helper function to facilitate creating isomorphic mapping between graphs
 *
 * The function will generate possible node pairs, consisting of a node from graphs lhs and rhs,
 * and then check if a pair passes vf2's feasability rules 
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to compare.
 * @param rhs The second graph to compare.
 * @param state the vf2_state containing information about the mappings, core and terminal sets
 * @param depth the depth of the recursion, important for backtracking the state to previous versions
 * @return a bool indicating if an isomorphic mapping had been found
 */
template <typename V, typename E, graph_type T>
bool check_isomorphism_helper(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state & state,
	size_t depth
);

/**
 * @brief initalize the inital state for the vf2 algorithm based on the graphs being compared
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to compare.
 * @param rhs The second graph to compare.
 * @return vf2_state struct
 */
template <typename V, typename E, graph_type T>
vf2_state * init_vf2_state(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs
);

/**
 * @brief functions returns an unordered_set of the nodes which are the destinations of edges stemming from @param node, otherwise 
 * known as the successors of node
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param _graph The graph containing the node
 * @param mapping The mapping containing _graph's node's vertex_id_t mapped to vertex_id_t's given by the VF2 algorithm
 * @param reverse_mapping The reverse_mapping is used to go from VF2's given vertex_id_t for a node to the original vertex_id_t
 * in _graph
 * @param node The node for which we get the successors
 * @return an unordered_set with nodes containing edges pointing to @param node, otherwise known as the
 * successors of node
 */

template <typename V, typename E, graph_type T>
std::unordered_set<vertex_id_t> get_successors(
	const graph <V, E, T> & _graph,
	const Mapping & mapping,
	const Mapping & reverse_mapping,
	vertex_id_t node
);

/**
 * @brief function returns an unordered_set of the nodes which are the sources of edges stemming towards the @param node, 
 * otherwise known as the predecessors of node
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param _graph The graph containing the node
 * @param mapping The mapping containing _graph's node's vertex_id_t mapped to vertex_id_t's given by the VF2 algorithm
 * @param reverse_mapping The reverse_mapping is used to go from VF2's given vertex_id_t for a node to the original vertex_id_t
 * in _graph
 * @param node The node for which we get the successors
 * @return an unordered_set with nodes containing the predecessors @param node
 */
template <typename V, typename E, graph_type T>
std::unordered_set<vertex_id_t> get_predecessors(
	const graph <V, E, T> & _graph,
	const Mapping & mapping,
	const Mapping & reverse_mapping,
	vertex_id_t node
);

/**
 * @brief function generate candidate pairs, which are pairs of nodes from lhs and rhs that may be possibly mapped to each other in 
 * an isomorphic mapping 
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to be compared
 * @param rhs The second graph to be compared
 * @param state The vf2_state containing information about mapping, core and terminal sets
 * @return a vector of vertex_id_t pairs
 */
template <typename V, typename E, graph_type T>
Candidate_pairs generate_candidate_pairs(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	const struct vf2_state & state
);

/**
 * @brief before checking two graphs for isomorphism we can rule out the possibility by comparing node and edge counts
 * this function checks for that
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to be compared
 * @return a bool representing if an isomorphism is possible
 */
template <typename V, typename E, graph_type T>
bool check_for_possibility_of_isomorphism(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs
);

/**
 * @brief to make keep track of nodes in each graph much easier, we assign custom vertex_id_t to each node in _graph
 * analogous to indexes in a vector
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param map The reference to the mapping we want to modify, this function will be always be given an empty unordered_map
 * @param _graph The graph we create a mapping from
 */
template <typename V, typename E, graph_type T>
void create_node_ordering(
	std::unordered_map<vertex_id_t, vertex_id_t> & map,
	const graph <V, E, T> & _graph
);

/**
 * @brief The function creates a mapping to get the original vertex_id_t of a node from a custom vertex_id_t. This is useful for 
 * searching and getting results from graphs vf2 is comparing
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param map The reference to the mapping we want to modify, this function will be always be given an empty unordered_map
 * @param _graph The graph we create a mapping from
 */
void create_reverse_node_ordering(
	std::unordered_map<vertex_id_t, vertex_id_t> & map,
	std::unordered_map<vertex_id_t, vertex_id_t> & reverse_map
);


/**
 * @brief For a pair of nodes to be added to the isomorphic mapping, if one exists, it must pass five feasability rules, and this 
 * function return the boolean result of passing all five rules
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to be compared
 * @param rhs The second graph to be compared
 * @param state The vf2_state containing the current information on the mapping, core and terminal sets
 * @param node_lhs The node from graph lhs
 * @param node_rhs the node from graph rhs
 */
template <typename V, typename E, graph_type T>
bool feasibility(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);

/**
 * @brief This function checks if a pair of node passes the r_pred feasibility rule, which checks if the pair of node have any 
 * ancestors that have already been mapped to each other in the current isomorphic mapping
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to be compared
 * @param rhs The second graph to be compared
 * @param state The vf2_state containing the current information on the mapping, core and terminal sets
 * @param node_lhs The node from graph lhs
 * @param node_rhs the node from graph rhs
 */
template <typename V, typename E, graph_type T>
bool r_pred(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);

/**
 * @brief This function checks if a pair of node passes the r_succ feasibility rule, which checks if the pair of nodes have any 
 * successors that have already been mapped to each other in the current isomorphic mapping
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to be compared
 * @param rhs The second graph to be compared
 * @param state The vf2_state containing the current information on the mapping, core and terminal sets
 * @param node_lhs The node from graph lhs
 * @param node_rhs the node from graph rhs
 */

template <typename V, typename E, graph_type T>
bool r_succ(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);

/**
 * @brief This function checks if a pair of node passes the r_in feasibility rule, which checks if the pair of nodes have the same
 * amount of successors and predecessor nodes in the tin_1 and tin_2 sets to match 
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to be compared
 * @param rhs The second graph to be compared
 * @param state The vf2_state containing the current information on the mapping, core and terminal sets
 * @param node_lhs The node from graph lhs
 * @param node_rhs the node from graph rhs
 */
template <typename V, typename E, graph_type T>
bool r_in(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);


/**
 * @brief This function checks if a pair of node passes the r_out feasibility rule, which checks if the pair of nodes which checks
 * if the pair of nodes have the same amount of successors and predecessor nodes in the tout_1 and tout_2 sets to match 
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to be compared
 * @param rhs The second graph to be compared
 * @param state The vf2_state containing the current information on the mapping, core and terminal sets
 * @param node_lhs The node from graph lhs
 * @param node_rhs the node from graph rhs
 */
template <typename V, typename E, graph_type T>
bool r_out(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);

/**
 * @brief This function checks if a pair of node passes the r_new feasibility rule, which checks if the pair of nodes in their 
 * respective graphs have the same number of nodes that are not in either the mapping or terminal sets to be matched
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to be compared
 * @param rhs The second graph to be compared
 * @param state The vf2_state containing the current information on the mapping, core and terminal sets
 * @param node_lhs The node from graph lhs
 * @param node_rhs the node from graph rhs
 */
template <typename V, typename E, graph_type T>
bool r_new(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs
);


/**
 * @brief This function updates the terminal sets tin_1, tin_2, tout_1, tout_2 based on node_lhs and node_rhs representing the pair 
 * of nodes added to the mapping
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to be compared
 * @param rhs The second graph to be compared
 * @param state The vf2_state containing the current information on the mapping, core and terminal sets
 * @param node_lhs The node from graph lhs
 * @param node_rhs the node from graph rhs
 * @param depth The depth of the recursion
 */
template <typename V, typename E, graph_type T>
void update_terminal_sets(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state & state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs,
	size_t depth
);


/**
 * @brief This function updates the mappings by adding the node pair
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to be compared
 * @param rhs The second graph to be compared
 * @param state The vf2_state containing the current information on the mapping, core and terminal sets
 * @param node_lhs The node from graph lhs
 * @param node_rhs the node from graph rhs
 * @param depth The depth of the recursion
 */
template <typename V, typename E, graph_type T>
void update_mappings(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs,
	size_t depth
);


/**
 * @brief This function restores the terminal sets tin_1, tin_2, tout_1, and tout_2 to previous state before a node pair was added
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to be compared
 * @param rhs The second graph to be compared
 * @param state The vf2_state containing the current information on the mapping, core and terminal sets
 * @param node_lhs The node from graph lhs
 * @param node_rhs the node from graph rhs
 * @param depth The depth of the recursion
 */
template <typename V, typename E, graph_type T>
void restore_terminal_sets(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs,
	int depth
);

/**
 * @brief This function restores the isomorphic mapping to the state prior to adding node_lhs and node_rhs
 *
 * @tparam V The vertex type of the graphs.
 * @tparam E The edge type of the graphs.
 * @tparam T The graph type of the graphs (directed or undirected).
 * @param lhs The first graph to be compared
 * @param rhs The second graph to be compared
 * @param state The vf2_state containing the current information on the mapping, core and terminal sets
 * @param node_lhs The node from graph lhs
 * @param node_rhs the node from graph rhs
 * @param depth The depth of the recursion
 */
template <typename V, typename E, graph_type T>
void restore_mappings(
	const graph <V, E, T> & lhs,
	const graph <V, E, T> & rhs,
	struct vf2_state * state,
	vertex_id_t node_lhs,
	vertex_id_t node_rhs,
	size_t depth
);




} // namespace graaf::algorithm




#include "graph_isomorphism.tpp"



