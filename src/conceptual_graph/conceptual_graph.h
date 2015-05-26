
#pragma once

#include "../distance/synset.h" // TODO: Look for better place as "../wordnet/wordnet.h"
#include "conceptual_graph/wn_conceptual_graph_export.h"
#include "relation.h"

namespace wn {
    class WN_CONCEPTUAL_GRAPH_EXPORT conceptual_graph {
        public:
            typedef std::size_t synset_id;

            conceptual_graph();
            ~conceptual_graph();

            synset_id add_node(const wnb::synset& s); //! returns 'id' for the given node (the same synset can appear more than once).
            wnb::synset get_node(const synset_id& s1) const;
            void add_relation(const synset_id& s1, const synset_id& s2, int rel_type);
            std::map<synset_id, wnb::synset> get_nodes() const;
            std::vector<relation> get_outgoing_edges(const synset_id& id) const;

            virtual void print(std::ostream& os) const;

        protected:
            struct data;
            data* d;
    };

}
