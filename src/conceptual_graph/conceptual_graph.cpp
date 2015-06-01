
#include "conceptual_graph.h"
#include <algorithm>
#include "conceptual_graph_data.h"
#include <boost/graph/mcgregor_common_subgraphs.hpp>
#include "mcs_callback_print.h"
#include "mcs_callback_store.h"

using namespace wn;
using namespace std;

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

conceptual_graph::conceptual_graph(const conceptual_graph& other) : d(new data(*other.d)) {
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

void conceptual_graph::add_relation(const synset_id& s1, const synset_id& s2, int rel_type) {
    relation rel;
    rel.type = rel_type;
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

void conceptual_graph::print(std::ostream& os) const {
    conceptual_graph_printer writer(d->graph);
    d->print(os, d->graph, writer);
}


namespace wn {
    using namespace boost;

    /* Doc for mcgregor_common_subgraphs
        http://www.boost.org/doc/libs/1_40_0/libs/graph/doc/mcgregor_common_subgraphs.html
        http://svn.kulitorum.com/RepSnapper/Libraries/Boost1.40/libs/graph/example/mcgregor_subgraphs_example.cpp
        https://www.ebi.ac.uk/msd-srv/ssm/papers/spe_csia.pdf
    */
    void mcgregor_common_subgraphs(
        const conceptual_graph& lhs,
        const conceptual_graph& rhs,
        std::function<bool (const synset&, const synset&)> cmp_synset,
        std::function<bool (const relation&, const relation&)> cmp_relation,
        std::vector<conceptual_graph>& ret) {

        struct equivalence_func {
            equivalence_func(const _t_graph& g1,
                        const _t_graph& g2,
                        std::function<bool (const synset&, const synset&)> synset_dist,
                        std::function<bool (const relation&, const relation&)> relation_dist)
                        : graph1(g1), graph2(g2), dist_synset(synset_dist), dist_relation(relation_dist) {
            };

            bool operator()(graph_traits<_t_graph>::vertex_descriptor v1, graph_traits<_t_graph>::vertex_descriptor v2) {
                return dist_synset(graph1[v1], graph2[v2]);
            };
            bool operator()(graph_traits<_t_graph>::edge_descriptor e1, graph_traits<_t_graph>::edge_descriptor e2) {
                return dist_relation(graph1[e1], graph2[e2]);
            };

            std::function<bool (const synset&, const synset&)> dist_synset;
            std::function<bool (const relation&, const relation&)> dist_relation;
            const _t_graph& graph1;
            const _t_graph& graph2;
        };
        equivalence_func funcs(lhs.d->graph, rhs.d->graph, cmp_synset, cmp_relation);

        /*
        // Print out all connected common subgraphs between graph1 and graph2.
        mcs::print_callback<_t_graph, _t_graph> my_callback(lhs.d->graph, rhs.d->graph);
        mcgregor_common_subgraphs_unique(lhs.d->graph, rhs.d->graph, true, my_callback,
            edges_equivalent(funcs).vertices_equivalent(funcs));
        */

        // Store all connected common subgraphs between graph1 and graph2.
        typedef mcs::store_callback<_t_graph, _t_graph> store_callback;
        std::vector<store_callback::MembershipFilteredGraph> subgraphs;
        store_callback mcs_graphs(lhs.d->graph, rhs.d->graph, subgraphs);
        mcgregor_common_subgraphs_unique(lhs.d->graph, rhs.d->graph, true, mcs_graphs,
            edges_equivalent(funcs).vertices_equivalent(funcs));

        for (auto& graph : subgraphs) {
            print_graph(graph);
            auto it = ret.insert(ret.end(), conceptual_graph());
            store_callback::MembershipFilteredGraph::vertex_iterator v, v_end;
            std::tie(v, v_end) = vertices(graph);
            for (; v != v_end; ++v) {
                (*it).add_node(lhs.d->graph[*v]);
            }

            std::tie(v, v_end) = vertices(graph);
            for (; v != v_end; ++v) {
                store_callback::MembershipFilteredGraph::out_edge_iterator e, e_end;
                tie(e, e_end) = boost::out_edges(*v, graph);
                for (; e != e_end; ++e) {
                    auto tgt = target(*e, graph);
                    (*it).add_relation(*v, tgt, lhs.d->graph[*e].type);
                }
            }
        }

    }
}
