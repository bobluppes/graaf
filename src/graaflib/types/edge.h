#pragma once

#include <algorithm>
#include <bits/ranges_algo.h>
#include <cstddef>
#include <vector>

#include <graaflib/types/vertex.h>

namespace graaf::types {

	// Strong type for edge IDs
	using edge_id_t = std::size_t;

    struct directed_edge {
		vertex_id_t from{};
		vertex_id_t to{};

		bool operator==(const directed_edge& rhs) const {
			return from == rhs.from && to == rhs.to;
		}

		friend std::ostream& operator<<(std::ostream& os, const directed_edge& e) {
				os << fmt::format("[{} -> {}]", e.from, e.to);
				return os;
			}
	};

	struct undirected_edge {
		vertex_id_t lhs{};
		vertex_id_t rhs{};

		bool operator==(const undirected_edge& other) const {
			std::vector<vertex_id_t> this_vertices{lhs, rhs};
			std::vector<vertex_id_t> other_vertices{other.lhs, other.rhs};

			// Sort the vectors as the order of an undirected edge does not matter
			// This is cheap as there is only one comparison required per vector
			std::ranges::make_heap(this_vertices);
			std::ranges::make_heap(other_vertices);

			return this_vertices == other_vertices;
		}

		friend std::ostream& operator<<(std::ostream& os, const undirected_edge& e) {
				os << fmt::format("[{} -- {}]", e.lhs, e.rhs);
				return os;
			}
	};

}