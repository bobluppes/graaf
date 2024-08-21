#pragma once

#include <graaflib/types.h>

namespace graaf::algorithm
{

namespace detail
{

    /**
     * An edge callback which does nothing.
     */
    struct noop_callback
    {
        void operator()(edge_id_t const& /*edge*/) const
        {}
    };

    /*
     * A unary predicate which always returns false, effectively resulting in an
     * exhaustive search.
     */
    struct exhaustive_search_strategy
    {
        [[nodiscard]]
        bool operator()(vertex_id_t const /*vertex*/) const
        {
            return false;
        }
    };

} // namespace detail

} // namespace graaf::algorithm
