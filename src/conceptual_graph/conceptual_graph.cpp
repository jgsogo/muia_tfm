
#include "conceptual_graph.h"
#include "conceptual_graph_data.h"
#include <boost/graph/mcgregor_common_subgraphs.hpp>

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

    template <typename GraphFirst, typename GraphSecond>
    struct print_callback {
        print_callback(const GraphFirst& graph1, const GraphSecond& graph2) : m_graph1(graph1), m_graph2(graph2) {
        }

        template <typename CorrespondenceMapFirstToSecond, typename CorrespondenceMapSecondToFirst>
        bool operator()(CorrespondenceMapFirstToSecond correspondence_map_1_to_2,
                        CorrespondenceMapSecondToFirst correspondence_map_2_to_1,
                        typename graph_traits<GraphFirst>::vertices_size_type subgraph_size) {
            std::cout << "print_callback::operator() " << std::endl;
            std::cout << "subgraph_size = " << subgraph_size << std::endl;
            // Print out correspondences between vertices
            BGL_FORALL_VERTICES_T(vertex1, m_graph1, GraphFirst) {
                std::cout << "\t" << vertex1 << std::endl;
                // Skip unmapped vertices
                if (get(correspondence_map_1_to_2, vertex1) != graph_traits<GraphSecond>::null_vertex()) {
                    std::cout << vertex1 << " <-> " << get(correspondence_map_1_to_2, vertex1) << std::endl;
                }
            }

            std::cout << "---" << std::endl;
            return (true);
        }

        private:
            const GraphFirst& m_graph1;
            const GraphSecond& m_graph2;
    };



    void mcgregor_common_subgraphs(
        const conceptual_graph& lhs,
        const conceptual_graph& rhs,
        std::function<bool (const synset&, const synset&)> cmp_synset,
        std::function<bool (const relation&, const relation&)> cmp_relation) {

        print_callback<_t_graph, _t_graph> my_callback(lhs.d->graph, rhs.d->graph);

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


        // Print out all connected common subgraphs between graph1 and graph2.
        std::cout << "COMPUTE McGREGOR" << std::endl;
        mcgregor_common_subgraphs_unique(lhs.d->graph, rhs.d->graph, true, my_callback,
            edges_equivalent(funcs).
            vertices_equivalent(funcs));

        /*
        // Assume both graphs were defined with implicit vertex name,
        // edge name, and vertex index properties
        property_map<_t_graph, int synset::*> vname_map1 = get(&synset::id, lhs.d->graph);
        property_map<_t_graph, int synset::*> vname_map2 = get(&synset::id, rhs.d->graph);
        //property_map<_t_graph, vertex_name_t> vname_map1 = get(id, lhs);
        //property_map<_t_graph, vertex_name_t> vname_map2 = get(id, rhs);

        property_map<_t_graph, int relation::*>::const_type ename_map1 = get(&relation::type, lhs.d->graph);
        property_map<_t_graph, int relation::*>::const_type ename_map2 = get(&relation::type, rhs.d->graph);

        struct vertices_equivalents {
            vertices_equivalents(const _t_graph& g1, const _t_graph& g2) : m_graph1(g1), m_graph2(g2) {};
            bool operator()(graph_traits<_t_graph>::vertex_descriptor v1, graph_traits<_t_graph>::vertex_descriptor v2) {
                return true;
            };
            const _t_graph& m_graph1;
            const _t_graph& m_graph2;
        };
        vertices_equivalents eqv(lhs.d->graph, rhs.d->graph);

        // Print out all connected common subgraphs between graph1 and graph2.
        std::cout << "COMPUTE McGREGOR" << std::endl;
        mcgregor_common_subgraphs_unique(lhs.d->graph, rhs.d->graph, true, my_callback,
            edges_equivalent(make_property_map_equivalent(ename_map1, ename_map2)).
            vertices_equivalent(eqv));
        */
    }
}
