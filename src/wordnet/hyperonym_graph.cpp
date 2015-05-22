

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

	typedef boost::property_map<wordnet::graph, int ptr::*>::const_type PointerSymbolMap;
	typedef boost::filtered_graph<wordnet::graph, hyperonym_edge<PointerSymbolMap> > G;
	typedef boost::graph_traits<G>::vertex_descriptor vertex;

}


struct hyperonym_graph::data {
    data(const wnb::wordnet& wnet, bool instance_hyperonym)
		: filter(boost::get(&ptr::pointer_symbol, wnet.wordnet_graph), instance_hyperonym),
		  fg(wnet.wordnet_graph, filter) {
	};
	_detail::hyperonym_edge<_detail::PointerSymbolMap> filter;
	_detail::G fg;
};


hyperonym_graph::hyperonym_graph(const wnb::wordnet& wnet, bool instance_hyperonym) : d(new data(wnet, instance_hyperonym)) {
}

hyperonym_graph::~hyperonym_graph() {
	delete d;
}

map<synset, std::size_t> hyperonym_graph::hypernym_map(wnb::synset s) const {
	using namespace _detail;

	map<vertex, std::size_t> vertices;
	boost::graph_traits<G>::out_edge_iterator e, e_end;
	std::queue<vertex> q;
	q.push(s.id);
	vertices[s.id] = 0;
	while (!q.empty()) {
		vertex u = q.front(); q.pop();
		auto new_d = vertices[u] + 1;
		for (boost::tie(e, e_end) = boost::out_edges(u, d->fg); e != e_end; ++e) {
			vertex v = target(*e, d->fg);
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
		ret.insert(make_pair(d->fg[vertex_data.first], vertex_data.second));
	}
	return ret;
}

std::size_t hyperonym_graph::max_depth() const {
	using namespace _detail;
	map<vertex, std::size_t> vert_depth;
	boost::graph_traits<G>::vertex_iterator v, v_end;
	std::tie(v, v_end) = boost::vertices(d->fg);
	for (; v != v_end; ++v) {
		auto it_vertex = vert_depth.insert(std::make_pair(*v, 0));
		if (it_vertex.second) {
			std::queue<vertex> q;
			q.push(*v);
			while (!q.empty()) {
				vertex u = q.front(); q.pop();
				auto hyperonym_depth = vert_depth.at(u) + 1;
				boost::graph_traits<G>::out_edge_iterator e, e_end;
				std::tie(e, e_end) = boost::out_edges(u, d->fg);
				for (; e != e_end; ++e) {
					vertex w = target(*e, d->fg);
					auto it_w = vert_depth.insert(std::make_pair(w, hyperonym_depth));
					if (it_w.second || it_w.first->second < hyperonym_depth) {
						it_w.first->second = hyperonym_depth;
						q.push(w);
					}					
				}				
			}
		}
	}
	auto it_max_depth = std::max_element(vert_depth.begin(), vert_depth.end(), [](const std::pair<vertex, std::size_t>& lhs, const std::pair<vertex, std::size_t>& rhs){
		return lhs.second < rhs.second;
	});
	return it_max_depth->second;
}

vector<wnb::synset> hyperonym_graph::orphans() const {
    using namespace _detail;

    vector<wnb::synset> ret;
    boost::graph_traits<G>::vertex_iterator v, v_end;
    std::tie(v, v_end) = boost::vertices(d->fg);
    for (; v != v_end; ++v) {
        boost::graph_traits<G>::out_edge_iterator e, e_end;
        std::tie(e, e_end) = boost::out_edges(*v, d->fg);
        if (e == e_end) {
            ret.push_back(d->fg[*v]);
        }
    }
    return ret;
}