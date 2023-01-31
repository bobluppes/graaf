#pragma once

#include <initializer_list>
#include <unordered_set>

#include "types/edge.h"
#include "types/vertex.h"

namespace graaf {

	template <typename T, typename T_HASH = std::hash<T>>
	class graaf {
		public:
			using vertex_type = types::vertex<T, T_HASH>;
			using edge_type = types::edge;

			graaf(std::initializer_list<vertex_type> vertices, std::initializer_list<edge_type> edges)
				: vertices_{vertices}, edges_{edges} {}

			[[nodiscard]] std::size_t number_of_vertices() const { return vertices_.size(); }

		private:
			std::unordered_set<vertex_type, types::vertex_hash> vertices_;
			std::unordered_set<edge_type, types::edge_hash> edges_;
		};


}
