
#include "semcor.h"
#include "xml_parser/api.h"


using namespace wn;
using namespace std;

tuple<wnb::pos_t, size_t, size_t> parse_lexsn(const std::string& lexsn) {
    // lex_sense ::= ss_type:lex_filenum:lex_id:head_word:head_id
    wnb::pos_t pos;
    size_t filenum, lex_id;
    stringstream ss(lexsn);
    string item;
    vector<string> elems;
    while (getline(ss, item, ':')) {
        elems.push_back(item);
    }
    pos = static_cast<wnb::pos_t>(atoi(elems[0].c_str()));
    filenum = atoi(elems[1].c_str());
    lex_id = atoi(elems[2].c_str());
    return make_tuple(pos, filenum, lex_id);
}

semcor::semcor(const wnb::wordnet& wordnet) : corpus(wordnet) {
}

corpus::_t_doc_index semcor::parse_document(const std::string& filename) const {
    corpus::_t_doc_index ret;

    auto on_wf_tag = [this, &ret](const core::service::node& wf) {
        bool has_lemma, has_lexsn;
        string lemma = wf.get_attribute("lemma", has_lemma);
        string lexsn = wf.get_attribute("lexsn", has_lexsn);
        if (has_lemma && has_lexsn) {
            //cout << lemma << " | " << lexsn;
            auto data = parse_lexsn(lexsn);
            vector<wnb::index>::const_iterator i, i_end;
            tie(i, i_end) = wordnet.get_indexes(lemma);
            for (; i!=i_end; ++i) {
                for (auto& synset_id: i->synset_ids) {
                    auto synset = wordnet.wordnet_graph[synset_id];
                    if (synset.pos == get<0>(data) && synset.lex_filenum == get<1>(data)) {
                        for(auto& id: synset.lex_ids) {
                            if(id == get<2>(data)) {
                                ret.insert(make_pair(synset, 0)).first->second += 1;
                                //cout << " -> " << synset << " [" << ret[synset] << "]"<< endl;
                                return;
                            }
                        }
                    }
                }
            }
            //cout << endl;
        }
    };
    // Parser
    core::service::parser* parser;
    build_xml_parser(parser, "expat");
    parser->register_tag("wf", on_wf_tag);
    parser->parse_file(filename, "contextfile");
    delete_xml_parser(parser);
    return ret;
}
