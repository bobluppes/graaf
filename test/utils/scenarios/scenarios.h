#pragma once

#include <graaflib/types.h>

#include <vector>

namespace graaf::utils::scenarios
{

template<typename GRAPH_T>
struct scenario
{
    GRAPH_T graph {};

    // This vector decouples the test scenario from the graphs internal id
    // generation logic. The first element in this vector is the first vertex and
    // so on...
    std::vector<vertex_id_t> vertex_ids {};
};

/**
 * Creates a scenario containing a tree structured graph. In the visualization
 * below, vertices and edge values are shown. Vertex IDs are given between
 * parentheses.
 *
 * The direction of the edges is visualized. However, undirected edges are
 * supported as well if an undirected graph is passed as a template parameter.
 *
 * ┌────────┐  100   ┌────────┐
 * │ 20 (1) │ ◀───── │ 10 (0) │
 * └────────┘        └────────┘
 *                     │
 *                     │ 200
 *                     ▼
 * ┌────────┐  400   ┌────────┐
 * │ 50 (4) │ ◀───── │ 30 (2) │
 * └────────┘        └────────┘
 *                     │
 *                     │ 300
 *                     ▼
 *                   ┌────────┐
 *                   │ 40 (3) │
 *                   └────────┘
 *
 * @tparam GRAPH_T Can be either a directed or undirected graph with numeric
 * vertices and edges.
 * @return The scenario containing the graph structure.
 */
template<typename GRAPH_T>
[[nodiscard]]
scenario<GRAPH_T> create_tree_scenario();

/**
 * Creates a scenario containing a simple graph structure. In the visualization
 * below, vertices and edge values are shown. Vertex IDs are given between
 * parentheses.
 *
 * The direction of the edges is visualized. However, undirected edges are
 * supported as well if an undirected graph is passed as a template parameter.
 *
 *       ┌────────┐
 *       │ 10 (0) │ ◀┐
 *       └────────┘  │
 *         │         │
 *         │ 100     │
 *         ▼         │
 *       ┌────────┐  │
 *       │ 20 (1) │  │ 300
 *       └────────┘  │
 *         │         │
 *         │ 200     │
 *         ▼         │
 *       ┌────────┐  │
 * ┌──── │ 30 (2) │ ─┘
 * │     └────────┘
 * │       │
 * │       │ 400
 * │       ▼
 * │     ┌────────┐
 * │ 600 │ 40 (3) │
 * │     └────────┘
 * │       │
 * │       │ 500
 * │       ▼
 * │     ┌────────┐
 * └───▶ │ 50 (4) │
 *       └────────┘
 *
 * @tparam GRAPH_T Can be either a directed or undirected graph with numeric
 * vertices and edges.
 * @return The scenario containing the graph structure.
 */
template<typename GRAPH_T>
[[nodiscard]]
scenario<GRAPH_T> create_simple_graph_scenario();

/**
 * Creates a scenario containing a fully connected graph structure. In the
 * visualization below, vertices and edge values are shown. Vertex IDs are given
 * between parentheses.
 *
 * The direction of the edges is visualized. However, undirected edges are
 * supported as well if an undirected graph is passed as a template parameter.
 *
 *
 *                   ┌─────────────────┐
 *                   │                 │
 *                 ┌────────┐          │
 *           ┌──── │ 10 (0) │ ─┐       │
 *           │     └────────┘  │       │
 *           │       │         │       │
 *           │       │ 100     │       │
 *           │       ▼         │       │
 *           │     ┌────────┐  │       │
 *      ┌────┼──── │ 20 (1) │ ─┼───────┼────────────┐
 *      │    │     └────────┘  │       │            │
 *      │    │       │         │       │            │
 *      │    │       │ 500     │ 200   │            │
 *      │    │       ▼         │       │            │
 *      │    │     ┌────────┐  │       │            │
 * ┌────┼────┼──── │ 30 (2) │ ◀┘       │            │
 * │    │    │     └────────┘          │            │
 * │    │    │       │                 │            │
 * │    │    │ 300   │ 800             │            │ 700
 * │    │    │       ▼                 │            │
 * │    │    │     ┌────────┐  600     │            │
 * │    │    └───▶ │ 40 (3) │ ◀────────┼───────┐    │
 * │    │          └────────┘          │       │    │
 * │    │            │                 │       │    │
 * │    │            │ 1000            │ 400   │    │
 * │    │            ▼                 ▼       │    │
 * │    │   900    ┌────────────────────────┐  │    │
 * └────┼────────▶ │         50 (4)         │ ◀┼────┘
 *      │          └────────────────────────┘  │
 *      │                                      │
 *      └──────────────────────────────────────┘
 *
 * @tparam GRAPH_T Can be either a directed or undirected graph with numeric
 * vertices and edges.
 * @return The scenario containing the graph structure.
 */
template<typename GRAPH_T>
[[nodiscard]]
scenario<GRAPH_T> create_fully_connected_graph_scenario();

/**
 * Creates a scenario containing a disconnected graph consisting of two
 * conntected subgraphs. In the visualization below, vertices and edge values
 * are shown. Vertex IDs are given between parentheses.
 *
 * The direction of the edges is visualized. However, undirected edges are
 * supported as well if an undirected graph is passed as a template parameter.
 *
 *
 *┌────────┐  200   ┌────────┐
 *│ 30 (2) │ ◀───── │ 10 (0) │
 *└────────┘        └────────┘
 *                   │
 *                   │ 100
 *                   ▼
 *                 ┌────────┐
 *                 │ 20 (1) │
 *                 └────────┘
 *                 ┌────────┐
 *                 │ 40 (3) │ ◀┐
 *                 └────────┘  │
 *                   │         │
 *                   │ 300     │
 *                   ▼         │
 *                 ┌────────┐  │
 *                 │ 50 (4) │  │ 500
 *                 └────────┘  │
 *                   │         │
 *                   │ 400     │
 *                   ▼         │
 *                 ┌────────┐  │
 *                 │ 60 (5) │ ─┘
 *                 └────────┘
 *
 * @tparam GRAPH_T Can be either a directed or undirected graph with numeric
 * vertices and edges.
 * @return The scenario containing the graph structure.
 */
template<typename GRAPH_T>
[[nodiscard]]
scenario<GRAPH_T> create_disconnected_graph_scenario();
} // namespace graaf::utils::scenarios

#include "scenarios.tpp"
