#pragma once

#include <graaflib/graph.h>

namespace graaf {

    template <typename T, typename T_HASH>
    class directed_graph : public graph<T, T_HASH> {

    };

}