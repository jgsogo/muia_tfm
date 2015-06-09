
#include "distance_wu_palmer.h"

using namespace wn;
using namespace wn::distance;
using namespace std;

wu_palmer::wu_palmer(const hyperonym_graph& graph) : depth_relative(graph) {
}

wu_palmer::~wu_palmer() {
}

float wu_palmer::operator()(const synset& s1, const synset& s2) const {
    auto sim_value = this->similarity(s1, s2);
    return 1.f - sim_value;
}

float wu_palmer::similarity(const synset& s1, const synset& s2) const {
    if (s1 == s2) {
        return 1.f;
    }
    return this->similarity_exact(s1, s2);
}

float wu_palmer::similarity_exact(const synset& s1, const synset& s2) const {
    auto lowest_common_hypernym = graph.lowest_hypernym(s1, s2);
    //auto lch_depth = graph.max_depth();
    float similarity = 0.f;
    for (auto& lch : lowest_common_hypernym) {
        // Work on paths s1->lch
        auto min_distance_s1 = base_synset::max_distance;
        auto paths_s1 = graph.hypernym_path(s1, lch);
        for (auto& path : paths_s1) {
            min_distance_s1 = std::min(min_distance_s1, float(path.size() - 1));
        }
        // Work on paths s2->lch
        auto paths_s2 = graph.hypernym_path(s2, lch);
        auto min_distance_s2 = base_synset::max_distance;
        for (auto& path : paths_s2) {
            min_distance_s2 = std::min(min_distance_s2, float(path.size() - 1));
        }
        // Similarity (formula Wu and Palmer, 1994)
        auto lch_depth = graph.get_max_depth(lch);
        float aux_similarity = 2 * lch_depth / (min_distance_s1 + min_distance_s2 + 2 * lch_depth);
        similarity = std::max(similarity, aux_similarity);
    }
    return similarity;
}

float wu_palmer::upper_bound() const {
	return 1.f;
}
