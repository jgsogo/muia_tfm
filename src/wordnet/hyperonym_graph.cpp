

#include "hyperonym_graph.h"
#include <queue>
#include <boost/graph/filtered_graph.hpp>

using namespace wn;
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
			// TODO: Create enum to identify edge types
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
			// TODO: Create enum to identify edge types
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
*    Hyperonym graph DATA definition and implementation
*******************/
struct hyperonym_graph::data {
	_detail::hyperonymG hyperonym_graph;
	_detail::hyponymG hyponym_graph;
	const wordnet& wnet;
	bool instances;
	map<_detail::vertex, std::size_t> vert_depth;

    data(const wordnet& wnet, bool instances)
		: hyperonym_graph(wnet.wordnet_graph, _detail::hyperonym_edge<_detail::PointerSymbolMap>(boost::get(&ptr::pointer_symbol, wnet.wordnet_graph), instances)),
		  hyponym_graph(wnet.wordnet_graph, _detail::hyponym_edge<_detail::PointerSymbolMap>(boost::get(&ptr::pointer_symbol, wnet.wordnet_graph), instances)),
		  wnet(wnet),
		  instances(instances) {
	};

	static void compute_max_depth(hyperonym_graph::data& data) {
        using namespace _detail;

        // Function for recursive assignment of depth value
        function<void (vertex, size_t)> recurse_vertex;
        recurse_vertex = [&data, &recurse_vertex](vertex v, size_t depth) {
            boost::graph_traits<hyponymG>::out_edge_iterator e, e_end;
            std::tie(e, e_end) = boost::out_edges(v, data.hyponym_graph);
            for(; e!=e_end; ++e) {
                vertex w = target(*e, data.hyponym_graph);
                auto it_vertex = data.vert_depth.insert(std::make_pair(w, depth));
                if (it_vertex.first->second > depth) {
                    return;
                }
                it_vertex.first->second = depth;
                recurse_vertex(w, depth+1);
            }
        };

        auto orphans = hyperonym_graph::orphans(data.wnet, data.instances);
        for(auto& s: orphans) {
            // Use hyponym graph
            auto it = data.vert_depth.insert(std::make_pair(s.id, 0));
            assert(it.second);
            size_t depth = 0;
            // Init recursion
            recurse_vertex(s.id, depth+1);
        }

        /* TODO: Not every hyperonym relation has its corresponding hyponym relation
                I think that this is an error in WordNet, I whether if there is some
                kind of reason to have hyperonyms relations and not its reverse
                hyponym relation.
        */
        std::vector<vertex> bastards; // They have a parent (hyperonym) but that parent doesn't recognize them as children (hyponyms)
        boost::graph_traits<wordnet::graph>::vertex_iterator v, v_end;
        std::tie(v, v_end) = boost::vertices(data.wnet.wordnet_graph);
        for (; v != v_end; ++v) {
            if (data.vert_depth.find(*v) == data.vert_depth.end()) {
                bastards.push_back(*v);
            }
        }
        for(auto& s: bastards) {
            // Look for his parent
            function<size_t (vertex, size_t)> look_for_parent;
            look_for_parent = [&data, &look_for_parent](vertex v, size_t up) {
                boost::graph_traits<hyperonymG>::out_edge_iterator e, e_end;
                std::tie(e, e_end) = boost::out_edges(v, data.hyperonym_graph);
                size_t max_level = up;
                for (; e!=e_end; ++e) {
                    vertex w = target(*e, data.hyperonym_graph);
                    auto it_vert_depth = data.vert_depth.find(w);
                    if (it_vert_depth != data.vert_depth.end()) {
                        max_level = std::max(max_level, it_vert_depth->second + up + 1);
                    }
                    else {
                        max_level = std::max(max_level, look_for_parent(w, up+1));
                    }
                }
                return max_level;
            };

            auto depth = look_for_parent(s, 0);
            data.vert_depth[s] = depth;
            recurse_vertex(s, depth+1);
        }
    }
};

/******************
*    hyperonym_graph implementation
*******************/
hyperonym_graph::hyperonym_graph(const wordnet& wnet, bool instances) : d(new data(wnet, instances)) {
    hyperonym_graph::data::compute_max_depth(*d);
}

hyperonym_graph::~hyperonym_graph() {
	delete d;
}

