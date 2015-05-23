
#include "corpus.h"

using namespace wn;
using namespace std;

namespace _detail {

    corpus::_t_doc_index& operator+=(corpus::_t_doc_index& lhs, const corpus::_t_doc_index& rhs) {
        for (auto& item: rhs) {
            auto it = lhs.insert(item);
            if (!it.second) {
                it.first->second += item.second;
            }
        }
        return lhs;
    }

    corpus::_t_doc_index operator+(const corpus::_t_doc_index& lhs, const corpus::_t_doc_index& rhs) {
        corpus::_t_doc_index ret = lhs;
        return ret += rhs;
    }

}


corpus::corpus(const wnb::wordnet& wordnet) : wordnet(wordnet) {
}

corpus::~corpus() {
}

const corpus::_t_corpus_index& corpus::get_index() const {
    return index;
}

corpus::_t_doc_index corpus::add_document(const std::string& filename) {
    using namespace _detail;
    auto doc_index = this->parse_document(filename);
    documents.push_back(filename);
    auto doc_i = documents.size();
    doc_count[doc_i] = accumulate(doc_index.begin(), doc_index.end(), 0, [](const size_t& lhs, const _t_doc_index::value_type& rhs){
        return lhs + rhs.second;
    });
    for (auto& entry: doc_index) {
        index[entry.first].insert(make_pair(doc_i, entry.second));
    }
    return doc_index;
}

corpus::_t_doc_index corpus::add_documents(const vector<string>& docs) {
    using namespace _detail;

    _t_doc_index partial_index;
    for (auto& filename : docs) {
        auto doc_index = this->add_document(filename);
        partial_index += doc_index;
    }
    return partial_index;
}

const vector<string>& corpus::get_documents() const {
    return documents;
}

const corpus::_t_doc_count& corpus::get_doc_count() const {
    return doc_count;
}
