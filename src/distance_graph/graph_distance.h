
#pragma once

#include "distance_graph/wn_distance_graph_export.h"
#include "../conceptual_graph/conceptual_graph.h"
#include "../distance_synset/distance.h"

namespace wn {
    namespace distance {

        class WN_DISTANCE_GRAPH_EXPORT base_graph {
            public:
                base_graph(const base_synset& base_distance);

                //! Compute minimum distance between two conceptual_graphs
                virtual float min_distance(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const = 0;

                virtual float min(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const;
                virtual float max(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const;

                virtual float max_edge_distance() const = 0;
            protected:
                const base_synset& dist_synset;
        };

    }
}
