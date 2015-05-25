
#include "conceptual_graph.h"
#include "conceptual_graph_data.h"

#include "relation.h"

using namespace wn;

class conceptual_graph_printer : public boost::default_writer {
    public:
        conceptual_graph_printer(const _t_graph& g) : graph(g) {}
        void operator()(std::ostream& os, const boost::graph_traits<_t_graph>::vertex_descriptor& v) const {
            os << "[label=\"" << graph[v] << "\"]";
        }
        void operator()(std::ostream& os, const boost::graph_traits<_t_graph>::edge_descriptor& e) const {
            const relation& rel = graph[e];
            os << "[label=\"" << rel << "\"]";
        }
    private:
        const _t_graph& graph;
};


conceptual_graph::conceptual_graph() : d(new data()) {
}

conceptual_graph::~conceptual_graph() {
    delete d;
}

conceptual_graph::synset_id conceptual_graph::add_node(const wnb::synset& s) {
    auto u = boost::add_vertex(d->graph);
    d->graph[u] = s;
    return u;
}

void conceptual_graph::add_relation(const synset_id& s1, const synset_id& s2, int rel_type) {
    relation rel;
    rel.type = rel_type;
    boost::add_edge(s1, s2, rel, d->graph);
}

void conceptual_graph::print(std::ostream& os) const {
    conceptual_graph_printer writer(d->graph);
    d->print(os, d->graph, writer);
}

