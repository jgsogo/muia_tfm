
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
        vector<string> elems;
        while (getline(ss, item, ':')) {
            elems.push_back(item);
        }

        pos = static_cast<pos_t>(atoi(elems[0].c_str()));
        filenum = atoi(elems[1].c_str());
        lex_id = atoi(elems[2].c_str());
        head_word = elems[3].c_str();
        head_id = atoi(elems[4].c_str());
        return make_tuple(pos, filenum, lex_id, head_word, head_id);
    }
}
