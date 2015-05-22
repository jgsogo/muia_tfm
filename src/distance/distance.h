
#pragma once

#include "synset.h"
#include "wnb/core/wordnet.hh"

#include "distance/wn_distance_export.h"

namespace wn {
	class WN_DISTANCE_EXPORT distance {
		public:
			distance(const wnb::wordnet& wordnet);
			virtual float min() const; //! min distance by default is 0
			virtual float max() const; //! max distance by default is std::numeric_limits<float>::max();
			virtual float operator()(const wnb::synset& s1, const wnb::synset& s2) const = 0;
			
            typedef std::vector<std::tuple<wnb::synset, wnb::synset, float>> _t_distance;
            virtual float min_distance(std::vector<wnb::synset> v1, std::vector<wnb::synset> v2, std::vector<_t_distance>& dist_combs) const;
    protected:
			const wnb::wordnet& wordnet;
	};
}