map<synset, size_t> hyperonym_graph::hypernym_map(const wordnet& wnet, const synset& s, bool instances) {
    using namespace _detail;
    hyperonym_graph::data d(wnet, instances);
    map<vertex, std::size_t> vertices;
	boost::graph_traits<hyperonymG>::out_edge_iterator e, e_end;
	std::queue<vertex> q;
	q.push(s.id);
	vertices[s.id] = 0;
	while (!q.empty()) {
		vertex u = q.front(); q.pop();
		auto new_d = vertices[u] + 1;
		for (boost::tie(e, e_end) = boost::out_edges(u, d.hyperonym_graph); e != e_end; ++e) {
			vertex v = target(*e, d.hyperonym_graph);
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
		ret.insert(make_pair(d.hyperonym_graph[vertex_data.first], vertex_data.second));
	}
	return ret;
}

map<synset, std::size_t> hyperonym_graph::hypernym_map(const synset& s) const {
    return hyperonym_graph::hypernym_map(d->wnet, s, d->instances);
}

std::size_t hyperonym_graph::max_depth() const {
    using namespace _detail;
	auto it_max_depth = std::max_element(d->vert_depth.begin(), d->vert_depth.end(), [](const std::pair<vertex, std::size_t>& lhs, const std::pair<vertex, std::size_t>& rhs){
		return lhs.second < rhs.second;
	});
	return it_max_depth->second;
}

vector<synset> hyperonym_graph::orphans(const wordnet& wnet, bool instances) {
    using namespace _detail;
    hyperonym_graph::data d(wnet, instances);
    vector<synset> ret;
    boost::graph_traits<hyperonymG>::vertex_iterator v, v_end;
    std::tie(v, v_end) = boost::vertices(d.hyperonym_graph);
    for (; v != v_end; ++v) {
        boost::graph_traits<hyperonymG>::out_edge_iterator e, e_end;
        std::tie(e, e_end) = boost::out_edges(*v, d.hyperonym_graph);
        if (e == e_end) {
            ret.push_back(d.hyperonym_graph[*v]);
        }
    }
    return ret;
}

vector<synset> hyperonym_graph::orphans() const {
    return hyperonym_graph::orphans(d->wnet, d->instances);
}

size_t hyperonym_graph::get_max_depth(const synset& s) const {
    return d->vert_depth[s.id];
}

vector<vector<synset>> hyperonym_graph::hypernym_path(const synset& from, const synset& to) const {
    return hyperonym_graph::hypernym_path(d->wnet, from, to, d->instances);
}

vector<vector<synset>> hyperonym_graph::hypernym_path(const wordnet& wnet, const synset& from, const synset& to, bool instances) {
    using namespace _detail;
    hyperonym_graph::data d(wnet, instances);
    // We take for granted that there is a hyperonym-path from 'from' to 'to'
    // Recursion function
    function<vector<vector<vertex>> (const vertex& s, const vertex& target)> find_target;
    find_target = [&d, &find_target](const vertex& s, const vertex& target) {
        vector<vector<vertex>> ret;
        boost::graph_traits<hyperonymG>::out_edge_iterator e, e_end;
        std::tie(e, e_end) = boost::out_edges(s, d.hyperonym_graph);
        for (; e!=e_end; ++e) {
            vertex v = boost::target(*e, d.hyperonym_graph);
            if (v == target) {
                auto it = ret.insert(ret.end(), vector<vertex>());
                it->push_back(v);
            }
            else {
                auto paths = find_target(v, target);
                for (auto& path: paths) {
                    path.push_back(v);
                    ret.push_back(vector<vertex>(path.begin(), path.end()));
                }
            }
        }
        return ret;
    };
    // Init recursion
    auto paths = find_target(from.id, to.id);
    // Prepare output
    vector<vector<synset>> results;
    for (auto& path: paths) {
        auto it_result = results.insert(results.end(), vector<synset>());
        it_result->push_back(from);
        for (auto it_path = path.rbegin(); it_path!=path.rend(); ++it_path) {
            it_result->push_back(wnet.wordnet_graph[*it_path]);
        }
    }
    return results;
}

std::vector<synset> hyperonym_graph::lowest_hypernym(const synset& s1, const synset& s2) const {
    return hyperonym_graph::lowest_hypernym(d->wnet, s1, s2, d->instances);
}

vector<synset> hyperonym_graph::lowest_hypernym(const wordnet& wnet, const synset& s1, const synset& s2, bool instances) {
    using namespace _detail;
    auto map1 = hyperonym_graph::hypernym_map(wnet, s1, instances);
    auto map2 = hyperonym_graph::hypernym_map(wnet, s2, instances);

    vector<synset> ret;
    auto min_distance = numeric_limits<size_t>::max();
	for (auto it1 = map1.begin(); it1 != map1.end(); ++it1) {
		for (auto it2 = map2.begin(); it2 != map2.end(); ++it2) {
			if (it1->first == it2->first) {
                auto distance = it1->second + it2->second;
                if(distance < min_distance) {
                    min_distance = distance;
                    ret.clear();
                }
                if (distance == min_distance) {
                    ret.push_back(it1->first);
                }
			}
		}
	}
	return ret;
}

vector<synset> hyperonym_graph::hyperonyms(const synset& s) const {
    return hyperonym_graph::hyperonyms(d->wnet, s, d->instances);
}

vector<synset> hyperonym_graph::hyponyms(const synset& s) const {
    return hyperonym_graph::hyponyms(d->wnet, s, d->instances);
}

vector<synset> hyperonym_graph::hyperonyms(const wordnet& wnet, const synset& s, bool instances) {
    using namespace _detail;
    hyperonym_graph::data d(wnet, instances);
    boost::graph_traits<hyperonymG>::out_edge_iterator e, e_end;
    std::tie(e, e_end) = boost::out_edges(s.id, d.hyperonym_graph);
    vector<synset> ret;
    for (; e!=e_end;++e) {
        vertex v = target(*e, d.hyperonym_graph);
        ret.push_back(d.hyperonym_graph[v]);
    }
    return ret;
}

vector<synset> hyperonym_graph::hyponyms(const wordnet& wnet, const synset& s, bool instances) {
    using namespace _detail;
    hyperonym_graph::data d(wnet, instances);
    boost::graph_traits<hyponymG>::out_edge_iterator e, e_end;
    std::tie(e, e_end) = boost::out_edges(s.id, d.hyponym_graph);
    vector<synset> ret;
    for (; e!=e_end;++e) {
        vertex v = target(*e, d.hyponym_graph);
        ret.push_back(d.hyperonym_graph[v]);
    }
    return ret;
}

const wordnet& hyperonym_graph::get_wordnet() const {
    return d->wnet;
}
