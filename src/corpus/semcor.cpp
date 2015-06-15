
#include "semcor.h"
#include "xml_parser/api.h"


using namespace wn;
using namespace std;


semcor::semcor(const wordnet& wnet) : corpus(wnet) {
}

corpus::_t_doc_index semcor::parse_document(const std::string& filename) const {
    corpus::_t_doc_index ret;

    auto on_wf_tag = [this, &ret](const core::service::node& wf) {
        bool has_lemma, has_lexsn;
        string lemma = wf.get_attribute("lemma", has_lemma);
        string lexsn = wf.get_attribute("lexsn", has_lexsn);
        if (has_lemma && has_lexsn) {
            auto data = wn::parse_lexsn(lexsn);
            vector<wn::index>::const_iterator i, i_end;
            tie(i, i_end) = wnet.get_indexes(lemma);
            for (; i!=i_end; ++i) {
                for (auto& synset_id: i->synset_ids) {
                    auto synset = wnet.wordnet_graph[synset_id];
                    if (synset.pos == get<0>(data) && synset.lex_filenum == get<1>(data)) {
                        for(auto& id: synset.lex_ids) {
                            if(id == get<2>(data)) {
                                ret.insert(make_pair(synset, 0)).first->second += 1;
                                return;
                            }
                        }
                    }
                }
            }
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
