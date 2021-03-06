
#include "conceptual_graph.h"
#include <algorithm>
#include "conceptual_graph_data.h"

using namespace wn;
using namespace std;

class conceptual_graph_printer : public boost::default_writer {
    public:
        conceptual_graph_printer(const _t_graph& g, bool only_headword = false) : graph(g), only_headword(only_headword) {}
        void operator()(std::ostream& os, const boost::graph_traits<_t_graph>::vertex_descriptor& v) const {
            auto synset = graph[v];
            if (only_headword) {
                os << "[label=\"" << synset.words[0] << "\"]";
            }
            else {
                os << "[label=\"" << graph[v] << "\"]";
            }
        }
        void operator()(std::ostream& os, const boost::graph_traits<_t_graph>::edge_descriptor& e) const {
            const relation& rel = graph[e];
            os << "[label=\"" << rel << "\"]";
        }
    private:
        const _t_graph& graph;
        bool only_headword;
};


conceptual_graph::conceptual_graph() : d(new data()) {
}

conceptual_graph::conceptual_graph(const conceptual_graph& other) : d(new data(*other.d)) {
}

conceptual_graph& conceptual_graph::operator+=(const conceptual_graph& other) {
    (*d) += (*other.d);
    return *this;
}

conceptual_graph& conceptual_graph::operator=(const conceptual_graph& other) {
    delete d;
    d = new data(*other.d);
    return *this;
}

conceptual_graph::~conceptual_graph() {
    delete d;
}

conceptual_graph::synset_id conceptual_graph::add_node(const synset& s) {
    auto u = boost::add_vertex(d->graph);
    d->graph[u] = s;
    return u;
}

synset conceptual_graph::get_node(const synset_id& s1) const {
    return d->graph[s1];
}

void conceptual_graph::add_relation(const synset_id& s1, const synset_id& s2, const relation::type& rel_type) {
    relation rel;
    rel.type_ = rel_type;
    rel.source = get_node(s1);
    rel.target = get_node(s2);
    boost::add_edge(s1, s2, rel, d->graph);
}

map<conceptual_graph::synset_id, synset> conceptual_graph::get_nodes() const {
    map<synset_id, synset> ret;
    boost::graph_traits<_t_graph>::vertex_iterator v, v_end;
    tie(v, v_end) = boost::vertices(d->graph);
    for (; v!=v_end; ++v) {
        ret[*v] = d->graph[*v];
    }
    return ret;
}

vector<relation> conceptual_graph::get_edges() const {
    vector<relation> ret;
    boost::graph_traits<_t_graph>::edge_iterator e, e_end;
    tie(e, e_end) = boost::edges(d->graph);
    for (; e != e_end; ++e) {
        ret.push_back(d->graph[*e]);
    }
    return ret;
}

vector<relation> conceptual_graph::get_outgoing_edges(const synset_id& id) const {
    vector<relation> ret;
    boost::graph_traits<_t_graph>::out_edge_iterator e, e_end;
    tie(e, e_end) = boost::out_edges(id, d->graph);
    for (; e!=e_end; ++e) {
        auto v = target(*e, d->graph);
        ret.push_back(d->graph[*e]);
    }
    return ret;
}

void conceptual_graph::print(std::ostream& os, bool only_headword) const {
    conceptual_graph_printer writer(d->graph, only_headword);
    d->print(os, d->graph, writer);
}
