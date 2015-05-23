
#pragma once

#include "distance.h"

namespace wn {
    /*! Depth relative distance: sibling concepts deep in a taxonomy appear to be
        more closely related to one another than those higher up.

        Sussna, M. (1993). Word sense disambiguation for free-text indexing using
        a massive semantic network. In Proceedings of the second international
        conference on Information and knowledge management - CIKM ’93 (pp. 67–74).
        New York, New York, USA: ACM Press. http://doi.org/10.1145/170088.170106
    */
    class WN_DISTANCE_EXPORT depth_relative : public distance {
        public:
            depth_relative(const wnb::wordnet& wordnet);
            ~depth_relative();
			virtual float operator()(const wnb::synset& s1, const wnb::synset& s2) const;
			virtual float max() const;

            float edge_weight(const wnb::synset& child, const wnb::synset& parent) const;

        protected:
            static const std::pair<float, float> minmax_hyperonym_r;
            static const std::pair<float, float> minmax_hyponym_r;
            struct data;
            data* d;
    };
}
