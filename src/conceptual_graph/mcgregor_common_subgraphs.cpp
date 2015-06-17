

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
        typedef std::tuple<store_callback::MembershipFilteredGraph, store_callback::MembershipFilteredGraph, conceptual_graph_corresponde, float> _t_subgraphs;
        std::vector<_t_subgraphs> subgraphs;
        store_callback mcs_graphs(lhs.d->graph, rhs.d->graph, subgraphs, cmp_synset_, cmp_relation_);
        mcgregor_common_subgraphs_maximum_unique(lhs.d->graph, rhs.d->graph, true, mcs_graphs,
            edges_equivalent(funcs).vertices_equivalent(funcs));

        //std::cout << "Number of subgraphs (original): " << subgraphs.size() << std::endl;
        

        /* Combination of subgraphs must be done here, where I have original node_ids (I have filtered graphs).
        The objective is to return every possible combination of subgraphs which is compatible; but it
        must be compatible in graph1 and graph2
        */
        auto compatible_correspondences = [](const conceptual_graph_corresponde& lhs, const conceptual_graph_corresponde& rhs)->bool {
            // Two correspondences are compatible if they don't share any common element;
            //  - compare keys
            for (auto& it_lhs : lhs) {
                if (rhs.find(it_lhs.first) != rhs.end()) {
                    return false;
                }
            }
            //  - compare values
            for (auto& it_lhs : lhs) {
                auto it = std::find_if(rhs.begin(), rhs.end(), [&it_lhs](const std::pair<size_t, size_t>& item){
                    return (it_lhs.second == item.second);
                });
                if (it != rhs.end()) {
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
                    graph.add_relation(tmp_map[*v], tmp_map[tgt], lhs.d->graph[*e].type_);
                }
            }
        };

        // Build compatibility matrix
        auto n_subgraphs = subgraphs.size();
        //  - best single graph
        auto it = std::max_element(subgraphs.begin(), subgraphs.end(), [](_t_subgraphs& lhs, _t_subgraphs& rhs){
            return std::get<3>(lhs) < std::get<3>(rhs);
        });
        auto lower_bound = std::get<3>(*it);
        //std::cout << "Compatibility matrix: " << n_subgraphs << std::endl;
        //std::cout << "lower_bound: " << lower_bound << std::endl;
        std::vector<std::vector<float>> compatibility_matrix(n_subgraphs);
        for (auto i = 0; i < n_subgraphs; ++i) {
            std::vector<float> i_compatible(n_subgraphs, 0.f);
            for (auto j = 0; j < n_subgraphs; ++j) {
                if (i != j) {
                    auto comp = compatible_correspondences(get<2>(subgraphs[i]), get<2>(subgraphs[j]));
                    if (comp) {
                        i_compatible[j] = get<3>(subgraphs[j]);
                    }
                }
                else {
                    i_compatible[j] = get<3>(subgraphs[j]);
                }
            }
            compatibility_matrix[i] = i_compatible;
        }

        typedef std::vector<float> _t_row;
        auto sum_row = [](const _t_row& lhs)->float {
            return std::accumulate(lhs.begin(), lhs.end(), 0.f, [](const float& item1, const float& item2){ return item1 + item2; });
        };

        // Build unique matrix
        auto unique_matrix = compatibility_matrix;
        unique_matrix.erase(std::remove_if(unique_matrix.begin(), unique_matrix.end(), [&lower_bound, &sum_row](const _t_row& row){
            return (sum_row(row) < lower_bound);
            }), unique_matrix.end());
        std::sort(unique_matrix.begin(), unique_matrix.end());
        unique_matrix.erase(std::unique(unique_matrix.begin(), unique_matrix.end()), unique_matrix.end());
        //std::cout << "Unique matrix rows: " << unique_matrix.size() << std::endl;

        // Build all compatible set (all permutations for every row)        
        auto intersect_rows = [](const _t_row& lhs, const _t_row& rhs)->_t_row{
            assert(lhs.size() == rhs.size());
            _t_row row(lhs.size(), 0.f);
            for (auto i = 0; i < lhs.size(); ++i) {
                assert(lhs[i] == rhs[i]);
                row[i] = (lhs[i] != 0.f && rhs[i] != 0.f) ? lhs[i] : 0.f;
            }
            return row;
        };        
        std::vector<std::vector<float>> compatible_sets;
        auto i = 0;
        for (auto& row : unique_matrix) {
            if (sum_row(row) < lower_bound) {
                continue;
            }
            // Build indexes
            std::vector<int> indexes;
            for (auto i = 0; i < row.size(); ++i) {
                if (row[i] != 0.f) {
                    indexes.push_back(i);
                }
            }
            // Permutations
            do {
                std::vector<float> compatible_set = compatibility_matrix[indexes[0]];
                for (auto i = 0; i < indexes.size(); ++i) {
                    compatible_set = intersect_rows(compatible_set, compatibility_matrix[indexes[i]]);
                    auto sum_row_ = sum_row(compatible_set);
                    if (sum_row_ < lower_bound) {
                        break;
                    }
                    else {
                        if (sum_row_ > lower_bound) {
                            compatible_sets.clear();
                            lower_bound = sum_row_;
                        }
                        compatible_sets.push_back(compatible_set);
                    }
                }
            } while (std::next_permutation(indexes.begin(), indexes.end()));
        }
        //std::cout << "Compatible sets: " << compatible_sets.size() << std::endl;

        // Build unique compatible sets
        std::sort(compatible_sets.begin(), compatible_sets.end());
        compatible_sets.erase(std::unique(compatible_sets.begin(), compatible_sets.end()), compatible_sets.end());
        //std::cout << "Unique compatible sets: " << compatible_sets.size() << std::endl;


        // Build return vector
        for (auto& row : unique_matrix) {
            conceptual_graph graph;
            conceptual_graph_corresponde correspondence_to_lhs;
            conceptual_graph_corresponde correspondence_to_rhs;
            float similarity = 0.f;

            for (auto i = 0; i < row.size(); ++i) {
                append_correspondence_tuple(subgraphs[i], graph, correspondence_to_lhs, correspondence_to_rhs);
                similarity += get<3>(subgraphs[i]);
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
