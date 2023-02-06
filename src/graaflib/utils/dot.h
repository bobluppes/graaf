#pragma once

#include <fmt/core.h>
#include <fmt/ostream.h>

#include <graaflib/graph.h>

namespace graaf::utils {

    template <typename T, typename EDGE>
    [[nodiscard]] std::string to_dot(const graph<T, EDGE>& graph) {
        std::string dot_string{fmt::format("{} {{", graph.get_graph_type())};
        for (const auto& vertex : graph.vertices()) {
            dot_string += fmt::format("\n\t{} [label=\"{}\"];", vertex.get_id(), vertex.get_element());
        }
        for (const auto& edge : graph.edges()) {
            dot_string += fmt::format("\n\t{};", edge);
        }
        dot_string += "\n}";

        return dot_string;
    }

}