
#pragma once

#include "graph_distance.h"

namespace wn {
    namespace distance {

        class WN_GRAPH_DISTANCE_EXPORT mine : public graph_base {
            public:
                mine(const base_synset& base_distance);

                //! Compute minimum distance between two conceptual_graphs
                virtual float min_distance(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const;

                // Compute minimum distance between two relation sets
                virtual float min_distance(const std::vector<relation>& rel1, const std::vector<relation>& rel2, float edge_penalization) const;

                // Distance between two relations
                virtual float operator()(const relation&, const relation&) const;

                float max_edge_distance() const;
        };
        typedef distance::mine distance_mine;
    }
}
