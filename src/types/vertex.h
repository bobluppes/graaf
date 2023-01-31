#pragma once

namespace graaf::types {

    template <typename T, typename T_HASH>
	class vertex {
		public:
			using element_type = T;
			vertex(std::size_t id, element_type elem) : id_{id}, elem_{std::move(elem)} {}

			std::size_t get_id() const { return id_; }
			const element_type& get_element() const { return elem_; }

			bool operator==(const vertex rhs) const {
					return id_ == rhs.get_id() && elem_ == rhs.get_element();
			}
		private:
			std::size_t id_;
			element_type elem_;
	};


	struct vertex_hash {
		template <typename T, typename T_HASH>
		std::size_t operator()(const vertex<T, T_HASH>& v) const {
			return std::hash<std::size_t>()(v.get_id()) ^ (T_HASH()(v.get_element()) << 1);
		}
	};

}