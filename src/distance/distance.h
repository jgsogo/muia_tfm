
#pragma once

#include "synset.h"
#include "wnb/core/wordnet.hh"

#include "distance/wn_distance_export.h"

namespace wn {
	class WN_DISTANCE_EXPORT distance {
		public:
			distance(const wnb::wordnet& wordnet);
			virtual float operator()(const wnb::synset& s1, const wnb::synset& s2) const = 0;
			virtual float min() const; //! min distance by default is 0
			virtual float max() const; //! max distance by default is std::numeric_limits<float>::max();
		protected:
			const wnb::wordnet& wordnet;
	};
}

