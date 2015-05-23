
#pragma once

#include "wordnet/wn_wordnet_export.h"
#include "wnb/core/wordnet.hh"

namespace wn {
	class WN_WORDNET_EXPORT hyperonym_graph {
		public:
			hyperonym_graph(const wnb::wordnet& wordnet, bool instance_hyperonym = true);
			~hyperonym_graph();

			static std::map<wnb::synset, std::size_t> hypernym_map(const wnb::wordnet& wordnet, const wnb::synset& s, bool instance_hyperonym = true);
            static std::vector<wnb::synset> orphans(const wnb::wordnet& wordnet, bool instance_hyperonym = true);

            std::map<wnb::synset, std::size_t> hypernym_map(const wnb::synset& s) const;
            std::vector<wnb::synset> orphans() const;
			std::size_t max_depth() const;
			std::size_t get_max_depth(const wnb::synset& s) const;
		protected:
			struct data;
			data* d;
			//const wnb::wordnet& wordnet;
	};
}

