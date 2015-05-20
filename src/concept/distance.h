
#pragma once

#include "synset.h"
#include "wnb/core/wordnet.hh"
#include "wnb/nltk_similarity.hh"

struct distance {
    //! shortest path distance
    float shortest_path(const wnb::wordnet& wn, const synset& s1, const synset& s2) {
        wnb::nltk_similarity sim(wn);
        return sim.shortest_path_distance(s1, s2);
    }

    //! other distance meassure
};

