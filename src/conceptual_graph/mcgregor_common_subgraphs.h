
#pragma once

#include "conceptual_graph/wn_conceptual_graph_export.h"
#include "conceptual_graph.h"

namespace wn {

    typedef std::map<conceptual_graph::synset_id, conceptual_graph::synset_id> conceptual_graph_corresponde;
    WN_CONCEPTUAL_GRAPH_EXPORT void mcgregor_common_subgraphs(
        const conceptual_graph& lhs,
        const conceptual_graph& rhs,
        std::function<bool(const synset&, const synset&)>,
        std::function<bool(const relation&, const relation&)>,
        std::vector<std::tuple<conceptual_graph, conceptual_graph_corresponde, conceptual_graph_corresponde>>&);

}