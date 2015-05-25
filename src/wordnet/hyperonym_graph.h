
#pragma once

#include "wordnet/wn_wordnet_export.h"
#include "../distance/synset.h" // TODO: This should be 'wordnet/wordnet.h'

namespace wn {

	class WN_WORDNET_EXPORT hyperonym_graph {
		public:
			hyperonym_graph(const wnb::wordnet& wordnet, bool instance_hyperonym = true);
			~hyperonym_graph();

			static std::map<wnb::synset, std::size_t> hypernym_map(const wnb::wordnet& wordnet, const wnb::synset& s, bool instance_hyperonym = true);
            static std::vector<wnb::synset> orphans(const wnb::wordnet& wordnet, bool instance_hyperonym = true);
            static std::vector<std::vector<wnb::synset>> hypernym_path(const wnb::wordnet& wordnet, const wnb::synset& from, const wnb::synset& to, bool instance_hyperonym = true);
            static std::vector<wnb::synset> lowest_hypernym(const wnb::wordnet& wordnet, const wnb::synset& s1, const wnb::synset& s2, bool instance_hyperonym = true);
            static std::vector<wnb::synset> hyperonyms(const wnb::wordnet& wordnet, const wnb::synset& s, bool instance_hyperonym = true);
            static std::vector<wnb::synset> hyponyms(const wnb::wordnet& wordnet, const wnb::synset& s, bool instance_hyperonym = true);

            std::map<wnb::synset, std::size_t> hypernym_map(const wnb::synset& s) const;
            std::vector<wnb::synset> orphans() const;
			std::size_t max_depth() const;
			std::size_t get_max_depth(const wnb::synset& s) const;
			std::vector<std::vector<wnb::synset>> hypernym_path(const wnb::synset& from, const wnb::synset& to) const;
			std::vector<wnb::synset> lowest_hypernym(const wnb::synset& s1, const wnb::synset& s2) const;
            std::vector<wnb::synset> hyperonyms(const wnb::synset& s) const;
            std::vector<wnb::synset> hyponyms(const wnb::synset& s) const;
            const wnb::wordnet& get_wordnet() const;
		protected:
			struct data;
			data* d;
			//const wnb::wordnet& wordnet;
	};
}

