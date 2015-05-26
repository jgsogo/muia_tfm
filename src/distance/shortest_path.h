
#pragma once

#include "distance.h"
#include "../wordnet/wordnet.h"

namespace wn {
    namespace distance {

        /*! Semantic distance based only in hypernymy and hyponymy.

            Rada, R., Mili, H., Bicknell, E., & Blettner, M. (1989). Development and application
            of a metric on semantic nets. IEEE Transactions on Systems, Man, and Cybernetics, 19(1), 17–30.
            http://doi.org/10.1109/21.24528
        */
        class WN_DISTANCE_EXPORT shortest_path : public base {
            public:
                shortest_path(const wordnet& wnet);
                virtual float operator()(const synset& s1, const synset& s2) const;
                virtual float max() const;
            protected:
                std::size_t max_depth;
                const wordnet& wnet;
        };

        typedef distance::shortest_path distance_shortest_path;

    }
}
