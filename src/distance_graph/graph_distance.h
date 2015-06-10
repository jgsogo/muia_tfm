
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
                ~base_graph();

                //! Lower bound for the distance between two graphs
                virtual float lower_bound(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const;
                //! Upper bound for the distance between two graphs
                virtual float upper_bound(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const;

                //! Compute max_similarity between two conceptual_graphs (tolerances must belong to [0, 1])
                virtual float max_similarity(const conceptual_graph& s1, const conceptual_graph& s2, float synset_tolerance, float relation_tolerance) const = 0;

        protected:
                const base_synset& dist_synset;
                const base_relation& dist_relation;
        };

    }
}
