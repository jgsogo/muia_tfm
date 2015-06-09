
#include "mcs.h"
#include "../conceptual_graph/mcgregor_common_subgraphs.h"

using namespace wn;
using namespace wn::distance;


mcs::mcs(const base_synset& base_distance, const base_relation& dist_relation) : base_graph(base_distance, dist_relation) {
}

mcs::~mcs() {
}

float mcs::min_distance(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const {
    struct synset_cmp {
        synset_cmp(const base_synset& syn) : dist_synset(syn) {}
        bool operator() (const synset& a, const synset& b) {
            auto distance = dist_synset(a, b);
            return distance <= synset_threshold;
        }
        const base_synset& dist_synset;
        float synset_threshold;
    };

    struct relation_cmp {
        relation_cmp(const base_relation& rel) : dist_relation(rel) {}
        bool operator() (const relation& a, const relation& b) {
            auto distance = dist_relation(a, b);
            return distance <= edge_threshold;
        }
        const base_relation& dist_relation;
        float edge_threshold;
    };

    synset_cmp cmp_synset(dist_synset);
    cmp_synset.synset_threshold = dist_synset.lower_bound() + 0.1f*(dist_synset.upper_bound()-dist_synset.lower_bound());

    relation_cmp cmp_relation(dist_relation);
    cmp_relation.edge_threshold = dist_relation.lower_bound() + 0.1f*(dist_relation.upper_bound()-dist_relation.lower_bound());

    std::vector<std::tuple<conceptual_graph, conceptual_graph_corresponde, conceptual_graph_corresponde>> mcs_subgraphs;
    mcgregor_common_subgraphs(s1, s2, cmp_synset, cmp_relation, mcs_subgraphs);

    // Rank candidates and keep the best one (minimizes distance)
    auto min_value = std::numeric_limits<float>::max();
    conceptual_graph best;
    conceptual_graph_corresponde correspondence_s1;
    conceptual_graph_corresponde correspondence_s2;
    for (auto& candidate: mcs_subgraphs) {
        auto value = 0.f;
        auto candidate_graph = get<0>(candidate);
        // Distance between nodes:
        auto it_s1 = get<1>(candidate).begin();
        auto it_s2 = get<2>(candidate).begin();
        for (; it_s1 != get<1>(candidate).end(); ++it_s1, ++it_s2) {
            value += dist_synset(s1.get_node(it_s1->second), s2.get_node(it_s2->second));
        }
        // Distance by relations
        // TODO(jgsogo): Sum also distance by relations.
        // Graph coverage
        auto max_size = std::max(s1.get_nodes().size(), s2.get_nodes().size());
        value = value + cmp_synset.synset_threshold*(max_size-candidate_graph.get_nodes().size());
        // Update minimum
        if (value < min_value) {
            min_value = value;
            best = get<0>(candidate);
            correspondence_s1 = get<1>(candidate);
            correspondence_s2 = get<2>(candidate);
        }
    }

    /*
    std::cout << "All candidates: " << std::endl;
    for (auto& graph : mcs_subgraphs) {
        std::cout << std::endl << "wn::distance::mcs" << std::endl;
        std::get<0>(graph).print(std::cout);
    }
    */
    std::cout << std::endl << "Best graph:" << std::endl << std::endl;
    best.print(std::cout);
    std::cout << std::endl << "Punctuation = " << min_value << std::endl;
    std::cout << "Correspondences = " << std::endl;
    auto it_cor_s1 = correspondence_s1.begin();
    auto it_cor_s2 = correspondence_s2.begin();
    for (; it_cor_s1 != correspondence_s1.end(); ++it_cor_s1, ++it_cor_s2) {
        std::cout << it_cor_s1->first << ">>> " << it_cor_s1->second << " <--> " << it_cor_s2->second << std::endl;
    }
    return min_value;
}
