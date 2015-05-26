
#pragma once

#include "wordnet/wn_wordnet_export.h"
#include "../wordnet/wordnet.h"

namespace wn {

	class WN_WORDNET_EXPORT hyperonym_graph {
		public:
			hyperonym_graph(const wordnet& wordnet, bool instance_hyperonym = true);
			~hyperonym_graph();

			static std::map<synset, std::size_t> hypernym_map(const wordnet& wordnet, const synset& s, bool instance_hyperonym = true);
            static std::vector<synset> orphans(const wordnet& wordnet, bool instance_hyperonym = true);
            static std::vector<std::vector<synset>> hypernym_path(const wordnet& wordnet, const synset& from, const synset& to, bool instance_hyperonym = true);
            static std::vector<synset> lowest_hypernym(const wordnet& wordnet, const synset& s1, const synset& s2, bool instance_hyperonym = true);
            static std::vector<synset> hyperonyms(const wordnet& wordnet, const synset& s, bool instance_hyperonym = true);
            static std::vector<synset> hyponyms(const wordnet& wordnet, const synset& s, bool instance_hyperonym = true);

            std::map<synset, std::size_t> hypernym_map(const synset& s) const;
            std::vector<synset> orphans() const;
			std::size_t max_depth() const;
			std::size_t get_max_depth(const synset& s) const;
			std::vector<std::vector<synset>> hypernym_path(const synset& from, const synset& to) const;
			std::vector<synset> lowest_hypernym(const synset& s1, const synset& s2) const;
            std::vector<synset> hyperonyms(const synset& s) const;
            std::vector<synset> hyponyms(const synset& s) const;
            const wordnet& get_wordnet() const;
		protected:
			struct data;
			data* d;
	};
}

