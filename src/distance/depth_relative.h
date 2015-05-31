
#pragma once

#include "distance.h"
#include "../wordnet/hyperonym_graph.h"

namespace wn {
    namespace distance {
        /*! Depth relative distance: sibling concepts deep in a taxonomy appear to be
            more closely related to one another than those higher up.
        */
        class WN_DISTANCE_EXPORT depth_relative : public base_synset {
            public:
                depth_relative(const hyperonym_graph& graph);
                ~depth_relative();
                virtual float operator()(const synset& s1, const synset& s2) const = 0;
                virtual float max() const = 0;

            protected:
                const hyperonym_graph& graph;

        };
    }
}
