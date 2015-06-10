
#include "mine.h"
#include <numeric>

using namespace wn;
using namespace wn::distance;
using namespace std;

mine::mine(const base_synset& base_distance, const base_relation& dist_relation) : base_graph(base_distance, dist_relation) {
}

//! Compute max_similarity between two conceptual_graphs (tolerances must belong to [0, 1))
float mine::max_similarity(const conceptual_graph& s1, const conceptual_graph& s2,
    float synset_tolerance, float relation_tolerance,
    conceptual_graph& result,
    conceptual_graph_corresponde& s1_to_result,
    conceptual_graph_corresponde& s2_to_result
    ) const {
    throw std::exception();
}

float mine::max_similarity(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const {
    auto s1_nodes = s1.get_nodes();
    auto s2_nodes = s2.get_nodes();

    if (s1_nodes.size() > s2_nodes.size()) {
        return this->max_similarity(s2, s1, node_penalization, edge_penalization);
    }
    else {
        assert(s2_nodes.size() >= s1_nodes.size());
        float similarity = numeric_limits<float>::min();
        vector<conceptual_graph::synset_id> s2_synsets(s2_nodes.size());
        for_each(s2_nodes.begin(), s2_nodes.end(), [&s2_synsets](const pair<conceptual_graph::synset_id, synset>& item){ s2_synsets.push_back(item.first); });
        do {
            float aux_similarity = 0.f;
            auto it_s1 = s1_nodes.begin();
            auto it_s2 = s2_synsets.begin();
            for (; it_s1 != s1_nodes.end(); ++it_s1, ++it_s2) {
                aux_similarity += this->dist_synset.similarity(it_s1->second, s2_nodes[*it_s2]);
                auto s1_edges = s1.get_outgoing_edges(it_s1->first);
                auto s2_edges = s2.get_outgoing_edges(*it_s2);
                auto max_distance = dist_relation.upper_bound(s1_edges, s2_edges, edge_penalization);
                aux_similarity += (max_distance - dist_relation.min_distance(s1_edges, s2_edges, edge_penalization));
            }
            if (aux_similarity >= similarity){
                // TODO: Store current permutation as 'min' candidate.
                similarity = std::max(similarity, aux_similarity);
            }
        } while (next_permutation(s2_synsets.begin(), s2_synsets.end()));

        return similarity;
    }
}
