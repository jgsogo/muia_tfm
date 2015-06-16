
#include "mcs.h"
#include "../conceptual_graph/mcgregor_common_subgraphs.h"

using namespace wn;
using namespace wn::distance;


mcs::mcs(const base_synset& base_distance, const base_relation& dist_relation) : base_graph(base_distance, dist_relation) {
}

mcs::~mcs() {
}

//! Compute max_similarity between two conceptual_graphs (tolerances must belong to [0, 1))
float mcs::max_similarity(const conceptual_graph& s1, const conceptual_graph& s2,
                          float synset_tolerance, float relation_tolerance,
                          conceptual_graph& result,
                          conceptual_graph_corresponde& s1_to_result,
                          conceptual_graph_corresponde& s2_to_result) const {
    assert(synset_tolerance >= 0.f && synset_tolerance < 1.f);
    assert(relation_tolerance >= 0.f && relation_tolerance < 1.f);

    struct synset_cmp : cmp_synset {
        synset_cmp(const base_synset& syn) : dist_synset(syn) {}
        virtual bool operator() (const synset& a, const synset& b) const {
            //std::cout << dist_synset(a, b) << " <= " << synset_threshold << " = " << (dist_synset(a, b) <= synset_threshold) << std::endl;
            return dist_synset(a, b) <= synset_threshold;
        }
        virtual float similarity(const synset& a, const synset& b) const {
            return dist_synset.similarity(a, b);
        }
        const base_synset& dist_synset;
        float synset_threshold;
    };

    struct relation_cmp : cmp_relation {
        relation_cmp(const base_relation& rel) : dist_relation(rel) {}
        virtual bool operator() (const relation& a, const relation& b) const {
            return dist_relation(a, b) <= edge_threshold;
        }
        virtual float similarity(const relation& a, const relation& b) const {
            return dist_relation.similarity(a, b);
        }
        const base_relation& dist_relation;
        float edge_threshold;
    };

    synset_cmp cmp_synset(dist_synset);
    cmp_synset.synset_threshold = dist_synset.lower_bound() + synset_tolerance*(dist_synset.upper_bound() - dist_synset.lower_bound());

    relation_cmp cmp_relation(dist_relation);
    cmp_relation.edge_threshold = dist_relation.lower_bound() + relation_tolerance*(dist_relation.upper_bound()-dist_relation.lower_bound());

    typedef std::tuple<conceptual_graph, conceptual_graph_corresponde, conceptual_graph_corresponde, float> _t_subgraph_data;
    std::vector<_t_subgraph_data> mcs_subgraphs;
    mcgregor_common_subgraphs(s1, s2, cmp_synset, cmp_relation, mcs_subgraphs);

    // Rank candidates and keep the best one (minimizes distance)
    auto it = std::max_element(mcs_subgraphs.begin(), mcs_subgraphs.end(), [](_t_subgraph_data& lhs, _t_subgraph_data& rhs){
        return get<3>(lhs) < get<3>(rhs);
    });

    if (it != mcs_subgraphs.end()) {
        result = get<0>(*it);
        s1_to_result = get<1>(*it);
        s2_to_result = get<2>(*it);
        auto max_value = get<3>(*it);

        /*
        std::cout << "\t - init print_best_graph" << std::endl;
        std::cout << std::endl << "Best graph:" << std::endl << std::endl;
        best.print(std::cout);
        std::cout << std::endl << "Punctuation = " << max_value << std::endl;
        std::cout << "Correspondences = " << std::endl;
        auto it_cor_s1 = correspondence_s1.begin();
        auto it_cor_s2 = correspondence_s2.begin();
        for (; it_cor_s1 != correspondence_s1.end(); ++it_cor_s1, ++it_cor_s2) {
        std::cout << it_cor_s1->first << ">>> " << it_cor_s1->second << " <--> " << it_cor_s2->second << std::endl;
        }
        std::cout << "\t - end  print_best_graph" << std::endl;
        */
        return max_value;
    }
    else {
        return 0.f;
    }
}



