
#include "distance_jiang_conrath.h"
#include <numeric>

using namespace wn::distance;
using namespace std;

jiang_conrath::jiang_conrath(const wn::hyperonym_graph& graph, const wn::corpus& corpus) : information_based(graph, corpus) {
    auto corpus_index = corpus.get_index();
    for (auto& s: corpus_index) {
        auto hypernyms = graph.hypernym_map(s.first);
        auto synset_count = std::accumulate(s.second.begin(), s.second.end(), 0, [](const size_t& lhs, const pair<corpus::doc_id, std::size_t>& doc_count){ return lhs+doc_count.second;});
        // Append counts
        concept_count.insert(make_pair(s.first, 0)).first->second += synset_count;
        for (auto& hypernym: hypernyms) {
            concept_count.insert(make_pair(hypernym.first, 0)).first->second += synset_count;
        }
        all_count += synset_count*(hypernyms.size()+1);
    }
}

jiang_conrath::~jiang_conrath() {
}

float jiang_conrath::operator()(const wnb::synset& s1, const wnb::synset& s2) const {
    auto distance = this->max();
    auto it_s1 = concept_count.find(s1);
    auto it_s2 = concept_count.find(s2);
    if (it_s1 != concept_count.end() && it_s2 != concept_count.end()) {
        auto lowest_common_hypernym = graph.lowest_hypernym(s1, s2);
        for (auto& lch : lowest_common_hypernym) {
            auto it_lch = concept_count.find(lch);
            if (it_lch != concept_count.end()) {
                auto aux_distance = 2 * log(it_lch->second) - (log(it_s1->second) + log(it_s2->second));
                distance = std::min(distance, float(aux_distance));
            }            
        }
    }
    return distance;
}

float jiang_conrath::max() const {
    return 2 * log(all_count) - (log(1) + log(1));
}
