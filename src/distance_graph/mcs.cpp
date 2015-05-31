
#include "mcs.h"

using namespace wn;
using namespace wn::distance;


mcs::mcs(const base_synset& base_distance, const base_relation& dist_relation) : base_graph(base_distance, dist_relation) {
}

mcs::~mcs() {
}

float mcs::min_distance(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const {
    //mcgregor_common_subgraphs(s1, s2);
    return 0;
}
