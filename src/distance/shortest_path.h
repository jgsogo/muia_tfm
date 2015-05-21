
#pragma once

#include "distance.h"

namespace wn {
	class WN_DISTANCE_EXPORT shortest_path : public distance {
		public:
			shortest_path(const wnb::wordnet& wordnet);
			virtual float operator()(const synset& s1, const synset& s2);
	};
}