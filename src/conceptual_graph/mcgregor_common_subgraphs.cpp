

#include "mcgregor_common_subgraphs.h"
#include <numeric>
#include <boost/graph/mcgregor_common_subgraphs.hpp>
#include "mcs_callback_print.h"
#include "mcs_callback_store.h"


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
        const cmp_synset& cmp_synset_,
        const cmp_relation& cmp_relation_,
        std::vector<std::tuple<conceptual_graph, conceptual_graph_corresponde, conceptual_graph_corresponde, float>>& ret) {

        struct equivalence_func {
            equivalence_func(const _t_graph& g1,
                const _t_graph& g2,
                std::function<bool(const synset&, const synset&)> synset_dist,
                std::function<bool(const relation&, const relation&)> relation_dist)
                : graph1(g1), graph2(g2), dist_synset(synset_dist), dist_relation(relation_dist) {
            };

            bool operator()(graph_traits<_t_graph>::vertex_descriptor v1, graph_traits<_t_graph>::vertex_descriptor v2) {
                return dist_synset(graph1[v1], graph2[v2]);
            };
            bool operator()(graph_traits<_t_graph>::edge_descriptor e1, graph_traits<_t_graph>::edge_descriptor e2) {
                return dist_relation(graph1[e1], graph2[e2]);
            };

            std::function<bool(const synset&, const synset&)> dist_synset;
            std::function<bool(const relation&, const relation&)> dist_relation;
            const _t_graph& graph1;
            const _t_graph& graph2;
        };
        equivalence_func funcs(lhs.d->graph, rhs.d->graph, cmp_synset_, cmp_relation_);

        /*
        // Print out all connected common subgraphs between graph1 and graph2.
        mcs::print_callback<_t_graph, _t_graph> my_callback(lhs.d->graph, rhs.d->graph);
        mcgregor_common_subgraphs_unique(lhs.d->graph, rhs.d->graph, true, my_callback,
        edges_equivalent(funcs).vertices_equivalent(funcs));
        */

        // Store all connected common subgraphs between graph1 and graph2 (from both perspectives).
        typedef mcs::store_callback<_t_graph, _t_graph> store_callback;
        std::vector<std::tuple<store_callback::MembershipFilteredGraph, store_callback::MembershipFilteredGraph, conceptual_graph_corresponde, float>> subgraphs;
        store_callback mcs_graphs(lhs.d->graph, rhs.d->graph, subgraphs, cmp_synset_, cmp_relation_);
        mcgregor_common_subgraphs_unique(lhs.d->graph, rhs.d->graph, true, mcs_graphs,
            edges_equivalent(funcs).vertices_equivalent(funcs));

        /* Combination of subgraphs must be done here, where I have original node_ids (I have filtered graphs).
        The objective is to return every possible combination of subgraphs which is compatible; but it
        must be compatible in graph1 and graph2
        */
        auto compatible_correspondences = [](const conceptual_graph_corresponde& lhs, const conceptual_graph_corresponde& rhs)->bool {
            // Two correspondences are compatible if they don't share any common element;
            for (auto& it_lhs : lhs) {
                if (rhs.find(it_lhs.first) != rhs.end()) {
                    return false;
                }
            }
            return true;
        };
        auto compatible_f = [](const store_callback::MembershipFilteredGraph& g, const conceptual_graph_corresponde& correspondence_graph)->bool{
            // Two graphs are compatible if they don't share any common element;
            store_callback::MembershipFilteredGraph::vertex_iterator v, v_end;
            std::tie(v, v_end) = vertices(g);
            for (; v != v_end; ++v) {
                if (correspondence_graph.find(*v) != correspondence_graph.end()) {
                    return false;
                }
            }
            return true;
        };
        auto compatible_pairs = [&compatible_f](const std::tuple<store_callback::MembershipFilteredGraph, store_callback::MembershipFilteredGraph, conceptual_graph_corresponde, float>& lhs,
                                                const conceptual_graph_corresponde& correspondence_graph1,
                                                const conceptual_graph_corresponde& correspondence_graph2)->bool {
            // Tow pairs of graphs are compatible if each one-to-one comparison is also compatible.
            auto g1_map = std::get<0>(lhs);
            auto g2_map = std::get<1>(lhs);
            return (compatible_f(g1_map, correspondence_graph1) && compatible_f(g2_map, correspondence_graph2));
        };

        /* Building conceptual graph from filtered one and building correspondence maps
        */
        auto append_correspondence_tuple = [&lhs, &rhs](const std::tuple<store_callback::MembershipFilteredGraph, store_callback::MembershipFilteredGraph, conceptual_graph_corresponde, float>& pair,
                                                        conceptual_graph& graph,
                                                        conceptual_graph_corresponde& correspondence_to_lhs,
                                                        conceptual_graph_corresponde& correspondence_to_rhs) {
            // Add nodes
            std::map<size_t, size_t> tmp_map;
            store_callback::MembershipFilteredGraph::vertex_iterator v, v_end;
            std::tie(v, v_end) = vertices(std::get<0>(pair));
            for (; v != v_end; ++v) {
                auto u1 = graph.add_node(lhs.d->graph[*v]);
                tmp_map[*v] = u1;
                correspondence_to_lhs[u1] = *v;
                correspondence_to_rhs[u1] = (std::get<2>(pair)).at(*v);
            }
            // Add edges
            std::tie(v, v_end) = vertices(std::get<0>(pair));
            for (; v != v_end; ++v) {
                store_callback::MembershipFilteredGraph::out_edge_iterator e, e_end;
                tie(e, e_end) = boost::out_edges(*v, std::get<0>(pair));
                for (; e != e_end; ++e) {
                    auto tgt = target(*e, std::get<0>(pair));
                    graph.add_relation(tmp_map[*v], tmp_map[tgt], lhs.d->graph[*e].type);
                }
            }
        };

        // We need to check for all permutations
        std::cout << "We will do " << subgraphs.size() << "! permutations" << std::endl;
        getchar();
        std::vector<size_t> indexes(subgraphs.size());
        std::iota(indexes.begin(), indexes.end(), 0);

        std::vector<bool> compatibility_matrix(subgraphs.size()*subgraphs.size());
        for (auto i = 0; i < subgraphs.size(); ++i) {
            for (auto j = i; j < subgraphs.size(); ++j) {
                if (i == j) {
                    compatibility_matrix[i*subgraphs.size() + j] = false;
                }
                else {
                    auto compatible = compatible_correspondences(get<2>(subgraphs[i]), get<2>(subgraphs[j]));
                    compatibility_matrix[i*subgraphs.size() + j] = compatible;
                    compatibility_matrix[j*subgraphs.size() + i] = compatible;
                }
            }
        }

        
        do {
            std::cout << ">>> graph[" << indexes[0] << "]" << std::endl;
            conceptual_graph graph;
            conceptual_graph_corresponde correspondence_to_lhs;
            conceptual_graph_corresponde correspondence_to_rhs;
            float similarity = 0.f;
            // Append myself
            append_correspondence_tuple(subgraphs[indexes[0]], graph, correspondence_to_lhs, correspondence_to_rhs);
            for (auto j = 1; j < indexes.size(); ++j) {
                if (compatibility_matrix[indexes[0] * subgraphs.size() + indexes[j]]) {
                    std::cout << "\t" << indexes[j] << " compatible." << std::endl;
                    append_correspondence_tuple(subgraphs[indexes[j]], graph, correspondence_to_lhs, correspondence_to_rhs);
                    similarity += get<3>(subgraphs[indexes[j]]);
                }
                else {
                    std::cout << "\t" << indexes[j] << " NON compatible." << std::endl;
                }
            }
            std::cout << "\t sim_value = " << similarity << std::endl;
            ret.insert(ret.end(), make_tuple(graph, correspondence_to_lhs, correspondence_to_rhs, similarity));
        } while (next_permutation(indexes.begin(), indexes.end()));
    }
}
