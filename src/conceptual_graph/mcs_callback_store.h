
#pragma once

#include <iostream>
#include <boost/graph/mcgregor_common_subgraphs.hpp>
#include "conceptual_graph.h"
#include "conceptual_graph_data.h"

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
            // Types for filtered graph
            typedef typename property_map<GraphFirst, vertex_index_t>::type VertexIndexMap;
            typedef shared_array_property_map<bool, VertexIndexMap> MembershipMap;
            typedef typename membership_filtered_graph_traits<_t_graph, MembershipMap>::graph_type
                  MembershipFilteredGraph;

            store_callback(const GraphFirst& graph1,
                const GraphSecond& graph2,
                std::vector < std::tuple < MembershipFilteredGraph, MembershipFilteredGraph, std::map<std::size_t, std::size_t>>> &out_vector) : m_graph1(graph1), m_graph2(graph2), graphs(out_vector) {
            }

            template <typename CorrespondenceMapFirstToSecond, typename CorrespondenceMapSecondToFirst>
            bool operator()(CorrespondenceMapFirstToSecond correspondence_map_1_to_2,
                            CorrespondenceMapSecondToFirst correspondence_map_2_to_1,
                            typename graph_traits<GraphFirst>::vertices_size_type subgraph_size) {

                // Fill membership map for first graph
                MembershipMap membership_map1(num_vertices(m_graph1), get(vertex_index, m_graph1));
                fill_membership_map<GraphFirst>(m_graph1, correspondence_map_1_to_2, membership_map1);

                // Fill membership map for second graph
                MembershipMap membership_map2(num_vertices(m_graph2), get(vertex_index, m_graph2));
                fill_membership_map<GraphFirst>(m_graph2, correspondence_map_2_to_1, membership_map2);

                // Generate filtered graphs using membership map
                MembershipFilteredGraph subgraph1 = make_membership_filtered_graph(m_graph1, membership_map1);
                MembershipFilteredGraph subgraph2 = make_membership_filtered_graph(m_graph2, membership_map2);

                // Build corresponde-map between graph1->graph2
                std::map<std::size_t, std::size_t> correspondence;
                BGL_FORALL_VERTICES_T(vertex1, m_graph1, GraphFirst) {
                    // Skip unmapped vertices
                    if (get(correspondence_map_1_to_2, vertex1) != graph_traits<GraphSecond>::null_vertex()) {
                        correspondence[vertex1] = get(correspondence_map_1_to_2, vertex1);
                    }
                }

                graphs.push_back(std::make_tuple(subgraph1, subgraph2, correspondence));
                return (true);
            }

            private:
                const GraphFirst& m_graph1;
                const GraphSecond& m_graph2;
                std::vector<std::tuple<MembershipFilteredGraph, MembershipFilteredGraph, std::map<std::size_t, std::size_t>>>& graphs;
        };
    }
}
