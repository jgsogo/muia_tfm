
#pragma once

#include "distance_graph/wn_distance_graph_export.h"
#include "../conceptual_graph/conceptual_graph.h"
#include "../distance_synset/distance.h"
#include "../distance_relation/distance_relation.h"

namespace wn {
    namespace distance {

        class WN_DISTANCE_GRAPH_EXPORT base_graph {
            public:
                base_graph(const base_synset& base_distance, const base_relation& dist_relation);

                //! Lower bound for the distance between two graphs
                virtual float lower_bound(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const;
                //! Upper bound for the distance between two graphs
                virtual float upper_bound(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const;

                //! Compute minimum distance between two conceptual_graphs
                virtual float min_distance(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const = 0;

        protected:
                const base_synset& dist_synset;
                const base_relation& dist_relation;
        };

    }
}
