
#pragma once

#include "graph_distance.h"

namespace wn {
    namespace distance {

        class WN_GRAPH_DISTANCE_EXPORT mine : public graph_base {
            public:
                mine(const base& base_distance);
                virtual float operator()(const conceptual_graph& s1, const conceptual_graph& s2) const;
                virtual float operator()(const conceptual_graph& s1,
                                         const std::vector<conceptual_graph::synset_id>& s1_synsets,
                                         const conceptual_graph& s2,
                                         const std::vector<conceptual_graph::synset_id>& s1_synsets) const;
        };
        typedef distance::mine distance_mine;
    }
}
