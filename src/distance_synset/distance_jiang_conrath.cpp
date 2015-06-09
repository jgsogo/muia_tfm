
#include "distance_jiang_conrath.h"
#include <numeric>

using namespace wn;
using namespace wn::distance;
using namespace std;

jiang_conrath::jiang_conrath(const hyperonym_graph& graph, const corpus& corpus_) : information_based(graph, corpus_) {    
}

jiang_conrath::jiang_conrath(   const hyperonym_graph& graph, const std::map<synset, std::size_t>& concept_count,
                                std::size_t all_count, std::size_t max_count) 
    : information_based(graph, concept_count, all_count, max_count) {
}

jiang_conrath::~jiang_conrath() {
}

float jiang_conrath::operator()(const synset& s1, const synset& s2) const {
    auto distance = this->upper_bound();
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

float jiang_conrath::similarity(const synset& s1, const synset& s2) const {
    return 0.f;
}

float jiang_conrath::upper_bound() const {
    return 2 * log(all_count) - (log(1) + log(1));
}
