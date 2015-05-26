
#include "distance_sussna.h"

using namespace wn::distance;
using namespace std;

const pair<float, float> sussna::minmax_hyperonym_r = make_pair(1, 2);
const pair<float, float> sussna::minmax_hyponym_r = make_pair(1, 2);

sussna::sussna(const wn::hyperonym_graph& graph) : depth_relative(graph) {
}

sussna::~sussna() {
}

float sussna::edge_weight(const wnb::synset& child, const wnb::synset& parent) const {
    assert(graph.get_max_depth(child) > graph.get_max_depth(parent));
    //assert(graph.get_max_depth(child) + 1 == graph.get_max_depth(parent));

    auto n_child_hypernyms = graph.hyperonyms(child).size();
    auto n_parent_hyponyms = graph.hyponyms(parent).size();
    // Formula in [Sussna, 1993]
    // TODO: This formula may have an ERROR, it should be: `min + (max-min)/n`
    auto w_child_hypernyms = minmax_hyperonym_r.second - (minmax_hyperonym_r.second - minmax_hyperonym_r.first)/float(n_child_hypernyms);
    auto w_parent_hyponyms = minmax_hyponym_r.second - (minmax_hyponym_r.second - minmax_hyponym_r.first)/float(n_parent_hyponyms);
    return (w_child_hypernyms + w_parent_hyponyms)/(2*(graph.get_max_depth(child)));
}

float sussna::operator()(const wnb::synset& s1, const wnb::synset& s2) const {
	//hyperonym_graph graph(wordnet);
	auto distance = this->max();
	auto lowest_common_hypernym = graph.lowest_hypernym(s1, s2);
	for(auto& lch: lowest_common_hypernym) {
        auto paths_s1 = graph.hypernym_path(s1, lch);
        auto paths_s2 = graph.hypernym_path(s2, lch);

        if (!paths_s1.empty() && !paths_s2.empty()) {
            // Compute minimum distance path
            auto path_weight = [this](const vector<wnb::synset>& path){
                float weight = 0.f;
                auto it_1 = path.begin();
                auto it_2 = it_1 + 1;
                do {
                    weight += edge_weight(*it_1, *it_2);
                    ++it_1; ++it_2;
                } while (it_2 != path.end());
                return weight;
            };

            // Work on paths s1->lch
            auto min_weight_s1 = this->max();
            for (auto& path : paths_s1) {
                min_weight_s1 = std::min(min_weight_s1, path_weight(path));
            }
            // Work on paths s2->lch

            auto min_weight_s2 = this->max();
            for (auto& path : paths_s2) {
                min_weight_s2 = std::min(min_weight_s2, path_weight(path));
            }

            // Keep minimum
            distance = std::min(distance, min_weight_s1 + min_weight_s2);
        }
	}
	return distance;
}

float sussna::max() const {
    // Max distance will happen on the longest path and with the highest edge-weights
    float max_v = 0.f;
    for (auto i = 1; i <= graph.max_depth(); ++i) {
        max_v +=  0.5f/i;
    }
    return 2 * (minmax_hyperonym_r.second + minmax_hyponym_r.second) * max_v;
}
