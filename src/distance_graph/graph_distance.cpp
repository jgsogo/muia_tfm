

#include "graph_distance.h"

using namespace wn;
using namespace wn::distance;

base_graph::base_graph(const base_synset& dist, const base_relation& dist_relation) : dist_synset(dist), dist_relation(dist_relation) {
}

float base_graph::lower_bound(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const {
    // Due to nodes
    auto s1_nodes = s1.get_nodes();
    auto s2_nodes = s2.get_nodes();
    auto min_elements = std::min(s1_nodes.size(), s2_nodes.size());
    auto due_nodes = min_elements*dist_synset.lower_bound() + abs(int(s2_nodes.size()) - int(s1_nodes.size()))*node_penalization;

    // Due to edges 
    auto s1_edges = s1.get_edges();
    auto s2_edges = s2.get_edges();
    auto min_edges = std::min(s1_edges.size(), s2_edges.size());
    auto due_edges = min_edges*dist_relation.lower_bound() + abs(int(s1_edges.size()) - int(s2_edges.size()))*edge_penalization;

    return due_nodes + due_edges;
}

float base_graph::upper_bound(const conceptual_graph& s1, const conceptual_graph& s2, float node_penalization, float edge_penalization) const {
    // Due to nodes
    auto s1_nodes = s1.get_nodes();
    auto s2_nodes = s2.get_nodes();
    auto min_elements = std::min(s1_nodes.size(), s2_nodes.size());
    auto due_nodes = min_elements*dist_synset.upper_bound() + abs(int(s2_nodes.size()) - int(s1_nodes.size()))*node_penalization;

    // Due to edges
    auto s1_edges = s1.get_edges();
    auto s2_edges = s2.get_edges();
    auto min_edges = std::min(s1_edges.size(), s2_edges.size());
    auto due_edges = min_edges*dist_relation.upper_bound() + abs(int(s1_edges.size()) - int(s2_edges.size()))*edge_penalization;

    return due_nodes + due_edges;
}
