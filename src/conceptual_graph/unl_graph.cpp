
#include "unl_graph.h"
#include "conceptual_graph_data.h"
#include "unl_relation.h"

using namespace wn;

class unl_graph_printer : public boost::default_writer {
    public:
        unl_graph_printer(const _t_graph& g, const unl_graph& unl_data) : graph(g), unl_data(unl_data) {}
        void operator()(std::ostream& os, const boost::graph_traits<_t_graph>::vertex_descriptor& v) const {
            os << "[label=\"" << graph[v];
            auto attributes = unl_data.get_attributes(v);
            for (auto& attr : attributes) {
                os << "@" << attr << ", ";
            }
            os << "\"]";
        }
        void operator()(std::ostream& os, const boost::graph_traits<_t_graph>::edge_descriptor& e) const {
            const relation& rel = graph[e];
            os << "[label=\"" << static_cast<unl::relation::type>(rel.type_) << "\"]";
        }
    private:
        const _t_graph& graph;
        const unl_graph& unl_data;
};


unl_graph::unl_graph() : conceptual_graph() {}

unl_graph::~unl_graph() {}

void unl_graph::add_attribute(const synset_id& id, const std::string& attr) {
    attributes[id].push_back(attr);
}

std::vector<std::string> unl_graph::get_attributes(const synset_id& id) const {
    std::vector<std::string> ret;
    auto it_attr = attributes.find(id);
    if (it_attr != attributes.end()) {
        std::copy(it_attr->second.begin(), it_attr->second.end(), std::back_inserter(ret));
    }
    return ret;
}

void unl_graph::print(std::ostream& os) const {
    unl_graph_printer writer(d->graph, *this);
    d->print(os, d->graph, writer);
}
