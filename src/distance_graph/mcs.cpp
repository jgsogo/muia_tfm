
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

    mcgregor_common_subgraphs(s1, s2, cmp_synset, cmp_relation);
    return 0;
}