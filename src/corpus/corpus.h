
#pragma once

#include <map>
#include <vector>
#include "corpus/wn_corpus_export.h"
#include "distance/synset.h" //! TODO: Restructure project to include "wordnet/wordnet.h"

namespace wn {
    class WN_CORPUS_EXPORT corpus {
        public:
            typedef std::size_t doc_id;
            typedef std::map<wnb::synset, std::size_t> _t_doc_index;
            typedef std::map<wnb::synset, std::map<doc_id, std::size_t>> _t_corpus_index;
            typedef std::map<doc_id, std::size_t> _t_doc_count;
        public:
            corpus(const wnb::wordnet& wordnet);
            ~corpus();

            _t_doc_index add_documents(const std::vector<std::string>& docs);
            _t_doc_index add_document(const std::string& filename);
            const _t_corpus_index& get_index() const;
            const std::vector<std::string>& get_documents() const;
            const _t_doc_count& get_doc_count() const;
        protected:
            virtual _t_doc_index parse_document(const std::string&) const = 0;

        protected:
            const wnb::wordnet& wordnet;
            std::vector<std::string> documents; // doc_id: position in this vector.
            _t_corpus_index index;  // inverse index of term count
            _t_doc_count doc_count; // number of terms per document
    };
}
