
#pragma once

#include "graph_distance.h"

namespace wn {
    namespace distance {

        class WN_DISTANCE_GRAPH_EXPORT mcs : public base_graph {
            public:
                mcs(const base_synset& base_distance, const base_relation& dist_relation);
                ~mcs();

                //! Compute max_similarity between two conceptual_graphs (tolerances must belong to [0, 1))
                virtual float max_similarity(const conceptual_graph& s1, const conceptual_graph& s2,
                                            float synset_tolerance, float relation_tolerance,
                                            conceptual_graph& result,
                                            conceptual_graph_corresponde& s1_to_result,
                                            conceptual_graph_corresponde& s2_to_result) const;
        };

    }
}
