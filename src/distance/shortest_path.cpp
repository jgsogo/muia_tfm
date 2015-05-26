
#include "shortest_path.h"
#include "../wordnet/hyperonym_graph.h"

using namespace wn;
using namespace wn::distance;

shortest_path::shortest_path(const wordnet& wnet) :wnet(wnet) {
    hyperonym_graph graph(wnet);
	max_depth = graph.max_depth();
}

float shortest_path::operator()(const synset& s1, const synset& s2) const {
    auto map1 = hyperonym_graph::hypernym_map(wnet, s1);
    auto map2 = hyperonym_graph::hypernym_map(wnet, s2);

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
	return path_length;
}

float shortest_path::max() const {
	return 2 * max_depth;
}
