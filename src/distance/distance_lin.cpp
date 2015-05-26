
#include "distance_lin.h"
#include <numeric>

using namespace wn::distance;
using namespace std;

lin::lin(const wn::hyperonym_graph& graph, const wn::corpus& corpus) : information_based(graph, corpus) {
    max_count = 0.f;
    auto corpus_index = corpus.get_index();
    for (auto& s : corpus_index) {
        auto hypernyms = graph.hypernym_map(s.first);
        auto synset_count = std::accumulate(s.second.begin(), s.second.end(), 0, [](const size_t& lhs, const pair<corpus::doc_id, std::size_t>& doc_count){ return lhs + doc_count.second; });
        // Append counts
        concept_count.insert(make_pair(s.first, 0)).first->second += synset_count;
        for (auto& hypernym : hypernyms) {
            concept_count.insert(make_pair(hypernym.first, 0)).first->second += synset_count;
        }
        all_count += synset_count*(hypernyms.size() + 1);
    }
    /*
    for (auto& s: corpus_index) {
        auto synset_count = std::accumulate(s.second.begin(), s.second.end(), size_t(0), [](const size_t& lhs, const pair<corpus::doc_id, std::size_t>& doc_count){ return lhs + doc_count.second; });
        concept_count[s.first] = synset_count;
        all_count += synset_count;
        max_count = std::max(max_count, synset_count);
    }
    */
}

lin::~lin() {
}

float lin::operator()(const wnb::synset& s1, const wnb::synset& s2) const {
    auto similarity = 0.f;
    auto it_s1 = concept_count.find(s1);
    auto it_s2 = concept_count.find(s2);
    if (it_s1 != concept_count.end() && it_s2 != concept_count.end()) {
        auto lowest_common_hypernym = graph.lowest_hypernym(s1, s2);
        for (auto& lch : lowest_common_hypernym) {
            auto it_lch = concept_count.find(lch);
            if (it_lch != concept_count.end()) {
                // TODO: Formula in Lin does not work as expected.
                auto aux_similarity = 2 * log(it_lch->second) / (log(it_s1->second) + log(it_s2->second));
                similarity = std::max(similarity, float(aux_similarity));
            }            
        }
    }
    if (similarity == 0.f) {
        return this->max();
    }
    return 1.f/similarity;
}

float lin::max() const {
    return 1.f;
}
