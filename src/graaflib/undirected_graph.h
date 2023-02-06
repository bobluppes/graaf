#pragma once

#include <utility>

#include <graaflib/builders/graphbuilder.h>
#include <graaflib/types/edge.h>
#include <graaflib/graph.h>

namespace graaf {

    template <typename T>
    class undirected_graph final : public graph<T, types::undirected_edge>{
        public:

            using edge_t = types::undirected_edge;

            using vertices_t = typename graph<T, edge_t>::vertices_t;
            using edges_t = typename graph<T, edge_t>::edges_t;

            undirected_graph(vertices_t&& vertices, edges_t&& edges) : graph<T, edge_t>(std::move(vertices), std::move(edges)) {
                do_validate();
            }

			undirected_graph(std::initializer_list<typename vertices_t::value_type> vertices, std::initializer_list<edge_t> edges)
				: graph<T, edge_t>(vertices, edges) {
                    do_validate();
                }

            [[nodiscard]] std::string get_graph_type() const override {
                return "graph";
            }

            using builder = builders::graphbuilder<undirected_graph<T>>;
        private:
            void do_validate() const {
                // TODO: validation logic
            }
    };

}