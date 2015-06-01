
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

        _t_graph graph;

        template <class TPrinter = boost::default_writer>
        std::ostream& print(std::ostream& os, _t_graph& graph, TPrinter& writer) {
            boost::write_graphviz(os, graph, writer, writer);
            return os;
        }

    };

}
