
#pragma once

#include "conceptual_graph/wn_conceptual_graph_export.h"
#include "conceptual_graph.h"

namespace wn {

    struct cmp_synset {
        virtual bool operator()(const synset& s1, const synset& s2) const { return s1 == s2; };
        virtual float similarity(const synset& s1, const synset& s2) const { return (s1 == s2) ? 1.f : 0.f; };
    };

    struct cmp_relation {
        virtual bool operator()(const relation& r1, const relation& r2) const { return r1 == r2; };
        virtual float similarity(const relation& r1, const relation& r2) const { return (r1 == r2) ? 1.f : 0.f; };
    };

    typedef std::map<conceptual_graph::synset_id, conceptual_graph::synset_id> conceptual_graph_corresponde;
    WN_CONCEPTUAL_GRAPH_EXPORT void mcgregor_common_subgraphs(
        const conceptual_graph& lhs,
        const conceptual_graph& rhs,
        const cmp_synset&,
        const cmp_relation&,
        std::vector<std::tuple<conceptual_graph, conceptual_graph_corresponde, conceptual_graph_corresponde, float>>&);

}