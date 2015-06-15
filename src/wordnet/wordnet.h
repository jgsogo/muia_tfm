
#pragma once

#include "wordnet/wn_wordnet_export.h"
#include "wnb/core/wordnet.hh"
#include "synset.h"

namespace wn {
    typedef wnb::wordnet wordnet;

    typedef wnb::ptr ptr;
    typedef wnb::index index;
    typedef wnb::pos_t pos_t;
    typedef wnb::info_helper info_helper;

    // lex_sense ::= ss_type:lex_filenum:lex_id:head_word:head_id
    typedef std::tuple<pos_t, std::size_t, std::size_t, std::string, std::size_t> lex_sense;
    WN_WORDNET_EXPORT lex_sense parse_lexsn(const std::string& lexsn_str);

    WN_WORDNET_EXPORT int search_synset(const wordnet&, const std::string&, const lex_sense&);

}
