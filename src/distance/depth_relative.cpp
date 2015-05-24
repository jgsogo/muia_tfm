
#include "depth_relative.h"
#include "../wordnet/hyperonym_graph.h"

using namespace wn;
using namespace std;

const pair<float, float> depth_relative::minmax_hyperonym_r = make_pair(1, 2);
const pair<float, float> depth_relative::minmax_hyponym_r = make_pair(1, 2);

struct depth_relative::data {
    data(const wnb::wordnet& wordnet) : graph(wordnet) {
    };
    hyperonym_graph graph;
};


depth_relative::depth_relative(const wnb::wordnet& wordnet) : distance(wordnet), d(new data(wordnet)) {
}

depth_relative::~depth_relative() {
    delete d;
}

float depth_relative::edge_weight(const wnb::synset& child, const wnb::synset& parent) const {
    assert(d->graph.get_max_depth(child) > d->graph.get_max_depth(parent));
    //assert(d->graph.get_max_depth(child) + 1 == d->graph.get_max_depth(parent));

    auto n_child_hypernyms = d->graph.hyperonyms(child).size();
    auto n_parent_hyponyms = d->graph.hyponyms(parent).size();
    // Formula in [Sussna, 1993]
    // TODO: This formula may have an ERROR, it should be: `min + (max-min)/n`
    auto w_child_hypernyms = minmax_hyperonym_r.second - (minmax_hyperonym_r.second - minmax_hyperonym_r.first)/float(n_child_hypernyms);
    auto w_parent_hyponyms = minmax_hyponym_r.second - (minmax_hyponym_r.second - minmax_hyponym_r.first)/float(n_parent_hyponyms);
    return (w_child_hypernyms + w_parent_hyponyms)/(2*(d->graph.get_max_depth(child)));
}

float depth_relative::operator()(const wnb::synset& s1, const wnb::synset& s2) const {
	//hyperonym_graph graph(wordnet);
	auto distance = distance::max_distance;
	auto lowest_common_hypernym = d->graph.lowest_hypernym(s1, s2);
	for(auto& lch: lowest_common_hypernym) {
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
        auto min_weight_s1 = distance::max_distance;
        auto paths_s1 = d->graph.hypernym_path(s1, lch);
        for (auto& path: paths_s1) {
            min_weight_s1 = std::min(min_weight_s1, path_weight(path));
        }
        // Work on paths s2->lch
        auto paths_s2 = d->graph.hypernym_path(s2, lch);
        auto min_weight_s2 = distance::max_distance;
        for (auto& path: paths_s2) {
            min_weight_s2 = std::min(min_weight_s2, path_weight(path));
        }

        // Keep minimum
        distance = std::min(distance, min_weight_s1+min_weight_s2);
	}
	return distance;
}

float depth_relative::max() const {
	return 2 * d->graph.max_depth(); //! TODO: Make this computation!
}
