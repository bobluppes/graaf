#pragma once

#include <initializer_list>
#include <stdexcept>
#include <vector>

#include <graaflib/types/edge.h>
#include <graaflib/types/vertex.h>

namespace graaf {

	template <typename T, typename EDGE>
	class graph {
		public:
			using vertex_t = types::vertex<T>;
			using edge_t = EDGE;

			// The index into the vector is the ID of the vertex or edge, all IDs should be consecutive and start at 0
			using vertices_t = std::vector<vertex_t>;
			using edges_t = std::vector<edge_t>;

			graph(vertices_t&& vertices, edges_t&& edges) : vertices_{vertices}, edges_{edges} {}

			graph(std::initializer_list<typename vertices_t::value_type> vertices, std::initializer_list<edge_t> edges)
				: vertices_{vertices}, edges_{edges} {}

			[[nodiscard]] std::size_t vertex_count() const noexcept { return vertices_.size(); }
			[[nodiscard]] std::size_t edge_count() const noexcept { return edges_.size(); }

			[[nodiscard]] const vertices_t& vertices() const noexcept { return vertices_; }
			[[nodiscard]] const edges_t& edges() const noexcept { return edges_; }

			[[nodiscard]] const vertex_t& get_vertex(types::vertex_id_t id) const {
				if (id >= edges_.size()) {
					throw std::out_of_range("Vertex not contained in graph.");
				}
				return vertices_[id];
			}

			[[nodiscard]] const edge_t& get_edge(types::edge_id_t id) {
				if (id >= edges_.size()) {
					throw std::out_of_range("Edge not contained in graph.");
				}
				return edges_[id];
			}

		private:
			vertices_t vertices_;
			edges_t edges_;
		};


}
