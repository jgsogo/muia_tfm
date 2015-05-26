
#pragma once

#include "corpus/wn_corpus_export.h"
#include "corpus.h"

namespace wn {
    class WN_CORPUS_EXPORT semcor : public corpus {
        public:
            semcor(const wordnet& wnet);
        protected:
            virtual _t_doc_index parse_document(const std::string&) const;
    };
}
