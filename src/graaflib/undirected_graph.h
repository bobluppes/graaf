#pragma once

#include <utility>

#include <graaflib/graph.h>

namespace graaf {

    template <typename T>
    class undirected_graph : public graph<T>{

        using vertices_type = typename graph<T>::vertices_type;
        using edges_types = typename graph<T>::edges_type;

        public:
            undirected_graph(vertices_type&& vertices, edges_types&& edges) : graph<T>(std::forward(vertices), std::forward(edges)) {
                do_validate();
            }

			undirected_graph(std::initializer_list<typename vertices_type::value_type> vertices, std::initializer_list<typename edges_types::value_type> edges)
				: graph<T>(vertices, edges) {
                    do_validate();
                }
        private:
            void do_validate() const {
                // TODO: validation logic
            }
    };

}