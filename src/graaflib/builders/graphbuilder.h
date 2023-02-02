#pragma once

#include <initializer_list>
#include <unordered_set>

#include <graaflib/graph_fwd.h>

namespace graaf::builders {

    template <typename T, typename T_HASH, typename V, typename V_HASH, typename E, typename E_HASH>
    class graphbuilder {
        public:
            using vertices_type = std::unordered_set<V, V_HASH>;
            using edges_type = std::unordered_set<E, E_HASH>;

            graphbuilder& vertices(std::initializer_list<V> vertices) {
                // TODO: assert vertices_ empty
                vertices_ = vertices;
                return *this;
            }

            graphbuilder& edges(std::initializer_list<E> edges) {
                // TODO: assert edges_ empty
                edges_ = edges;
                return *this;
            }

            [[nodiscard]] std::size_t add_vertex(T element) {
                [[maybe_unused]] const auto [vertex, success]{vertices_.insert({id_supplier_++, std::move(element)})};
                // TODO: assert success
                return vertex->get_id();
            }

            void add_edge(std::size_t l, std::size_t r) {
                edges_.insert({l, r});  // TODO: maybe use emplace
                // TODO: assert success
            }

            graaf::graph<T, T_HASH> build() {
                return graaf::graph<T, T_HASH>{std::move(vertices_), std::move(edges_)};
            }

        private:
            vertices_type vertices_{};
            edges_type edges_{};

            std::size_t id_supplier_{0};
    };

}