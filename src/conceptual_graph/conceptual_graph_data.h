
#pragma once

# include <boost/graph/graph_traits.hpp>
# include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>

#include "conceptual_graph.h"
#include "relation.h"

namespace wn {

    typedef boost::adjacency_list<boost::vecS, boost::vecS,
                                  boost::bidirectionalS,
                                  synset, relation> _t_graph;

    struct conceptual_graph::data {
        data() {};
        data(const data& other) {
            graph = other.graph;
        };

        data& operator+=(const data& other) {
            _t_graph::vertex_iterator v, v_end;
            std::tie(v, v_end) = vertices(other.graph);
            std::map<std::size_t, std::size_t> veq;
            for (; v != v_end; ++v) {
                auto u = add_vertex(graph);
                graph[u] = other.graph[*v];
                veq[*v] = u;
            }

            std::tie(v, v_end) = vertices(other.graph);
            for (; v != v_end; ++v) {
                _t_graph::out_edge_iterator e, e_end;
                tie(e, e_end) = boost::out_edges(*v, other.graph);
                for (; e != e_end; ++e) {
                    auto tgt = target(*e, other.graph);

                    relation rel = other.graph[*e];
                    boost::add_edge(veq[*v], veq[tgt], rel, graph);
                }
            }
            return *this;
        }

        _t_graph graph;

        template <class TPrinter = boost::default_writer>
        std::ostream& print(std::ostream& os, _t_graph& graph, TPrinter& writer) {
            boost::write_graphviz(os, graph, writer, writer);
            return os;
        }

    };

}
