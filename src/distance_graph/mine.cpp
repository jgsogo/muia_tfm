
#include "mine.h"
#include <numeric>

using namespace wn;
using namespace wn::distance;
using namespace std;

mine::mine(const base_synset& base_distance, const base_relation& dist_relation) : base_graph(base_distance, dist_relation) {
}

float mine::min_distance(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const {
    auto s1_nodes = s1.get_nodes();
    auto s2_nodes = s2.get_nodes();

    if (s1_nodes.size() > s2_nodes.size()) {
        return this->min_distance(s2, s1, node_penalization, edge_penalization);
    }
    else {
        assert(s2_nodes.size() >= s1_nodes.size());
        float distance = numeric_limits<float>::max();
        vector<conceptual_graph::synset_id> s2_synsets(s2_nodes.size());
        for_each(s2_nodes.begin(), s2_nodes.end(), [&s2_synsets](const pair<conceptual_graph::synset_id, synset>& item){ s2_synsets.push_back(item.first); });
        do {
            float aux_distance = 0.f;
            auto it_s1 = s1_nodes.begin();
            auto it_s2 = s2_synsets.begin();
            for (; it_s1 != s1_nodes.end(); ++it_s1, ++it_s2) {
                aux_distance += this->dist_synset.operator()(it_s1->second, s2_nodes[*it_s2]);
                auto s1_edges = s1.get_outgoing_edges(it_s1->first);
                auto s2_edges = s2.get_outgoing_edges(*it_s2);
                aux_distance += dist_relation.min_distance(s1_edges, s2_edges, edge_penalization);
            }
            if (aux_distance <= distance){
                // TODO: Store current permutation as 'min' candidate.
                distance = std::min(distance, aux_distance);
            }
        } while (next_permutation(s2_synsets.begin(), s2_synsets.end()));

        return distance + (s2_nodes.size() - s1_nodes.size())*node_penalization;
    }
}
