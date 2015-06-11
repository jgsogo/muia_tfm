
#pragma once

#include <vector>
#include "conceptual_graph.h"
#include "unl_relation.h"

namespace wn {

    class WN_CONCEPTUAL_GRAPH_EXPORT unl_graph : public conceptual_graph {
        public:
            unl_graph();
            ~unl_graph();

            void add_attribute(const synset_id& id, const std::string& attr);
            std::vector<std::string> get_attributes(const synset_id& id) const;

            virtual void print(std::ostream& os) const;
        protected:
            std::map<synset_id, std::vector<std::string>> attributes;
    };

}
