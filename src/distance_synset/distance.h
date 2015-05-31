
#pragma once

#include "../wordnet/synset.h"
#include "distance_synset/wn_distance_synset_export.h"

namespace wn {
    namespace distance {

        class WN_DISTANCE_SYNSET_EXPORT base_synset {
            public:
                static const float max_distance; //! max_distance to consider synsets connected

            public:
                base_synset();
                virtual float min() const; //! min distance by default is 0
                virtual float max() const; //! max distance between two synsets (by default is '''distance::max_distance''');
                virtual float operator()(const synset& s1, const synset& s2) const = 0;
                virtual bool connected(const synset& s1, const synset& s2) const;

                typedef std::vector<std::tuple<synset, synset, float>> _t_distance;
                virtual float min_distance(const std::vector<synset>& v1, const std::vector<synset>& v2, std::vector<_t_distance>& dist_combs) const;
                virtual float min_distance(const std::vector<synset>& v1, const std::vector<synset>& v2, std::vector<_t_distance>& dist_combs, float penalization) const;

                //! Max and min values for the distance between two synset sets.
                virtual float min(const std::vector<synset>& v1, const std::vector<synset>& v2, float penalization) const;
                virtual float max(const std::vector<synset>& v1, const std::vector<synset>& v2, float penalization) const;
            protected:
        };

    }
}

