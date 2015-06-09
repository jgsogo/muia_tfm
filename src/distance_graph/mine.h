
#pragma once

#include "graph_distance.h"

namespace wn {
    namespace distance {

        class WN_DISTANCE_GRAPH_EXPORT mine : public base_graph {
            public:
                mine(const base_synset& base_distance, const base_relation& dist_relation);

                //! Compute minimum distance between two conceptual_graphs
                virtual float max_similarity(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const;

        };
        typedef distance::mine distance_mine;
    }
}
