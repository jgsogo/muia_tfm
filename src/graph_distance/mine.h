
#pragma once

#include "graph_distance.h"

namespace wn {
    namespace distance {

        class WN_GRAPH_DISTANCE_EXPORT mine : public graph_base {
            public:
                mine(const base& base_distance);
                // Compute minimum distance between two conceptual_graphs
                virtual float operator()(const conceptual_graph& s1, const conceptual_graph& s2) const;

                // Compute distance between two conceptual_graphs using given order for their nodes
                virtual float operator()(const conceptual_graph& s1,
                                         const std::vector<conceptual_graph::synset_id>& s1_synsets,
                                         const conceptual_graph& s2,
                                         const std::vector<conceptual_graph::synset_id>& s1_synsets) const;



                // Compute minimum distance between two relation sets
                virtual float operator()(const conceptual_graph& s1,
                                         const std::vector<std::pair<relation, synset_id>>& s1_relations,
                                         const conceptual_graph& s2,
                                         const std::vector<std::pair<relation, synset_id>>& s2_synsets) const;

        };
        typedef distance::mine distance_mine;
    }
}
