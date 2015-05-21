
#pragma once

#include "synset.h"
#include "wnb/core/wordnet.hh"

#include "distance/wn_distance_export.h"

namespace wn {
	class WN_DISTANCE_EXPORT distance {
		public:
			distance(const wnb::wordnet& wordnet);
			virtual float operator()(const synset& s1, const synset& s2) = 0;
		protected:
			const wnb::wordnet& wordnet;
	};
}

