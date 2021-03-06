
#pragma once

#include "distance.h"
#include "../wordnet/hyperonym_graph.h"
#include "../corpus/corpus.h"

namespace wn {
    namespace distance {
        /*! Depth relative distance: sibling concepts deep in a taxonomy appear to be
            more closely related to one another than those higher up.
        */
        class WN_DISTANCE_SYNSET_EXPORT information_based : public base_synset {
            public:
                information_based(const hyperonym_graph& graph, const corpus& corpus_);
                information_based(  const hyperonym_graph& graph, 
                                    const std::map<synset, std::size_t>& concept_count, 
                                    std::size_t all_count,
                                    std::size_t max_count);
                ~information_based();

                virtual float operator()(const synset& s1, const synset& s2) const = 0;
                virtual float similarity(const synset& s1, const synset& s2) const = 0;

            protected:
                const hyperonym_graph& graph;
                
                std::map<synset, std::size_t> concept_count;
                std::size_t all_count;
                std::size_t max_count;

        };
    }
}
