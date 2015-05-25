
#include "depth_relative.h"

namespace wn {
    namespace distance {

        /*!

            Wu and Palmer distance (cited in [Budanitsky2006])
        */
        class WN_DISTANCE_EXPORT wu_palmer : public depth_relative {
            public:
                wu_palmer(const hyperonym_graph& graph);
                ~wu_palmer();
                virtual float operator()(const wnb::synset& s1, const wnb::synset& s2) const;
                virtual float max() const;

            protected:

        };
        typedef distance::wu_palmer distance_wu_palmer;
    }
}