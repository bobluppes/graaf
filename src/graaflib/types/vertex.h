#pragma once

namespace graaf::types {

	// Strong type for vertex IDs
	using vertex_id_t = std::size_t;

    template <typename T>
	class vertex {
		public:
			vertex(vertex_id_t id, T elem) : id_{id}, elem_{std::move(elem)} {}

			vertex_id_t get_id() const { return id_; }
			const T& get_element() const { return elem_; }

			bool operator==(const vertex rhs) const {
					return id_ == rhs.get_id() && elem_ == rhs.get_element();
			}
		private:
			vertex_id_t id_;
			T elem_;
	};

}