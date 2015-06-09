
#pragma once

#include "../wordnet/synset.h"
#include "distance_synset/wn_distance_synset_export.h"

namespace wn {
    namespace distance {

        class WN_DISTANCE_SYNSET_EXPORT base_synset {
            public:
                typedef std::vector<std::tuple<synset, synset, float>> _t_distance;
                static const float max_distance; //! max_distance to consider synsets connected

            public:
                base_synset();
                //! Lower bound for the distance between two synsets (0.f iff synsets are equal)
                float lower_bound() const;
                //! Upper bound for the distance between two synsets (defaults to '''distance::base_synset::max_distance''')
                virtual float upper_bound() const;

                //! Lower bound value for the distance between two synset sets.
                float lower_bound(const std::vector<synset>& v1, const std::vector<synset>& v2, float penalization) const;
                //! Upper bound bound value for the distance between two synset sets.
                float upper_bound(const std::vector<synset>& v1, const std::vector<synset>& v2, float penalization) const;

                //! Distance between two synsets
                virtual float operator()(const synset& s1, const synset& s2) const = 0;
                //! Similarity between two synsets
                virtual float similarity(const synset& s1, const synset& s2) const;
                //! Min distance between two bags of synsets
                float min_distance(const std::vector<synset>& v1, const std::vector<synset>& v2, std::vector<_t_distance>& dist_combs) const;
                //! Min distance between two bags of synsets (can be of different size)
                float min_distance(const std::vector<synset>& v1, const std::vector<synset>& v2, std::vector<_t_distance>& dist_combs, float penalization) const;

            
                //virtual bool connected(const synset& s1, const synset& s2) const;
            protected:
        };

        //! Compute similarity based on a distance value (for a given distance metric)
        float similarity(const base_synset&, const float& distance_value);

    }
}

