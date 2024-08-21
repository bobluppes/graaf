#include <benchmark/benchmark.h>
#include <graaflib/algorithm/clique_detection/bron_kerbosch.h>
#include <graaflib/graph.h>

#include <random>
#include <vector>

namespace
{
// Generating random number of vertices (1- 30) for a clique
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> random_clique_size(1, 30);

template<typename EDGE_T>
[[nodiscard]]
std::vector<graaf::vertex_id_t> create_vertices(
    graaf::undirected_graph<int, EDGE_T>& graph,
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

template<typename EDGE_T>
void add_clique(graaf::undirected_graph<int, EDGE_T>& graph,
                std::vector<graaf::vertex_id_t> const& vertices,
                size_t start_vertex,
                size_t clique_size)
{
    // We are in range of vector of vertices
    size_t end_vertex = std::min(start_vertex + clique_size, vertices.size());

    // Constructing a clique
    for(size_t i {start_vertex}; i < end_vertex; ++i)
    {
        for(size_t j {i + 1}; j < end_vertex; ++j)
        {
            graph.add_edge(vertices[i], vertices[j], 1);
        }
    }
}
} // namespace

static void bron_kerbosh_cliques(benchmark::State& state)
{
    auto const number_of_edges {static_cast<size_t>(state.range(0))};

    graaf::undirected_graph<int, int> graph {};

    // We create enough vertices to construct the requested number of edges
    auto const number_of_vertices {number_of_edges + 1};
    auto const vertices {create_vertices(graph, number_of_vertices)};
    auto const clique_size = static_cast<size_t>(state.range(1));

    for(size_t i {0}; i < number_of_edges; i += clique_size)
    {
        add_clique(graph, vertices, i, clique_size);
    }

    for(auto _: state)
    {
        auto result = graaf::algorithm::bron_kerbosch(graph);
        benchmark::DoNotOptimize(result);
    }

    state.SetComplexityN(state.range(1));
}

static void bron_kerbosh_connected_cliques(benchmark::State& state)
{
    auto const number_of_edges {static_cast<size_t>(state.range(0))};

    graaf::undirected_graph<int, int> graph {};

    // We create enough vertices to construct the requested number of edges
    auto const number_of_vertices {number_of_edges + 1};
    auto const vertices {create_vertices(graph, number_of_vertices)};
    auto const clique_size = static_cast<size_t>(state.range(1));

    // Connecting all cliques
    for(size_t i {0}; i + clique_size < number_of_edges; i += clique_size)
    {
        graph.add_edge(vertices[i], vertices[i + clique_size], 1);
    }

    for(size_t i {0}; i < number_of_edges; i += clique_size)
    {
        add_clique(graph, vertices, i, clique_size);
    }

    for(auto _: state)
    {
        auto result = graaf::algorithm::bron_kerbosch(graph);
        benchmark::DoNotOptimize(result);
    }

    state.SetComplexityN(state.range(1));
}

static void bron_kerbosh_random_cliques(benchmark::State& state)
{
    auto const number_of_edges {static_cast<size_t>(state.range(0))};

    graaf::undirected_graph<int, int> graph {};

    // We create enough vertices to construct the requested number of edges
    auto const number_of_vertices {number_of_edges + 1};
    auto const vertices {create_vertices(graph, number_of_vertices)};
    size_t clique_size = random_clique_size(rng);

    for(size_t i {0}; i + clique_size < number_of_edges; i += clique_size)
    {
        add_clique(graph, vertices, i, clique_size++);
        clique_size = random_clique_size(rng);
    }

    for(auto _: state)
    {
        auto result = graaf::algorithm::bron_kerbosch(graph);
        benchmark::DoNotOptimize(result);
    }

    state.SetComplexityN(state.range(0));
}

static void bron_kerbosh_connected_random_cliques(benchmark::State& state)
{
    auto const number_of_edges {static_cast<size_t>(state.range(0))};

    graaf::undirected_graph<int, int> graph {};

    // We create enough vertices to construct the requested number of edges
    auto const number_of_vertices {number_of_edges + 1};
    auto const vertices {create_vertices(graph, number_of_vertices)};
    size_t clique_size = random_clique_size(rng);

    // Connecting all cliques
    for(size_t i {0}; i < number_of_edges; ++i)
    {
        graph.add_edge(vertices[i], vertices[i + 1], 1);
    }

    for(size_t i {0}; i + clique_size < number_of_edges; i += clique_size)
    {
        add_clique(graph, vertices, i, clique_size++);
        clique_size = random_clique_size(rng);
    }

    for(auto _: state)
    {
        auto result = graaf::algorithm::bron_kerbosch(graph);
        benchmark::DoNotOptimize(result);
    }

    state.SetComplexityN(state.range(0));
}

BENCHMARK(bron_kerbosh_cliques)
    ->Ranges({
        {100, 10000},
        {  2,    32}
}) /* clique size 2 ^ n */
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(bron_kerbosh_connected_cliques)
    ->Ranges({
        {100, 10000},
        {  2,    32}
}) /* clique size 2 ^ n */
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(bron_kerbosh_cliques)
    ->Ranges({
        { 100, 1000},
        {1000, 1000}
}) /* Dense graph, number of vertices are
                                                                  min(state.range(1),
                          vertex.size()) */
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(bron_kerbosh_cliques)
    ->Ranges({
        {100, 10000},
        { 10,    60}
}) /* large cliques */
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(bron_kerbosh_connected_cliques)
    ->Ranges({
        {100, 10000},
        { 10,    60}
}) /* large cliques */
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(bron_kerbosh_random_cliques) /* random clique size between 1-30 */
    ->Range(100, 10000)
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
BENCHMARK(bron_kerbosh_connected_random_cliques) /* random clique size between 1-30 */
    ->Range(100, 10000)
    ->Unit(benchmark::kMillisecond)
    ->Complexity();
