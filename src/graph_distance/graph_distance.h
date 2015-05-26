
#pragma once

#include "graph_distance/wn_graph_distance_export.h"
#include "../conceptual_graph/conceptual_graph.h"
#include "../distance/distance.h"

namespace wn {
    namespace distance {

        class WN_GRAPH_DISTANCE_EXPORT graph_base {
            public:
                graph_base(const base& base_distance);

                //! Compute minimum distance between two conceptual_graphs
                virtual float min_distance(const conceptual_graph& s1, const conceptual_graph& s2) const = 0;

            protected:
                const base& dist;
        };

    }
}
