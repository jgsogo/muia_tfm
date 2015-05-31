
#pragma once

#include <iostream>
#include <boost/graph/mcgregor_common_subgraphs.hpp>
#include "conceptual_graph/conceptual_graph.h"

namespace wn {
    namespace mcs {

        using namespace boost;

        /* Doc for mcgregor_common_subgraphs
            http://www.boost.org/doc/libs/1_40_0/libs/graph/doc/mcgregor_common_subgraphs.html
            http://svn.kulitorum.com/RepSnapper/Libraries/Boost1.40/libs/graph/example/mcgregor_subgraphs_example.cpp
            https://www.ebi.ac.uk/msd-srv/ssm/papers/spe_csia.pdf
        */

        template <typename GraphFirst, typename GraphSecond>
        struct store_callback {
            store_callback(const GraphFirst& graph1, const GraphSecond& graph2) : m_graph1(graph1), m_graph2(graph2) {
            }

            template <typename CorrespondenceMapFirstToSecond, typename CorrespondenceMapSecondToFirst>
            bool operator()(CorrespondenceMapFirstToSecond correspondence_map_1_to_2,
                            CorrespondenceMapSecondToFirst correspondence_map_2_to_1,
                            typename graph_traits<GraphFirst>::vertices_size_type subgraph_size) {

                conceptual_graph graph;
                BGL_FORALL_VERTICES_T(vertex1, m_graph1, GraphFirst) {
                  // Skip unmapped vertices
                  if (get(correspondence_map_1_to_2, vertex1) != graph_traits<GraphSecond>::null_vertex()) {
                    graph.add_node(m_graph1[vertex1]);
                    std::cout << vertex1 << " <-> " << get(correspondence_map_1_to_2, vertex1) << std::endl;
                  }
                }
                std::cout << "---" << std::endl;
                graphs.push_back(graph);
                return (true);
            }

            private:
                const GraphFirst& m_graph1;
                const GraphSecond& m_graph2;
                std::vector<conceptual_graph> graphs;
        };
    }
}
