#pragma once

namespace graaf::types {

	// Strong type for edge IDs
	using edge_id_t = std::size_t;

    struct edge {
		edge_id_t from_id{};
		edge_id_t to_id{};

		bool operator==(const edge& rhs) const {
			return from_id == rhs.from_id && to_id == rhs.to_id;
		}
	};

}