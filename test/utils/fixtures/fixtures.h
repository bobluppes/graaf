#pragma once

namespace graaf::utils::fixtures
{

/**
 * 1. Minimal weighted graph types
 */
using minimal_graph_types =
    testing::Types<directed_graph<int, int>, undirected_graph<int, int>>;

using minimal_directed_graph_type   = testing::Types<directed_graph<int, int>>;

using minimal_undirected_graph_type = testing::Types<undirected_graph<int, int>>;

/**
 * 2. More detailed weighted graph types
 */
template<typename T>
class my_weighted_edge : public weighted_edge<T>
{
  public:
    explicit my_weighted_edge(T weight)
        : weight_ {weight}
    {}

    [[nodiscard]]
    T get_weight() const noexcept override
    {
        return weight_;
    }

  private:
    T weight_ {};
};

using weighted_graph_types = testing::Types<

    /**
     * Primitive edge type directed graph
     */
    std::pair<directed_graph<int, int>, int>,
    std::pair<directed_graph<int, unsigned long>, unsigned long>,
    std::pair<directed_graph<int, float>, float>,
    std::pair<directed_graph<int, long double>, long double>,

    /**
     * Non primitive weighted edge type directed graph
     */

    std::pair<directed_graph<int, my_weighted_edge<int>>, my_weighted_edge<int>>,
    std::pair<directed_graph<int, my_weighted_edge<unsigned long>>,
              my_weighted_edge<unsigned long>>,
    std::pair<directed_graph<int, my_weighted_edge<float>>, my_weighted_edge<float>>,
    std::pair<directed_graph<int, my_weighted_edge<long double>>,
              my_weighted_edge<long double>>,

    /**
     * Primitive edge type undirected graph
     */
    std::pair<undirected_graph<int, int>, int>,
    std::pair<undirected_graph<int, unsigned long>, unsigned long>,
    std::pair<undirected_graph<int, float>, float>,
    std::pair<undirected_graph<int, long double>, long double>,

    /**
     * Non primitive weighted edge type undirected graph
     */
    std::pair<undirected_graph<int, my_weighted_edge<int>>, my_weighted_edge<int>>,
    std::pair<undirected_graph<int, my_weighted_edge<unsigned long>>,
              my_weighted_edge<unsigned long>>,
    std::pair<undirected_graph<int, my_weighted_edge<float>>, my_weighted_edge<float>>,
    std::pair<undirected_graph<int, my_weighted_edge<long double>>,
              my_weighted_edge<long double>>>;

using weighted_graph_signed_types = testing::Types<

    /**
     * Primitive edge type directed graph
     */
    std::pair<directed_graph<int, int>, int>,
    std::pair<directed_graph<int, float>, float>,
    std::pair<directed_graph<int, long double>, long double>,

    /**
     * Non primitive weighted edge type directed graph
     */

    std::pair<directed_graph<int, my_weighted_edge<int>>, my_weighted_edge<int>>,
    std::pair<directed_graph<int, my_weighted_edge<float>>, my_weighted_edge<float>>,
    std::pair<directed_graph<int, my_weighted_edge<long double>>,
              my_weighted_edge<long double>>,

    /**
     * Primitive edge type undirected graph
     */
    std::pair<undirected_graph<int, int>, int>,
    std::pair<undirected_graph<int, float>, float>,
    std::pair<undirected_graph<int, long double>, long double>,

    /**
     * Non primitive weighted edge type undirected graph
     */
    std::pair<undirected_graph<int, my_weighted_edge<int>>, my_weighted_edge<int>>,
    std::pair<undirected_graph<int, my_weighted_edge<float>>, my_weighted_edge<float>>,
    std::pair<undirected_graph<int, my_weighted_edge<long double>>,
              my_weighted_edge<long double>>>;

using directed_weighted_graph_types = testing::Types<

    /**
     * Primitive edge type directed graph
     */
    std::pair<directed_graph<int, int>, int>,
    std::pair<directed_graph<int, unsigned long>, unsigned long>,
    std::pair<directed_graph<int, float>, float>,
    std::pair<directed_graph<int, long double>, long double>,

    /**
     * Non primitive weighted edge type directed graph
     */

