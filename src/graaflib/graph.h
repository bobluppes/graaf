#pragma once

#include <initializer_list>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include <graaflib/types/edge.h>
#include <graaflib/types/vertex.h>

namespace graaf {

	template <typename T>
	class graph {
		public:
			using vertex_type = types::vertex<T>;
			using edge_type = types::edge;

			// Unordered map for fast access by vertex ID
			using vertices_type = std::unordered_map<types::vertex_id_t, vertex_type>;
			// The index into the vector is the ID of the edge, all vertex IDs should be consecutive and start at 0
			using edges_type = std::vector<edge_type>;

			graph(vertices_type&& vertices, edges_type&& edges) : vertices_{vertices}, edges_{edges} {}

			graph(std::initializer_list<vertex_type> vertices, std::initializer_list<edge_type> edges)
				: vertices_{vertices}, edges_{edges} {}

			[[nodiscard]] std::size_t vertex_count() const noexcept { return vertices_.size(); }
			[[nodiscard]] std::size_t edge_count() const noexcept { return edges_.size(); }

			[[nodiscard]] const vertices_type& vertices() const noexcept { return vertices_; }
			[[nodiscard]] const edges_type& edges() const noexcept { return edges_; }

			[[nodiscard]] const vertex_type& get_vertex(types::vertex_id_t id) const {
				if (!vertices_.contains(id)) {
					throw std::out_of_range("Vertex not contained in graph.");
				}
				return vertices_[id];
			}

			[[nodiscard]] const edge_type& get_edge(types::edge_id_t id) {
				if (id >= edges_.size()) {
					throw std::out_of_range("Edge not contained in graph.");
				}
				return edges_[id];
			}

		private:
			vertices_type vertices_;
			edges_type edges_;
		};


}
