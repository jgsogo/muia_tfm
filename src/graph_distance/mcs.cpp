
#include "mcs.h"

using namespace wn;
using namespace wn::distance;


mcs::mcs(const base_synset& base_distance) : graph_base(base_distance) {
}

mcs::~mcs() {
}

float mcs::min_distance(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const {
    s1.mcgregor_common_subgraphs(s2);
    return 0;
}

float mcs::max_edge_distance() const {
    return 1.f;
}
