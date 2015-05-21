
#pragma once

#include "wordnet/wn_wordnet_export.h"
#include "wnb/core/wordnet.hh"

namespace wn {
	class WN_WORDNET_EXPORT hyperonym_graph {
		public:
			hyperonym_graph(const wnb::wordnet& wordnet);
			~hyperonym_graph();
			std::map<wnb::synset, std::size_t> hypernym_map(wnb::synset s) const;
			std::size_t max_depth() const;
		protected:
			struct data;
			data* d;
			//const wnb::wordnet& wordnet;
	};
}

