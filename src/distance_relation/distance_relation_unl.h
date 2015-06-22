
#pragma once

#include "../conceptual_graph/unl_relation.h"
#include "distance_relation.h"
#include "distance_relation/wn_distance_relation_export.h"

namespace wn {
    namespace distance {

        class WN_DISTANCE_RELATION_EXPORT base_relation_unl : public base_relation  {
            public:

            public:
                base_relation_unl();

                //! Distance between two relations
                virtual float operator()(const wn::unl::relation& r1, const wn::unl::relation& r2) const;

            protected:
        };

    }
}


