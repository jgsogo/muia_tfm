
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
                virtual float min_distance(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const = 0;

                virtual float min(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const;
                virtual float max(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const;

                virtual float max_edge_distance() const = 0;
            protected:
                const base& dist;
        };

    }
}
