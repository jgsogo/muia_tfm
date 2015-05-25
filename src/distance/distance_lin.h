
#pragma once

#include "information_based.h"

namespace wn {
    namespace distance {
        /*!

            
        */
        class WN_DISTANCE_EXPORT lin : public information_based {
            public:
                lin(const hyperonym_graph& graph, const wn::corpus& corpus);
                ~lin();
                virtual float operator()(const wnb::synset& s1, const wnb::synset& s2) const;
                virtual float max() const;

            protected:
                std::map<wnb::synset, std::size_t> concept_count;
                std::size_t all_count;
        };
        typedef distance::lin distance_lin;
    }
}
