
#include "shortest_path.h"
#include "wordnet/hyperonym_graph.h"

using namespace wn;

shortest_path::shortest_path(const wnb::wordnet& wordnet) : distance(wordnet) {
	hyperonym_graph graph(wordnet);
	max_depth = graph.max_depth();
}

float shortest_path::operator()(const wnb::synset& s1, const wnb::synset& s2) const {
	hyperonym_graph graph(wordnet);
	auto map1 = graph.hypernym_map(s1);
	auto map2 = graph.hypernym_map(s2);

	// For each ancestor synset common to both subject synsets, find the
	// connecting path length. Return the shortest of these.
    auto path_length = distance::max_distance;
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