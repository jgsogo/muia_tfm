
#pragma once

#include "information_based.h"

namespace wn {
    namespace distance {
        /*!


        */
        class WN_DISTANCE_SYNSET_EXPORT lin : public information_based {
            public:
                lin(const hyperonym_graph& graph, const wn::corpus& corpus);
                lin(const hyperonym_graph& graph,
                    const std::map<synset, std::size_t>& concept_count,
                    std::size_t all_count,
                    std::size_t max_count);
                ~lin();

                virtual float upper_bound() const;
                virtual float operator()(const synset& s1, const synset& s2) const;
                virtual float similarity(const synset& s1, const synset& s2) const;

                float similarity_exact(const synset& s1, const synset& s2) const;
            protected:
        };
        typedef distance::lin distance_lin;
    }
}
