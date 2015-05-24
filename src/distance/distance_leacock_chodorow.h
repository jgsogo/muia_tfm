
#include "depth_relative.h"

namespace wn {
    namespace distance {

        /*!

            Leacock, C., & Chodorow, M. (1998). Combining Local Context and WordNet
            Similarity for Word Sense Identification. In C. Fellbaum (Ed.),
            WordNet: An Electronic Lexical Database (pp. 265–283). Cambridge,
            Massachusetts: The MIT Press. Retrieved from
            http://www.researchgate.net/publication/200045856_Combining_Local_Context_and_WordNet_Similarity_for_Word_Sense_Identification
        */
        class WN_DISTANCE_EXPORT leacock_chodorow : public depth_relative {
            public:
                leacock_chodorow(const hyperonym_graph& graph);
                ~leacock_chodorow();
                virtual float operator()(const wnb::synset& s1, const wnb::synset& s2) const;
                virtual float max() const;
            protected:

        };
        typedef distance::leacock_chodorow distance_leacock_chodorow;
    }
}
