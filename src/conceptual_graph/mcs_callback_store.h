
#pragma once

#include <iostream>
#include <exception>
#include <boost/graph/mcgregor_common_subgraphs.hpp>
#include "conceptual_graph.h"
#include "conceptual_graph_data.h"
#include "mcgregor_common_subgraphs.h"

namespace wn {
    namespace mcs {

        using namespace boost;

        /* Doc for mcgregor_common_subgraphs
            http://www.boost.org/doc/libs/1_40_0/libs/graph/doc/mcgregor_common_subgraphs.html
            http://svn.kulitorum.com/RepSnapper/Libraries/Boost1.40/libs/graph/example/mcgregor_subgraphs_example.cpp
            https://www.ebi.ac.uk/msd-srv/ssm/papers/spe_csia.pdf
        */

        struct search_space_overflow : public std::runtime_error {
            search_space_overflow() : std::runtime_error("mcs::store_callback search space overflow") {};
        };

        template <typename GraphFirst, typename GraphSecond>
        struct store_callback {
            // Types for filtered graph
            typedef typename property_map<GraphFirst, vertex_index_t>::type VertexIndexMap;
            typedef shared_array_property_map<bool, VertexIndexMap> MembershipMap;
            typedef typename membership_filtered_graph_traits<_t_graph, MembershipMap>::graph_type
                  MembershipFilteredGraph;

            typedef typename std::tuple<MembershipFilteredGraph, MembershipFilteredGraph, conceptual_graph_corresponde, float> _t_subgraphs;

            store_callback(const GraphFirst& graph1,
                const GraphSecond& graph2,
                std::vector<std::unique_ptr<_t_subgraphs>> &out_vector,
                const wn::cmp_synset& cmp_synset,
                const wn::cmp_relation& cmp_relation,
                const float& search_space_max_size)
                : m_graph1(graph1), m_graph2(graph2), graphs(out_vector), cmp_synset(cmp_synset), cmp_relation(cmp_relation) {
                limit_search = search_space_max_size;
            }

            template <typename CorrespondenceMapFirstToSecond, typename CorrespondenceMapSecondToFirst>
            bool operator()(CorrespondenceMapFirstToSecond correspondence_map_1_to_2,
                            CorrespondenceMapSecondToFirst correspondence_map_2_to_1,
                            typename graph_traits<GraphFirst>::vertices_size_type subgraph_size) {
                --limit_search;
                //std::cout << limit_search << std::endl;
                if (subgraph_size < 2) {                    
                    return (limit_search>0);
                }

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
                float similarity = 0.f;
                BGL_FORALL_VERTICES_T(vertex1, m_graph1, GraphFirst) {
                    // Skip unmapped vertices
                    if (get(correspondence_map_1_to_2, vertex1) != graph_traits<GraphSecond>::null_vertex()) {
                        auto v2 = get(correspondence_map_1_to_2, vertex1);
                        correspondence[vertex1] = v2;
                        similarity += cmp_synset.similarity(m_graph1[vertex1], m_graph2[v2]);
                        //std::cout << "--------" << std::endl << vertex1 << " <-> " << get(correspondence_map_1_to_2, vertex1) << "\t sim_value = " << cmp_synset.similarity(m_graph1[vertex1], m_graph2[v2]) << std::endl;
                    }
                }
                
                auto nested = [](const conceptual_graph_corresponde& lhs, const conceptual_graph_corresponde& rhs) {
                    return std::all_of(lhs.begin(), lhs.end(), [&rhs](const conceptual_graph_corresponde::value_type& item){
                        auto it = rhs.find(item.first);
                        return (it != rhs.end() && it->second == item.second);
                    });
                };
                for (auto& g : graphs) {
                    if (nested(correspondence, get<2>(*g))) {
                        //std::cout << "-" << limit_search << std::endl;
                        return (limit_search>0);
                    }
                }

                // Append similarity due to relations...
                // TODO: This code snippet can misbehave if there are more than one edge between the two same nodes
                for (auto& vertices : correspondence) {
                    typename graph_traits<MembershipFilteredGraph>::out_edge_iterator it_edges_g1_begin, it_edges_g1_end;
                    typename graph_traits<MembershipFilteredGraph>::out_edge_iterator it_edges_g2_begin, it_edges_g2_end;
                    std::tie(it_edges_g1_begin, it_edges_g1_end) = boost::out_edges(vertices.first, subgraph1);
                    std::tie(it_edges_g2_begin, it_edges_g2_end) = boost::out_edges(vertices.second, subgraph2);
                    for (; it_edges_g1_begin != it_edges_g1_end; ++it_edges_g1_begin) {
                        auto target_g1 = boost::target(*it_edges_g1_begin, subgraph1);
                        for (auto it = it_edges_g2_begin; it != it_edges_g2_end; ++it) {
                            auto target_g2 = boost::target(*it, subgraph2);
                            if (subgraph1[target_g1] == subgraph2[target_g2]) {
                                similarity += cmp_relation.similarity(subgraph1[*it_edges_g1_begin], subgraph2[*it]);
                            }
                        }
                    }

                }

                //std::cout << "--- " << similarity << std::endl << std::endl;
                limit_search -= subgraph_size;
                graphs.push_back(std::unique_ptr<_t_subgraphs>(new _t_subgraphs(subgraph1, subgraph2, correspondence, similarity)));
                
                return (true);
            }

            private:
                const wn::cmp_synset& cmp_synset;
                const wn::cmp_relation& cmp_relation;
                const GraphFirst& m_graph1;
                const GraphSecond& m_graph2;
                std::vector<std::unique_ptr<_t_subgraphs>>& graphs;

                long limit_search;
        };
    }
}