    std::pair<directed_graph<int, utils::fixtures::my_weighted_edge<int>>,
              utils::fixtures::my_weighted_edge<int>>,
    std::pair<directed_graph<int, utils::fixtures::my_weighted_edge<unsigned long>>,
              utils::fixtures::my_weighted_edge<unsigned long>>,
    std::pair<directed_graph<int, utils::fixtures::my_weighted_edge<float>>,
              utils::fixtures::my_weighted_edge<float>>,
    std::pair<directed_graph<int, utils::fixtures::my_weighted_edge<long double>>,
              utils::fixtures::my_weighted_edge<long double>>>;

using directed_weighted_graph_signed_types = testing::Types<
    /**
     * Primitive edge type directed graph
     */
    std::pair<directed_graph<int, int>, int>,
    std::pair<directed_graph<int, float>, float>,
    std::pair<directed_graph<int, long double>, long double>,

    /**
     * Non primitive weighted edge type directed graph
     */
    std::pair<directed_graph<int, my_weighted_edge<int>>, my_weighted_edge<int>>,
    std::pair<directed_graph<int, my_weighted_edge<float>>, my_weighted_edge<float>>,
    std::pair<directed_graph<int, my_weighted_edge<long double>>,
              my_weighted_edge<long double>>>;

/**
 * 3. Unit-weighted graph types
 * We do not inherit from weighted_edge, nor do we use an arithmetic type, such
 * that each edge has a unit weight.
 */
template<typename T>
class my_unit_weighted_edge
{};

using unit_weighted_graph_types = testing::Types<

    /**
     * Unit weighted edge type directed graph
     */
    std::pair<directed_graph<int, my_unit_weighted_edge<bool>>,
              my_unit_weighted_edge<bool>>,
    std::pair<directed_graph<int, my_unit_weighted_edge<int>>,
              my_unit_weighted_edge<int>>,
    std::pair<directed_graph<int, my_unit_weighted_edge<unsigned long>>,
              my_unit_weighted_edge<unsigned long>>,
    std::pair<directed_graph<int, my_unit_weighted_edge<float>>,
              my_unit_weighted_edge<float>>,
    std::pair<directed_graph<int, my_unit_weighted_edge<long double>>,
              my_unit_weighted_edge<long double>>,

    /**
     * Unit weighted edge type undirected graph
     */
    std::pair<undirected_graph<int, my_unit_weighted_edge<bool>>,
              my_unit_weighted_edge<bool>>,
    std::pair<undirected_graph<int, my_unit_weighted_edge<int>>,
              my_unit_weighted_edge<int>>,
    std::pair<undirected_graph<int, my_unit_weighted_edge<unsigned long>>,
              my_unit_weighted_edge<unsigned long>>,
    std::pair<undirected_graph<int, my_unit_weighted_edge<float>>,
              my_unit_weighted_edge<float>>,
    std::pair<undirected_graph<int, my_unit_weighted_edge<long double>>,
              my_unit_weighted_edge<long double>>>;

/**
 * 4. Unweighted graph types
 * We do not derive from weighted edge, so we do not have the default provided
 * get_weight method.
 */
template<typename T>
struct my_unweighted_edge
{
    using weight_t = T;
    T val {};
};

using unweighted_graph_types = testing::Types<

    /**
     * Unweighted edge type directed graph
     */
    std::pair<directed_graph<int, my_unweighted_edge<int>>, my_unweighted_edge<int>>,
    std::pair<directed_graph<int, my_unweighted_edge<unsigned long>>,
              my_unweighted_edge<unsigned long>>,
    std::pair<directed_graph<int, my_unweighted_edge<float>>, my_unweighted_edge<float>>,
    std::pair<directed_graph<int, my_unweighted_edge<long double>>,
              my_unweighted_edge<long double>>,

    /**
     * Unweighted edge type undirected graph
     */
    std::pair<undirected_graph<int, my_unweighted_edge<int>>, my_unweighted_edge<int>>,
    std::pair<undirected_graph<int, my_unweighted_edge<unsigned long>>,
              my_unweighted_edge<unsigned long>>,
    std::pair<undirected_graph<int, my_unweighted_edge<float>>,
              my_unweighted_edge<float>>,
    std::pair<undirected_graph<int, my_unweighted_edge<long double>>,
              my_unweighted_edge<long double>>>;

} // namespace graaf::utils::fixtures
