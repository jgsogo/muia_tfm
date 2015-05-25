
#include "mine.h"

using namespace wn::distance;
using namespace std;

mine::mine(const base& base_distance) : graph_base(base_distance) {
}

float mine::operator()(const conceptual_graph& s1, const conceptual_graph& s2) const {
    auto s1_nodes = s1.get_nodes();
    auto s2_nodes = s2.get_nodes();

    if (s1_nodes.size() > s2_nodes.size()) {
        return this->operator()(s2, s1);
    }
    else {
        assert(s2_nodes.size() >= s1_nodes.size());
        // Prepare synsets to iterate
        vector<conceptual_graph::synset_id> s2_synsets(s2_nodes.size()), s1_synsets(s1_nodes.size());
        for_each(s2_nodes.begin(), s2_nodes.end(), [&s2_synsets](const pair<conceptual_graph::synset_id, wnb::synset>& item){
            s2_synsets.push_back(item.first);
        });
        sort(s2_synsets.begin(), s2_synsets.end());
        for_each(s1_nodes.begin(), s1_nodes.end(), [&s1_synsets](const pair<conceptual_graph::synset_id, wnb::synset>& item){
            s1_synsets.push_back(item.first);
        });

        do {

        } while(next_permutation(s2_synsets.begin(), s2_synsets.end()));

    }
}

float mine::operator()(const conceptual_graph& s1,
                       const vector<conceptual_graph::synset_id>& s1_synsets,
                       const conceptual_graph& s2,
                       const vector<conceptual_graph::synset_id>& s1_synsets) const {
    assert(s2.size() >= s1.size());
    float distance = 0.f;

    auto s1_nodes = s1.get_nodes();
    auto s2_nodes = s2.get_nodes();
    auto it_s1 = s1_synsets.begin();
    auto it_s2 = s2_synsets.begin();
    for (; it_s1 != s1.end(); ++it_s1, ++it_s2) {
        // Distance between nodes
        distance += dist(s1_nodes[*it_s1], s2_nodes[*it_s2]);
        auto s1_edges = s1.get_outgoing_edges(*it_s1);
        auto s2_edges = s2.get_outgoing_edges(*it_s2);
        distance += this->operator()(s1, s1_edges, s2, s2_edges);

    }
    return distance;
}

float mine::operator()(const conceptual_graph& s1,
                       const vector<pair<relation, synset_id>>& s1_relations,
                       const conceptual_graph& s2,
                       const vector<pair<relation, synset_id>>& s2_relations) const {

    if (s1_relations.size() > s2_relations.size()) {
        return this->operator()(s2, s2_relations, s1, s1_relations);
    }
    else {
        float distance = numeric_limits<float>::max();
        assert(s2_relations.size() >= s1_relations.size());
        sort(s1_relations.begin(), s1_relations.end());
        sort(s2_relations.begin(), s2_relations.end());
        do {
            float aux_distance = inner_product(s1_relations.begin(), s1_relations.end(), s2_relations.begin(), s2_relations.end(),
                                                0.f, [this](const pair<relation, synset_id>& lhs, const pair<relation, synset_id>& rhs){
                                                    if (lhs.first == rhs.first) {
                                                        return dist(s1.get_node(lhs.second), s2.get_node(rhs.second));
                                                        }
                                                    else {
                                                        return dist.max();
                                                        }
                                                });


            distance = std::min(distance, aux_distance);
        } while(next_permutation(s2_relations.begin(), s2_relations.end()));
    }
}
