

#include "graph_distance.h"

using namespace wn;
using namespace wn::distance;

base_graph::base_graph(const base_synset& dist) : dist_synset(dist) {
}

float base_graph::min(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const {
    auto s1_nodes = s1.get_nodes();
    auto s2_nodes = s2.get_nodes();

    return abs(int(s2_nodes.size()) - int(s1_nodes.size()))*node_penalization;
    // TODO: There is a more fine grained estimation of minimum based on number of edges.
}

float base_graph::max(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const {
    auto s1_nodes = s1.get_nodes();
    auto s2_nodes = s2.get_nodes();
    auto due_nodes = std::min(s1_nodes.size(), s2_nodes.size())*dist_synset.max();
    due_nodes += abs(int(s2_nodes.size()) - int(s1_nodes.size()))*node_penalization;

    auto s1_edges = s1.get_edges();
    auto s2_edges = s2.get_edges();
    auto due_edges = std::min(s1_edges.size(), s2_edges.size())*this->max_edge_distance();
    due_edges += abs(int(s1_edges.size()) - int(s2_edges.size()))*edge_penalization;
    return due_nodes + due_edges;
}
