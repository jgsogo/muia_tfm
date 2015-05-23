
#pragma once

#include <map>
#include <vector>
#include "corpus/wn_corpus_export.h"
#include "wnb/core/wordnet.hh"

namespace wn {
    class WN_CORPUS_EXPORT corpus {
        public:
            typedef std::size_t doc_id;
            typedef std::map<wnb::synset, std::size_t> _t_doc_index;
            typedef std::map<wnb::synset, std::map<doc_id, std::size_t>> _t_corpus_index;
        public:
            corpus(const wnb::wordnet& wordnet);
            ~corpus();

            _t_doc_index add_documents(const std::vector<std::string>& docs);
            const _t_corpus_index& get_index() const;
        protected:
            virtual _t_doc_index parse_document(const std::string&) const = 0;

        protected:
            const wnb::wordnet& wordnet;
            std::vector<std::string> documents;
            _t_corpus_index index;
    };
}
