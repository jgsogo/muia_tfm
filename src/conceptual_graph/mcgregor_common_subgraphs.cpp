

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
        typedef store_callback::_t_subgraphs _t_subgraphs;
        std::vector<std::unique_ptr<_t_subgraphs>> subgraphs;
        store_callback mcs_graphs(lhs.d->graph, rhs.d->graph, subgraphs, cmp_synset_, cmp_relation_);
        mcgregor_common_subgraphs_unique(lhs.d->graph, rhs.d->graph, true, mcs_graphs,
            edges_equivalent(funcs).vertices_equivalent(funcs));
        //std::cout << "Number of subgraphs (original): " << subgraphs.size() << std::endl;

        // Remove duplicated graphs
        auto nested = [](const conceptual_graph_corresponde& lhs, const conceptual_graph_corresponde& rhs) {
            return std::all_of(lhs.begin(), lhs.end(), [&rhs](const conceptual_graph_corresponde::value_type& item){
                auto it = rhs.find(item.first);
                return (it != rhs.end() && it->second == item.second);
            });
        };
        for (auto it1 = subgraphs.begin(); it1 != subgraphs.end(); ++it1) {
            for (auto it2 = subgraphs.begin(); it2 != subgraphs.end(); ++it2) {
                if (it1 == it2) { continue; }
                if (nested(get<2>(**it1), get<2>(**it2))) {
                    subgraphs.erase(it1);
                    it1 = subgraphs.begin();
                    break;
                }
            }
        }
        //std::cout << "Number of subgraphs (filtered): " << subgraphs.size() << std::endl;

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
        auto it = std::max_element(subgraphs.begin(), subgraphs.end(), [](std::unique_ptr<_t_subgraphs>& lhs, std::unique_ptr<_t_subgraphs>& rhs){
            return std::get<3>(*lhs) < std::get<3>(*rhs);
        });
        auto lower_bound = std::get<3>(**it);
        //std::cout << "Compatibility matrix: " << n_subgraphs << std::endl;
        //std::cout << "lower_bound: " << lower_bound << std::endl;
        std::vector<std::vector<float>> compatibility_matrix(n_subgraphs);
        for (auto i = 0; i < n_subgraphs; ++i) {
            std::vector<float> i_compatible(n_subgraphs, 0.f);
            for (auto j = 0; j < n_subgraphs; ++j) {
                if (i != j) {
                    auto comp = compatible_correspondences(get<2>(*subgraphs[i]), get<2>(*subgraphs[j]));
                    if (comp) {
                        i_compatible[j] = get<3>(*subgraphs[j]);
                    }
                }
            }
            compatibility_matrix[i] = i_compatible;
        }


        typedef std::vector<float> _t_row;
        auto sum_row = [](const _t_row& lhs, const float& init)->float {
            return std::accumulate(lhs.begin(), lhs.end(), init, [](const float& item1, const float& item2){ return item1 + item2; });
        };


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

        std::vector<std::vector<std::size_t>> compatible_sets;
        auto append_compatible_set = [&compatible_sets, &lower_bound, &subgraphs](std::vector<std::size_t>& set){
            auto sim_value = std::accumulate(set.begin(), set.end(), 0.f, [&subgraphs](const float& lhs, const std::size_t& rhs){
                return lhs + get<3>(*subgraphs[rhs]);
            });
            if (sim_value >= lower_bound) {
                if (sim_value > lower_bound) {
                    compatible_sets.clear();
                    lower_bound = sim_value;
                }
                std::sort(set.begin(), set.end());
                compatible_sets.push_back(set);
            }
            return sim_value;
        };

        for (auto i = (std::size_t)0; i < compatibility_matrix.size(); ++i) {
            const std::vector<float>& row = compatibility_matrix[i];
            auto i_sim_value = get<3>(*subgraphs[i]);
            if (sum_row(row, i_sim_value) < lower_bound) {
                continue;
            }
            // Build indexes
            std::vector<std::size_t> indexes;
            for (auto j = 0; j < row.size(); ++j) {
                if (i!=j && row[j] != 0.f) {
                    indexes.push_back(j);
                }
            }
            // Permutations
            do {
                std::vector<std::size_t> comp_set = { i };
                std::vector<float> compatible_set = compatibility_matrix[i];
                append_compatible_set(comp_set);
                for (auto j = 0; j < indexes.size(); ++j) {
                    if (!compatible_set[indexes[j]]) { break; }
                    compatible_set = intersect_rows(compatible_set, compatibility_matrix[indexes[j]]);
                    comp_set.push_back(indexes[j]);
                    i_sim_value = append_compatible_set(comp_set);
                    if (sum_row(compatible_set, i_sim_value) < lower_bound)  {
                        break;
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
        for (auto& row : compatible_sets) {
            conceptual_graph graph;
            conceptual_graph_corresponde correspondence_to_lhs;
            conceptual_graph_corresponde correspondence_to_rhs;
            float similarity = 0.f;

            for (auto i = 0; i < row.size(); ++i) {
                append_correspondence_tuple(*subgraphs[row[i]], graph, correspondence_to_lhs, correspondence_to_rhs);
                similarity += get<3>(*subgraphs[row[i]]);
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
