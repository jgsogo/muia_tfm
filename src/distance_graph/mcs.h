
#pragma once

#include "graph_distance.h"

namespace wn {
    namespace distance {

        class WN_DISTANCE_GRAPH_EXPORT mcs : public base_graph {
            public:
                mcs(const base_synset& base_distance, const base_relation& dist_relation);
                ~mcs();

                //! Compute minimum distance between two conceptual_graphs
                virtual float min_distance(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const;

        };

    }
}
