
#include "distance_lin.h"
#include <numeric>

using namespace wn;
using namespace wn::distance;
using namespace std;

lin::lin(const hyperonym_graph& graph_, const corpus& corpus_) : information_based(graph_, corpus_) {    
}

lin::lin(   const hyperonym_graph& graph, const std::map<synset, std::size_t>& concept_count,
            std::size_t all_count, std::size_t max_count)
    : information_based(graph, concept_count, all_count, max_count) {
}

lin::~lin() {
}

float lin::operator()(const synset& s1, const synset& s2) const {
    auto sim_value = this->similarity(s1, s2);
    return 1.f - sim_value;
}

float lin::similarity(const synset& s1, const synset& s2) const {
    if (s1 == s2) {
        return 1.f;
    }
    auto sim_value = this->similarity_exact(s1, s2);
    auto max_sim_value = 2 * log(max_count) / (log(2) + log(1)); // TODO: it is a little bit weird..
    return (sim_value / max_sim_value);    
}

float lin::similarity_exact(const synset& s1, const synset& s2) const {
    auto similarity = 0.f;
    auto it_s1 = concept_count.find(s1);
    auto it_s2 = concept_count.find(s2);
    if (it_s1 != concept_count.end() && it_s2 != concept_count.end()) {
        if ((it_s1->second > 1) || (it_s2->second > 1)) {
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
    }
    return similarity;
}

float lin::upper_bound() const {
    return 1.f;
}
