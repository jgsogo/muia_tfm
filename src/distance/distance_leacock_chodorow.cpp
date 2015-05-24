
#include "distance_leacock_chodorow.h"

using namespace wn::distance;
using namespace std;

leacock_chodorow::leacock_chodorow(const hyperonym_graph& graph) : depth_relative(graph) {
}

leacock_chodorow::~leacock_chodorow() {
}

float leacock_chodorow::operator()(const wnb::synset& s1, const wnb::synset& s2) const {
	auto map1 = graph.hypernym_map(s1);
	auto map2 = graph.hypernym_map(s2);

	// For each ancestor synset common to both subject synsets, find the
	// connecting path length. Return the shortest of these.
    auto path_length = base::max_distance;
	for (auto it1 = map1.begin(); it1 != map1.end(); ++it1) {
		for (auto it2 = map2.begin(); it2 != map2.end(); ++it2) {
			if (it1->first == it2->first) {
				path_length = (std::min)(path_length, float(it1->second + it2->second));
			}
		}
	}

    if (path_length == 0) {
        return 0;
    }
    else {
        auto similarity = -log(path_length/(2*graph.max_depth()));
        return 1.f/similarity;
    }
}

float leacock_chodorow::max() const {
	return 2 * graph.max_depth(); // TODO: Make this computation!
}
