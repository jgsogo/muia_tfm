
#include "distance_leacock_chodorow.h"

using namespace wn;
using namespace wn::distance;
using namespace std;

leacock_chodorow::leacock_chodorow(const hyperonym_graph& graph) : depth_relative(graph) {
}

leacock_chodorow::~leacock_chodorow() {
}

float leacock_chodorow::operator()(const synset& s1, const synset& s2) const {
    auto sim_value = this->similarity(s1, s2);
    return 1.f - sim_value;
}

float leacock_chodorow::similarity(const synset& s1, const synset& s2) const {
    if (s1 == s2) {
        return 1.f;
    }
    auto sim_value = this->similarity_exact(s1, s2);
    auto max_sim_value = -log(1 / float(2 * graph.max_depth()));
    return (sim_value / max_sim_value);
}

float leacock_chodorow::similarity_exact(const synset& s1, const synset& s2) const {
    auto map1 = graph.hypernym_map(s1);
    auto map2 = graph.hypernym_map(s2);

    // For each ancestor synset common to both subject synsets, find the
    // connecting path length. Return the shortest of these.
    auto max_path_length = 2 * graph.max_depth();
    auto path_length = max_path_length;
    for (auto it1 = map1.begin(); it1 != map1.end(); ++it1) {
        for (auto it2 = map2.begin(); it2 != map2.end(); ++it2) {
            if (it1->first == it2->first) {
                path_length = (std::min)(path_length, it1->second + it2->second);
            }
        }
    }
    return -log(path_length / float(max_path_length));
}
