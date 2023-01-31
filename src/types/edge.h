#pragma once

namespace graaf::types {

    struct edge {
		std::size_t from_id{};
		std::size_t to_id{};

		bool operator==(const edge& rhs) const {
			return from_id == rhs.from_id && to_id == rhs.to_id;
		}
	};

	struct edge_hash {
		std::size_t operator()(const edge& k) const {
			return std::hash<std::size_t>()(k.from_id) ^ (std::hash<std::size_t>()(k.to_id) << 1);
		}
	};

}