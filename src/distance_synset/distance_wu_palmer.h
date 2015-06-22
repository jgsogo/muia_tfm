
#pragma once 

#include "depth_relative.h"

namespace wn {
    namespace distance {

        /*!

            Wu and Palmer distance (cited in [Budanitsky2006])
        */
        class WN_DISTANCE_SYNSET_EXPORT wu_palmer : public depth_relative {
            public:
                wu_palmer(const hyperonym_graph& graph);
                ~wu_palmer();

                virtual float operator()(const synset& s1, const synset& s2) const;
                virtual float similarity(const synset& s1, const synset& s2) const;

                float similarity_exact(const synset& s1, const synset& s2) const;
            protected:

        };
        typedef distance::wu_palmer distance_wu_palmer;
    }
}
