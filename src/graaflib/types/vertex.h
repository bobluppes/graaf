#pragma once

#include <ostream>
#include <utility>

#include <fmt/core.h>

namespace graaf::types {

	// Strong type for vertex IDs
	using vertex_id_t = std::size_t;

    template <typename T>
	class vertex {
		public:
			using element_t = T;

			vertex(vertex_id_t id, T elem) : id_{id}, elem_{std::move(elem)} {}

			vertex_id_t get_id() const { return id_; }
			const T& get_element() const { return elem_; }

			bool operator==(const vertex rhs) const {
					return id_ == rhs.get_id() && elem_ == rhs.get_element();
			}

			friend std::ostream& operator<<(std::ostream& os, const vertex& v) {
				return os << fmt::format("[{}, {}]", v.get_id(), v.get_element());
			}
			
		private:
			vertex_id_t id_;
			T elem_;
	};

}