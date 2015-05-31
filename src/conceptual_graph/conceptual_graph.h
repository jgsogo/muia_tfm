
#pragma once

#include "../wordnet/synset.h"
#include "conceptual_graph/wn_conceptual_graph_export.h"
#include "relation.h"

namespace wn {
    class WN_CONCEPTUAL_GRAPH_EXPORT conceptual_graph {
        public:
            typedef std::size_t synset_id;

            conceptual_graph();
            ~conceptual_graph();

            synset_id add_node(const synset& s); //! returns 'id' for the given node (the same synset can appear more than once).
            synset get_node(const synset_id& s1) const;
            std::map<synset_id, synset> get_nodes() const;

            void add_relation(const synset_id& s1, const synset_id& s2, int rel_type);
            std::vector<relation> get_edges() const;
            std::vector<relation> get_outgoing_edges(const synset_id& id) const;

            virtual void print(std::ostream& os) const;

            friend WN_CONCEPTUAL_GRAPH_EXPORT void mcgregor_common_subgraphs(
                const conceptual_graph& lhs,
                const conceptual_graph& rhs,
                std::function<bool (const synset&, const synset&)>,
                std::function<bool (const relation&, const relation&)>
                );
        protected:
            struct data;
            data* d;
    };

    WN_CONCEPTUAL_GRAPH_EXPORT void mcgregor_common_subgraphs(
        const conceptual_graph& lhs,
        const conceptual_graph& rhs,
        std::function<bool (const synset&, const synset&)>,
        std::function<bool (const relation&, const relation&)>
        );
}
