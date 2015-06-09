
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
    auto distance = this->max_distance();
    auto it_s1 = concept_count.find(s1);
    auto it_s2 = concept_count.find(s2);
    if (it_s1 != concept_count.end() && it_s2 != concept_count.end()) {
        auto lowest_common_hypernym = graph.lowest_hypernym(s1, s2);
        for (auto& lch : lowest_common_hypernym) {
            auto it_lch = concept_count.find(lch);
            if (it_lch != concept_count.end()) {
                auto aux_distance = 2.f * log(it_lch->second / (float)all_count) - (log(it_s1->second / (float)all_count) + log(it_s2->second / (float)all_count));
                distance = std::min(distance, float(aux_distance));
            }            
        }
    }
    return distance / this->max_distance();
}

float jiang_conrath::similarity(const synset& s1, const synset& s2) const {
    auto distance = this->operator()(s1, s2);
    return 1.f - distance;
}

float jiang_conrath::max_distance() const {
    return 2.f * log(max_count / (float)all_count) - (log(1.f / (float)all_count) + log(1.f / (float)all_count));
}
