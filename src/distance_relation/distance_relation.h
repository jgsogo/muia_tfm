
#pragma once

#include "../conceptual_graph/relation.h"
#include "distance_relation/wn_distance_relation_export.h"

namespace wn {
    namespace distance {

        class WN_DISTANCE_RELATION_EXPORT base_relation {
            public:
                typedef std::vector<std::tuple<relation, relation, float>> _t_distance;
                static const float max_distance; //! max_distance for relations

            public:
                base_relation();

                //! Lower bound for the distance between two relations (0.f iff relations are equal)
                float lower_bound() const;
                //! Upper bound for the distance between two relations (defaults to '''distance::base_relation::max_distance''')
                virtual float upper_bound() const;

                //! Lower bound value for the distance between two relation sets.
                float lower_bound(const std::vector<relation>& r1, const std::vector<relation>& r2, float penalization) const;
                //! Upper bound value for the distance between two relation sets.
                float upper_bound(const std::vector<relation>& r1, const std::vector<relation>& r2, float penalization) const;

                //! Distance between two relations
                virtual float operator()(const relation& r1, const relation& r2) const;
                //! Min distance between two bags of relations
                float min_distance(const std::vector<relation>& r1, const std::vector<relation>& r2, std::vector<_t_distance>& dist_combs) const;
                //! Min distance between two bags of relations (can be of different size)
                float min_distance(const std::vector<relation>& r1, const std::vector<relation>& r2, std::vector<_t_distance>& dist_combs, float penalization) const;
                //! Min distance between two bags of relations (can be of different size)
                float min_distance(const std::vector<relation>& r1, const std::vector<relation>& r2, float penalization) const;

            protected:
        };

    }
}


