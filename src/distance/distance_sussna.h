
#include "depth_relative.h"

namespace wn {
    namespace distance {

        /*!

            Sussna, M. (1993). Word sense disambiguation for free-text indexing using
            a massive semantic network. In Proceedings of the second international
            conference on Information and knowledge management - CIKM ’93 (pp. 67–74).
            New York, New York, USA: ACM Press. http://doi.org/10.1145/170088.170106
        */
        class WN_DISTANCE_EXPORT sussna : public depth_relative {
            public:
                sussna(const hyperonym_graph& graph);
                ~sussna();
                virtual float operator()(const synset& s1, const synset& s2) const;
                virtual float max() const;

                float edge_weight(const synset& child, const synset& parent) const;

            protected:
                static const std::pair<float, float> minmax_hyperonym_r;
                static const std::pair<float, float> minmax_hyponym_r;

        };
        typedef distance::sussna distance_sussna;
    }
}
