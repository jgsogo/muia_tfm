

#include "hyperonym_graph.h"
#include <queue>
#include <boost/graph/filtered_graph.hpp>

using namespace wn;
using namespace wnb;
using namespace std;

namespace _detail {
	template <typename PointerSymbolMap>
	struct hyperonym_edge {
		hyperonym_edge() {}

        hyperonym_edge(PointerSymbolMap pointer_symbol, bool instance_hyperonym)
			: m_pointer_symbol(pointer_symbol),
              instance_hyperonym(instance_hyperonym) {}

		template <typename Edge>
		bool operator()(const Edge& e) const {
			//! \todo TODO: Create enum to identify edge types
            auto pointer_symbol = get(m_pointer_symbol, e);
            return (1 == pointer_symbol || (instance_hyperonym && 2 == pointer_symbol));
		}
		PointerSymbolMap m_pointer_symbol;
        bool instance_hyperonym;
	};

	template <typename PointerSymbolMap>
	struct hyponym_edge {
		hyponym_edge() {}

        hyponym_edge(PointerSymbolMap pointer_symbol, bool instance_hyponym)
			: m_pointer_symbol(pointer_symbol),
              instance_hyponym(instance_hyponym) {}

		template <typename Edge>
		bool operator()(const Edge& e) const {
			//! \todo TODO: Create enum to identify edge types
            auto pointer_symbol = get(m_pointer_symbol, e);
            return (3 == pointer_symbol || (instance_hyponym && 4 == pointer_symbol));
		}
		PointerSymbolMap m_pointer_symbol;
        bool instance_hyponym;
	};

	typedef boost::property_map<wordnet::graph, int ptr::*>::const_type PointerSymbolMap;

	typedef boost::filtered_graph<wordnet::graph, hyperonym_edge<PointerSymbolMap> > hyperonymG;
	typedef boost::filtered_graph<wordnet::graph, hyponym_edge<PointerSymbolMap> > hyponymG;

	typedef boost::graph_traits<wordnet::graph>::vertex_descriptor vertex;

}

/******************
*    Hyperonym graph data definition and implementation
*******************/
struct hyperonym_graph::data {
	_detail::hyperonym_edge<_detail::PointerSymbolMap> filter;
	_detail::hyperonymG fg;
	const wnb::wordnet& wnet;
	bool instance_hyperonym;
	map<_detail::vertex, std::size_t> vert_depth;

    data(const wnb::wordnet& wnet, bool instance_hyperonym)
		: filter(boost::get(&ptr::pointer_symbol, wnet.wordnet_graph), instance_hyperonym),
		  fg(wnet.wordnet_graph, filter),
		  wnet(wnet),
		  instance_hyperonym(instance_hyperonym) {
	};

	static void compute_max_depth(hyperonym_graph::data& data) {
        using namespace _detail;
        auto orphans = hyperonym_graph::orphans(data.wnet, data.instance_hyperonym);
        for(auto& s: orphans) {
            // Use hyponym graph
            hyponym_edge<_detail::PointerSymbolMap> hypo_filter(boost::get(&ptr::pointer_symbol, data.wnet.wordnet_graph), data.instance_hyperonym);
            hyponymG graph(data.wnet.wordnet_graph, hypo_filter);
            auto it = data.vert_depth.insert(std::make_pair(s.id, 0));
            assert(it.second);
            size_t depth = 0;

            // Function for recursiveness
            function<void (vertex, size_t)> recurse_vertex;
            recurse_vertex = [&data, &graph, &recurse_vertex](vertex v, size_t depth) {
                boost::graph_traits<hyponymG>::out_edge_iterator e, e_end;
                std::tie(e, e_end) = boost::out_edges(v, graph);
                for(; e!=e_end; ++e) {
                    vertex w = target(*e, graph);
                    auto it_vertex = data.vert_depth.insert(std::make_pair(w, depth));
                    if (it_vertex.first->second > depth) {
                        return;
                    }
                    recurse_vertex(w, depth+1);
                }
            };
            // Init recursion
            recurse_vertex(s.id, depth+1);
        }
    }
};

/******************
*    hyperonym_graph implementation
*******************/
hyperonym_graph::hyperonym_graph(const wnb::wordnet& wnet, bool instance_hyperonym) : d(new data(wnet, instance_hyperonym)) {
    hyperonym_graph::data::compute_max_depth(*d);
}

hyperonym_graph::~hyperonym_graph() {
	delete d;
}

map<synset, size_t> hyperonym_graph::hypernym_map(const wordnet& wnet, const synset& s, bool instance_hyperonym) {
    using namespace _detail;
    hyperonym_graph::data d(wnet, instance_hyperonym);
    map<vertex, std::size_t> vertices;
	boost::graph_traits<hyperonymG>::out_edge_iterator e, e_end;
	std::queue<vertex> q;
	q.push(s.id);
	vertices[s.id] = 0;
	while (!q.empty()) {
		vertex u = q.front(); q.pop();
		auto new_d = vertices[u] + 1;
		for (boost::tie(e, e_end) = boost::out_edges(u, d.fg); e != e_end; ++e) {
			vertex v = target(*e, d.fg);
			q.push(v);
			if (vertices.find(v) != vertices.end()) {
				if (new_d < vertices[v]) {
					vertices[v] = new_d;
				}
				else {
					q.pop();
				}
			}
			else {
				vertices[v] = new_d;
			}
		}
	}

	map<synset, std::size_t> ret;
	for (auto& vertex_data : vertices) {
		ret.insert(make_pair(d.fg[vertex_data.first], vertex_data.second));
	}
	return ret;
}

map<synset, std::size_t> hyperonym_graph::hypernym_map(const wnb::synset& s) const {
    return hyperonym_graph::hypernym_map(d->wnet, s, d->instance_hyperonym);
}

std::size_t hyperonym_graph::max_depth() const {
    using namespace _detail;
	auto it_max_depth = std::max_element(d->vert_depth.begin(), d->vert_depth.end(), [](const std::pair<vertex, std::size_t>& lhs, const std::pair<vertex, std::size_t>& rhs){
		return lhs.second < rhs.second;
	});
	return it_max_depth->second;
}

vector<wnb::synset> hyperonym_graph::orphans(const wnb::wordnet& wnet, bool instance_hyperonym) {
    using namespace _detail;
    hyperonym_graph::data d(wnet, instance_hyperonym);
    vector<wnb::synset> ret;
    boost::graph_traits<hyperonymG>::vertex_iterator v, v_end;
    std::tie(v, v_end) = boost::vertices(d.fg);
    for (; v != v_end; ++v) {
        boost::graph_traits<hyperonymG>::out_edge_iterator e, e_end;
        std::tie(e, e_end) = boost::out_edges(*v, d.fg);
        if (e == e_end) {
            ret.push_back(d.fg[*v]);
        }
    }
    return ret;
}

vector<wnb::synset> hyperonym_graph::orphans() const {
    return hyperonym_graph::orphans(d->wnet, d->instance_hyperonym);
}
