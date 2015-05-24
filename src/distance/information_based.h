
#pragma once

#include "distance.h"
#include "../wordnet/hyperonym_graph.h"
#include "../corpus/corpus.h"

namespace wn {
    namespace distance {
        /*! Depth relative distance: sibling concepts deep in a taxonomy appear to be
            more closely related to one another than those higher up.
        */
        class WN_DISTANCE_EXPORT information_based : public base {
            public:
                information_based(const hyperonym_graph& graph, const corpus& corpus);
                ~information_based();
                virtual float operator()(const wnb::synset& s1, const wnb::synset& s2) const = 0;
                virtual float max() const = 0;

            protected:
                const hyperonym_graph& graph;
                const wn::corpus& corpus;

        };
    }
}
