
#include "wordnet.h"

using namespace std;

namespace wn {
    lex_sense parse_lexsn(const string& lexsn_str) {
        // lex_sense ::= ss_type:lex_filenum:lex_id:head_word:head_id
        pos_t pos;
        size_t filenum, lex_id, head_id;
        string head_word;

        stringstream ss(lexsn_str);
        string item;
        vector<string> elems(5);
        auto i = 0;
        while (getline(ss, item, ':') && i<5) {
            elems[i++] = item;
        }

        pos = static_cast<pos_t>(atoi(elems[0].c_str()));
        filenum = atoi(elems[1].c_str());
        lex_id = atoi(elems[2].c_str());
        head_word = elems[3].c_str();
        head_id = atoi(elems[4].c_str());
        return make_tuple(pos, filenum, lex_id, head_word, head_id);
    }

    int search_synset(const wordnet& wnet, const std::string& lemma, const lex_sense& data) {
        // TODO: It should be possible to look for the synset without the lemma, shouldn't it?
        vector<wn::index>::const_iterator i, i_end;
        tie(i, i_end) = wnet.get_indexes(lemma);
        for (; i != i_end; ++i) {
            for (auto& synset_id : i->synset_ids) {
                auto synset = wnet.wordnet_graph[synset_id];
                if (synset.pos == get<0>(data) && synset.lex_filenum == get<1>(data)) {
                    for (auto& id : synset.lex_ids) {                        
                        if (id == get<2>(data)) {
                            return synset_id;
                        }
                    }
                }
            }
        }
        return -1;
    }

}
