
#pragma once

#include "distance.h"

namespace wn {
	class WN_DISTANCE_EXPORT shortest_path : public distance {
		public:
			shortest_path(const wnb::wordnet& wordnet);
			virtual float operator()(const wnb::synset& s1, const wnb::synset& s2) const;
			virtual float max() const;
	};
}