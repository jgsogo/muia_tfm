

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
                const cmp_synset& cmp_synset_,
                const cmp_relation& cmp_relation_)
                : graph1(g1), graph2(g2), dist_synset(cmp_synset_), dist_relation(cmp_relation_) {
            };

            bool operator()(graph_traits<_t_graph>::vertex_descriptor v1, graph_traits<_t_graph>::vertex_descriptor v2) {
                return dist_synset(graph1[v1], graph2[v2]);
            };
            bool operator()(graph_traits<_t_graph>::edge_descriptor e1, graph_traits<_t_graph>::edge_descriptor e2) {
                return dist_relation(graph1[e1], graph2[e2]);
            };

            const cmp_synset& dist_synset;
            const cmp_relation& dist_relation;
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

        auto n_subgraphs = subgraphs.size();
        // Build compatibility matrix
        std::vector<bool> compatibility_matrix(n_subgraphs*n_subgraphs);
        for (auto i = 0; i < n_subgraphs; ++i) {
            for (auto j = i; j < n_subgraphs; ++j) {
                if (i == j) {
                    compatibility_matrix[i*n_subgraphs + j] = false;
                }
                else {
                    auto compatible = compatible_correspondences(get<2>(subgraphs[i]), get<2>(subgraphs[j]));
                    compatibility_matrix[i*n_subgraphs + j] = compatible;
                    compatibility_matrix[j*n_subgraphs + i] = compatible;
                }
            }
        }

        /*
        std::cout << "Compatibility matrix: " << subgraphs.size() << std::endl;
        for (auto i = 0; i < subgraphs.size(); ++i) {
            for (auto j = 0; j < subgraphs.size(); ++j) {
                std::cout << compatibility_matrix[i*subgraphs.size() + j] << " ";
            }
            std::cout << std::endl;
        }
        getchar();
        */

        // Build all posible compatible combinations (without order)
        typedef std::vector<std::size_t> _t_indexes;
        std::vector<_t_indexes> compatible_subgraphs;
        auto filter_compatibles = [&compatibility_matrix, &n_subgraphs](const _t_indexes& original, const std::size_t& row)->_t_indexes{
            _t_indexes ret;
            for (auto& i : original) {
                if (compatibility_matrix[row*n_subgraphs + i]) {
                    ret.push_back(i);
                }
            }
            return ret;
        };


        std::function<std::vector<_t_indexes>(const _t_indexes&)> recurse_indexes = [&recurse_indexes, &filter_compatibles](const _t_indexes& indexes_)->std::vector<_t_indexes>{
            std::vector<_t_indexes> ret;
            if (indexes_.size() == 1) {
                ret.insert(ret.end(), { indexes_[0] });
            }
            else {
                for (auto& i : indexes_) {
                    _t_indexes aux = filter_compatibles(indexes_, i);
                    if (aux.size()) { // Always look for maximum correpondence
                        std::vector<_t_indexes> tmp = recurse_indexes(aux);
                        for (auto& seq : tmp) {
                            auto it = ret.insert(ret.end(), { i });
                            it->insert(it->end(), seq.begin(), seq.end());
                        }
                    }
                    else {
                        ret.insert(ret.end(), { i });
                    }
                }
            }
            return ret;
        };

        std::vector<std::size_t> indexes(n_subgraphs);
        std::iota(indexes.begin(), indexes.end(), 0);
        auto all_compatible_combinations = recurse_indexes(indexes);

        // Filter combinations
        decltype(all_compatible_combinations) all_compatible_filtered;
        for (auto& comb : all_compatible_combinations) {
            std::sort(comb.begin(), comb.end());
            auto repeated = std::any_of(all_compatible_filtered.begin(), all_compatible_filtered.end(), [&comb](const _t_indexes& item)->bool{
                auto it_comb = comb.begin();
                auto it_item = item.begin();
                while (it_comb != comb.end() && it_item != item.end() && *it_comb == *it_item) {
                    ++it_comb, ++it_item;
                }
                return (it_comb == comb.end() && it_item == item.end());
            });
            if (!repeated) { all_compatible_filtered.push_back(comb); }
        }

        /*
        std::cout << "Compatible combinations (filtered): " << all_compatible_filtered.size() << std::endl;
        auto i = 0;
        for (auto& comb : all_compatible_filtered) {
            std::cout << i++ << ": ";
            for (auto& item : comb) {
                std::cout << item << ", ";
            }
            std::cout << std::endl;
        }
        getchar();
        */

        // Build return vector
        for (auto& combination : all_compatible_filtered) {
            conceptual_graph graph;
            conceptual_graph_corresponde correspondence_to_lhs;
            conceptual_graph_corresponde correspondence_to_rhs;
            float similarity = 0.f;
            for (auto& index : combination) {
                append_correspondence_tuple(subgraphs[index], graph, correspondence_to_lhs, correspondence_to_rhs);
                similarity += get<3>(subgraphs[index]);
            }            
            ret.insert(ret.end(), make_tuple(graph, correspondence_to_lhs, correspondence_to_rhs, similarity));
        }


        /* TODO: Aquí se puede implementar un algoritmo recursivo basado en la compatibilidad. A medida que voy
            seleccionando/añadiendo grafos las opciones compatibles van disminuyendo (sólo es compatible la
            intersección de los que son compatibles con cada uno de los grafos que he añadido) ==> nace un 
            concepto de "Compatibility cascade/recursive algorithm" o quizá se puede convertir la matriz en
            un árbol donde cada camino sea un una combinación posible.

            Todo este preprocesado, bien implementado, seguro que reduce los tiempos de cálculo (y la explosión
            combinatoria) de forma drástica.
        */
        
    }
}
