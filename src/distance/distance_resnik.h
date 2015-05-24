
#pragma once

#include "information_based.h"

namespace wn {
    namespace distance {
        /*!

            Resnik, P. (1995). Using Information Content to Evaluate Semantic Similarity
            in a Taxonomy. In Proceedings of the 14th International Joint Conference on
            Artificial Intelligence (pp. 448–453). Retrieved from
            http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.55.5277
        */
        class WN_DISTANCE_EXPORT resnik : public information_based {
            public:
                resnik(const hyperonym_graph& graph, const wn::corpus& corpus);
                ~resnik();
                virtual float operator()(const wnb::synset& s1, const wnb::synset& s2) const;
                virtual float max() const;

            protected:
                std::map<wnb::synset, std::size_t> concept_count;
                std::size_t all_count;
        };
        typedef distance::resnik distance_resnik;
    }
}
