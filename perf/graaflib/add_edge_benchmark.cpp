#include <benchmark/benchmark.h>
#include <graaflib/graph.h>

#include <vector>

namespace
{

template<typename EDGE_T>
[[nodiscard]]
std::vector<graaf::vertex_id_t> create_vertices(graaf::directed_graph<int, EDGE_T>& graph,
                                                size_t n)
{
    std::vector<graaf::vertex_id_t> vertices {};
    vertices.reserve(n);

    for(size_t i {0}; i < n; ++i)
    {
        vertices.push_back(graph.add_vertex(i));
    }

    return vertices;
}

static void bm_add_primitive_numeric_edge(benchmark::State& state)
{
    auto const number_of_edges {static_cast<size_t>(state.range(0))};

    graaf::directed_graph<int, int> graph {};

    // We create enough vertices to construct the requested number of edges
    auto const number_of_vertices {number_of_edges + 1};
    auto const vertices {create_vertices(graph, number_of_vertices)};

    for(auto _: state)
    {
        for(size_t i {0}; i < number_of_edges; ++i)
        {
            graph.add_edge(vertices[i], vertices[i + 1], i);
        }
    }
}

struct edge
{
    // Something which benefits from move construction
    std::vector<double> data {100};
};

static void bm_add_user_defined_edge(benchmark::State& state)
{
    auto const number_of_edges {static_cast<size_t>(state.range(0))};

    graaf::directed_graph<int, edge> graph {};

    // We create enough vertices to construct the requested number of edges
    auto const number_of_vertices {number_of_edges + 1};
    auto const vertices {create_vertices(graph, number_of_vertices)};

    for(auto _: state)
    {
        for(size_t i {0}; i < number_of_edges; ++i)
        {
            graph.add_edge(vertices[i], vertices[i + 1], edge {});
        }
    }
}

} // namespace

// Register the benchmarks
BENCHMARK(bm_add_primitive_numeric_edge)->Range(1'000, 10'000);
BENCHMARK(bm_add_user_defined_edge)->Range(1'000, 10'000);
