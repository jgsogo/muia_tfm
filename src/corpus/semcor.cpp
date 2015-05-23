
#include "semcor.h"
#include "xml_parser/api.h"

using namespace wn;
using namespace std;

semcor::semcor(const wnb::wordnet& wordnet) : corpus(wordnet) {
}

corpus::_t_doc_index semcor::parse_document(const std::string& filename) const {
    corpus::_t_doc_index ret;

    auto on_wf_tag = [this](const core::service::node& wf) {
        bool has_attribute;
        string value = wf.get_attribute("lexsn", has_attribute);
        if (has_attribute) {
            wordnet;
        }
    };
    //
    core::service::parser* parser;
    build_xml_parser(parser, "expat");
    parser->register_tag("wf", on_wf_tag);
    parser->parse_file(filename, "contextfile");
    delete_xml_parser(parser);
    return ret;
}
