
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
        class WN_DISTANCE_SYNSET_EXPORT resnik : public information_based {
            public:
                static void parse_corpus(const hyperonym_graph& graph, const corpus& corpus_, std::map<synset, 
                                         std::size_t>& concept_count, std::size_t& all_count, std::size_t& max_count);

            public:
                resnik(const hyperonym_graph& graph, const wn::corpus& corpus);
                resnik(const hyperonym_graph& graph,
                    const std::map<synset, std::size_t>& concept_count,
                    std::size_t all_count,
                    std::size_t max_count);
                ~resnik();

                virtual float upper_bound() const;
                virtual float operator()(const synset& s1, const synset& s2) const;

            protected:
        };
        typedef distance::resnik distance_resnik;
    }
}
