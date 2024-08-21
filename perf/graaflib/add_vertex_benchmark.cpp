#include <benchmark/benchmark.h>
#include <graaflib/graph.h>

#include <vector>

namespace
{

static void bm_add_primitive_numeric_vertex(benchmark::State& state)
{
    auto const number_of_vertices {static_cast<size_t>(state.range(0))};

    graaf::directed_graph<int, int> graph {};
    for(auto _: state)
    {
        for(size_t i {0}; i < number_of_vertices; ++i)
        {
            [[maybe_unused]]
            auto const vertex_id {graph.add_vertex(i)};
        }
    }
}

struct vertex
{
    // Something which benefits from move construction
    std::vector<double> data {100};
};

static void bm_add_user_defined_vertex(benchmark::State& state)
{
    auto const number_of_vertices {static_cast<size_t>(state.range(0))};

    graaf::directed_graph<vertex, int> graph {};
    for(auto _: state)
    {
        for(size_t i {0}; i < number_of_vertices; ++i)
        {
            [[maybe_unused]]
            auto const vertex_id {graph.add_vertex(vertex {})};
        }
    }
}

} // namespace

// Register the benchmarks
BENCHMARK(bm_add_primitive_numeric_vertex)->Range(1'000, 10'000'000);
BENCHMARK(bm_add_user_defined_vertex)->Range(1'000, 10'000'000);
