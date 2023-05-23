#pragma once

#include <algorithm>
#include <initializer_list>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include <fmt/core.h>

#include <graaflib/types.h>

namespace graaf {

	enum class GRAPH_SPEC {DIRECTED, UNDIRECTED};

	template <typename VERTEX_T, typename EDGE_T, GRAPH_SPEC GRAPH_SPEC_V>
	class graph {
		public:
			using vertex_t = VERTEX_T;
			using edge_t = EDGE_T;

			using vertex_ids_t = std::pair<vertex_id_t, vertex_id_t>;

			using vertices_t = std::unordered_set<vertex_id_t>;

			[[nodiscard]] constexpr bool is_directed() const { return GRAPH_SPEC_V == GRAPH_SPEC::DIRECTED; }
			[[nodiscard]] constexpr bool is_undirected() const { return GRAPH_SPEC_V == GRAPH_SPEC::UNDIRECTED; }

			/**
			 * STATISTICS
			*/
			[[nodiscard]] std::size_t vertex_count() const noexcept { return vertices_.size(); }
			[[nodiscard]] std::size_t edge_count() const noexcept { return edges_.size(); }

			/**
			 * GETTERS
			*/
			[[nodiscard]] bool has_vertex(vertex_id_t vertex_id) const noexcept {
				return vertices_.contains(vertex_id);
			}
			[[nodiscard]] bool has_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) const noexcept { 
				return do_has_edge(vertex_id_lhs, vertex_id_rhs);
			 }

			[[nodiscard]] vertex_t& get_vertex(vertex_id_t vertex_id) {
				if (!has_vertex(vertex_id)) {
					throw std::out_of_range{fmt::format("Vertex with ID [{}] not found in graph.", vertex_id)};
				}
				return vertices_.at(vertex_id);
			}
			[[nodiscard]] const vertex_t& get_vertex(vertex_id_t vertex_id) const {
				return get_vertex(vertex_id);
			}

			[[nodiscard]] edge_t& get_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) { 
				if (!has_edge(vertex_id_lhs, vertex_id_rhs)) {
					throw std::out_of_range{fmt::format("No edge found between vertices [{}] -> [{}].", vertex_id_lhs, vertex_id_rhs)};
				}
				return do_get_edge(vertex_id_lhs, vertex_id_rhs);
			 }
			[[nodiscard]] const edge_t& get_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) const {
				return get_edge(vertex_id_lhs, vertex_id_rhs);
			}

			[[nodiscard]] vertices_t get_neighbors(vertex_id_t vertex_id) const {
				if (!adjacency_list_.contains(vertex_id)) {
					return {};
				}
				
				return adjacency_list_.at(vertex_id);
			}

			/**
			 * SETTERS
			*/
			vertex_id_t add_vertex(VERTEX_T vertex) {
				// TODO: check overflow
				const auto vertex_id{vertex_id_supplier_++};
				vertices_.emplace(vertex_id, std::move(vertex));
				return vertex_id;
			}

			void remove_vertex(vertex_id_t vertex_id) {

				if (adjacency_list_.contains(vertex_id)) {
					for (auto& target_vertex_id : adjacency_list_.at(vertex_id)) {
						edges_.erase({vertex_id, target_vertex_id});
					}
				}

				adjacency_list_.erase(vertex_id);
				vertices_.erase(vertex_id);

				for (auto& [source_vertex_id, neighbors] : adjacency_list_) {
					neighbors.erase(vertex_id);
					edges_.erase({source_vertex_id, vertex_id});
				}
			}

			void add_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs, EDGE_T edge) {
				if (!has_vertex(vertex_id_lhs) || !has_vertex(vertex_id_rhs)) {
					throw std::out_of_range{fmt::format("Vertices with ID [{}] and [{}] not found in graph.", vertex_id_lhs, vertex_id_rhs)};
				}
				do_add_edge(vertex_id_lhs, vertex_id_rhs, std::move(edge));
			}

			vertex_ids_t add_edge(VERTEX_T vertex_lhs, VERTEX_T vertex_rhs, EDGE_T edge) {
				const auto vertex_id_lhs{add_vertex(std::move(vertex_lhs))};
				const auto vertex_id_rhs{add_vertex(std::move(vertex_rhs))};
				add_edge(vertex_id_lhs, vertex_id_rhs, std::move(edge));
				return {vertex_id_lhs, vertex_id_rhs};
			}

			void remove_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) { do_remove_edge(vertex_id_lhs, vertex_id_rhs); }

		protected:
			struct vertex_ids_hash {
				[[nodiscard]] std::size_t operator()(const vertex_ids_t& key) const {
					const auto h1{std::hash<vertex_id_t>{}(key.first)};
					const auto h2{std::hash<vertex_id_t>{}(key.second)};
					
					// TODO: use something like boost::hash_combine
					return h1 ^ h2;
				}
			};

			using vertex_id_to_vertex_t = std::unordered_map<vertex_id_t, vertex_t>;
			using vertex_ids_to_edge_t = std::unordered_map<vertex_ids_t, edge_t, vertex_ids_hash>;

			std::unordered_map<vertex_id_t, vertices_t> adjacency_list_{};

			vertex_id_to_vertex_t vertices_{};
			vertex_ids_to_edge_t edges_{};


		private:
			[[nodiscard]] virtual bool do_has_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) const noexcept = 0;
			[[nodiscard]] virtual edge_t& do_get_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) = 0;
			virtual void do_add_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs, EDGE_T edge) = 0;
			virtual void do_remove_edge(vertex_id_t vertex_id_lhs, vertex_id_t vertex_id_rhs) = 0;

			size_t vertex_id_supplier_{0};
		};


}
