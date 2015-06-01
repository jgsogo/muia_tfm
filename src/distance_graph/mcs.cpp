
#include "mcs.h"

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
    cmp_synset.synset_threshold = dist_synset.min() + 0.1f*(dist_synset.max()-dist_synset.min());

    relation_cmp cmp_relation(dist_relation);
    cmp_relation.edge_threshold = dist_relation.min() + 0.1f*(dist_relation.max()-dist_relation.min());

    std::vector<conceptual_graph> max_subgraphs;
    mcgregor_common_subgraphs(s1, s2, cmp_synset, cmp_relation, max_subgraphs);

    // TODO: Build set of maximum_common_subgraphs without overlappings.
    //  1) Compute punctuation of each subgraph.
    auto punctuation_f = [this](const conceptual_graph& graph) {
        return graph.get_nodes().size();
    };
    //  2) Build matrix of incompatibilities.
    auto compatible_f = [this](const conceptual_graph& lhs, const conceptual_graph& rhs) {
        auto lhs_nodes = lhs.get_nodes();
        auto rhs_nodes = rhs.get_nodes();
        // Credit: http://stackoverflow.com/questions/3772664/intersection-of-two-stl-maps
        //      non-general version of intersection of two maps.
        auto lhs_it = lhs_nodes.begin();
        auto rhs_it = rhs_nodes.end();
        while (lhs_it != lhs_nodes.end() && rhs_it != rhs_nodes.end()) {
            if (lhs_it->first < rhs_it->first) {
                ++lhs_it;
            }
            else if (rhs_it->first < lhs_it->first) {
                ++rhs_it;
            }
            else {
                return false;
            }
        }
        return true;
    };
    //  3) Look for the best combination.
    auto n = max_subgraphs.size();
    std::vector<bool> compatibles(n^2);
    std::vector<float> value(n);
    for(auto i = 0; i<n; ++i) {
        value[i] = punctuation_f(max_subgraphs[i]);
        for (auto j=i; j<n; ++j) {
            auto compatible = compatible_f(max_subgraphs[i], max_subgraphs[j]);
            compatibles[i +j*n] = compatible;
            compatibles[i*n +j] = compatible;
        }
    }
    std::vector<float> sum_value(n);
    for(auto i = 0; i<n; ++i) {
        auto sum_values = value[i];
        for (auto j=0; j<n; ++j) {
            if (compatibles[i +j*n]) {
                sum_values += value[j];
            }
        }
        sum_value[i] = sum_values;
    }

    auto it = std::max_element(sum_value.begin(), sum_value.end());
    auto max_n = std::distance(sum_value.begin(), it);

    auto ret = 0.f;
    conceptual_graph mcs_graph;
    for (auto i = 0; i<n; ++i) {
        if (compatibles[i+max_n*n] || i==max_n) {
            mcs_graph += max_subgraphs[i];
        }
    }

    std::cout << "All candidates: " << std::endl;
    for (auto& graph : max_subgraphs) {
        std::cout << std::endl << "wn::distance::mcs" << std::endl;
        graph.print(std::cout);
    }
    std::cout << "Max graphs" << std::endl << std::endl;
    mcs_graph.print(std::cout);
    return *it;
}
