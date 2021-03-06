
#pragma once

#include "information_based.h"

namespace wn {
    namespace distance {
        /*!

            Jiang, J. J., & Conrath, D. W. (1997). Semantic Similarity Based on Corpus Statistics
            and Lexical Taxonomy. In Proceedings of International Conference Research on Computational
            Linguistics (p. 15). Taiwan. doi:10.1.1.269.3598
        */
        class WN_DISTANCE_SYNSET_EXPORT jiang_conrath : public information_based {
            public:
                jiang_conrath(const hyperonym_graph& graph, const wn::corpus& corpus_);
                jiang_conrath(const hyperonym_graph& graph,
                    const std::map<synset, std::size_t>& concept_count,
                    std::size_t all_count,
                    std::size_t max_count);
                ~jiang_conrath();

                virtual float operator()(const synset& s1, const synset& s2) const;
                virtual float similarity(const synset& s1, const synset& s2) const;

            protected:
                float max_distance() const;
        };
        typedef distance::jiang_conrath distance_jiang_conrath;
    }
}
