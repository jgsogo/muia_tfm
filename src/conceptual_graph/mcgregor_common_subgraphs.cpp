
#include "mcgregor_common_subgraphs.h"
//#include <boost/graph/mcgregor_common_subgraphs.hpp>

/* Doc:
http://www.boost.org/doc/libs/1_40_0/libs/graph/doc/mcgregor_common_subgraphs.html
http://svn.kulitorum.com/RepSnapper/Libraries/Boost1.40/libs/graph/example/mcgregor_subgraphs_example.cpp
https://www.ebi.ac.uk/msd-srv/ssm/papers/spe_csia.pdf
*/
/*
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


namespace wn {

    void mcgregor_common_subgraphs_compute(const _t_graph& lhs, const _t_graph& rhs) {
        print_callback<_t_graph, _t_graph> my_callback(lhs, rhs);

        // Assume both graphs were defined with implicit vertex name,
        // edge name, and vertex index properties
        property_map<_t_graph, int synset::*>::const_type vname_map1 = get(&synset::id, lhs);
        property_map<_t_graph, int synset::*>::const_type vname_map2 = get(&synset::id, rhs);
        //property_map<_t_graph, vertex_name_t> vname_map1 = get(id, lhs);
        //property_map<_t_graph, vertex_name_t> vname_map2 = get(id, rhs);

        property_map<_t_graph, int relation::*>::const_type ename_map1 = get(&relation::type, lhs);
        property_map<_t_graph, int relation::*>::const_type ename_map2 = get(&relation::type, rhs);

        struct vertices_equivalents {
            vertices_equivalents(const _t_graph& g1, const _t_graph& g2) : m_graph1(g1), m_graph2(g2) {};
            bool operator()(graph_traits<_t_graph>::vertex_descriptor v1, graph_traits<_t_graph>::vertex_descriptor v2) {
                return true;
            };
            const _t_graph& m_graph1;
            const _t_graph& m_graph2;
        };
        vertices_equivalents eqv(lhs, rhs);

        // Print out all connected common subgraphs between graph1 and graph2.
        std::cout << "COMPUTE McGREGOR" << std::endl;
        mcgregor_common_subgraphs_unique(lhs, rhs, true, my_callback,
            edges_equivalent(make_property_map_equivalent(ename_map1, ename_map2)).
            vertices_equivalent(eqv));

    }

}
*/
