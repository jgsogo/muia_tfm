
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

/* TODO: Move to wn::distance::base_relation
float mine::min_distance(const vector<relation>& rel1, const vector<relation>& rel2, float edge_penalization) const {
    if (rel1.size() > rel2.size()) {
        return this->min_distance(rel2, rel1, edge_penalization);
    }
    else {
        assert(rel2.size() >= rel1.size());
        float distance = rel1.size()*dist_relation.max();
        auto relation_less = [](const relation& lhs, const relation& rhs){ return lhs.type < rhs.type; };
        vector<relation> aux_rel2(rel2.begin(), rel2.end());
        sort(aux_rel2.begin(), aux_rel2.end(), relation_less);
        do {
            float aux_distance = inner_product(rel1.begin(), rel1.end(), aux_rel2.begin(), 0.f,
                [](const float& lhs, const float& rhs){ return lhs + rhs; },
                [this](const relation& lhs, const relation& rhs){ return this->operator()(lhs, rhs); });
            distance = std::min(distance, aux_distance);
        } while (next_permutation(aux_rel2.begin(), aux_rel2.end(), relation_less));
        return distance + (rel2.size() - rel1.size())*edge_penalization;
    }
}
*/
