#pragma once

#include <initializer_list>
#include <unordered_set>

#include <graaflib/graph_fwd.h>
#include <graaflib/types/edge.h>
#include <graaflib/types/vertex.h>

namespace graaf::builders {

    template <class GRAPH>
    class graphbuilder {
        public:
            using vertices_type = typename GRAPH::vertices_t;
            using edges_type = typename GRAPH::edges_t;

            // TODO: this implicitly relies on the container types
            using vertex_t = typename vertices_type::value_type;
            using edge_t = typename edges_type::value_type;

            using element_t = typename vertex_t::element_t;

            graphbuilder& vertices(std::initializer_list<typename vertices_type::value_type> vertices) {
                // TODO: assert vertices_ empty
                vertices_ = vertices;
                return *this;
            }

            graphbuilder& edges(std::initializer_list<edge_t> edges) {
                // TODO: assert edges_ empty
                edges_ = edges;
                return *this;
            }

            [[nodiscard]] types::vertex_id_t add_vertex(element_t element) {
                vertices_.emplace_back(vertex_t{id_supplier_++, std::move(element)});
                
                // The ID of the vertex is it's index into the container
                return vertices_.size() - 1;
            }

            types::edge_id_t add_edge(std::size_t l, std::size_t r) {
                edges_.emplace_back(edge_t{l, r});

                // The ID of the vertex is it's index into the container
                return edges_.size() - 1;
            }

            GRAPH build() {
                return {std::move(vertices_), std::move(edges_)};
            }

        private:
            vertices_type vertices_{};
            edges_type edges_{};

            std::size_t id_supplier_{0};
    };

}