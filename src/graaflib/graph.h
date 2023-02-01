#pragma once

#include <initializer_list>
#include <unordered_set>

#include <graaflib/graph_fwd.h>
#include <graaflib/types/edge.h>
#include <graaflib/types/vertex.h>

namespace graaf {

	template <typename T, typename T_HASH>
	class graph {
		public:
			using vertex_type = types::vertex<T, T_HASH>;
			using edge_type = types::edge;
			using vertices_type = std::unordered_set<vertex_type, types::vertex_hash>;
			using edges_type = std::unordered_set<edge_type, types::edge_hash>;

			graph(std::initializer_list<vertex_type> vertices, std::initializer_list<edge_type> edges)
				: vertices_{vertices}, edges_{edges} {}

			[[nodiscard]] std::size_t vertex_count() const noexcept { return vertices_.size(); }
			[[nodiscard]] std::size_t edge_count() const noexcept { return edges_.size(); }

			[[nodiscard]] const vertices_type& vertices() const noexcept { return vertices_; }
			[[nodiscard]] const edges_type& edges() const noexcept { return edges_; }

		private:
			vertices_type vertices_;
			edges_type edges_;
		};


}
