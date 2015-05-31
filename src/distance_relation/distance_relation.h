
#pragma once

#include "../conceptual_graph/relation.h"
#include "distance_relation/wn_distance_relation_export.h"

namespace wn {
    namespace distance {

        class WN_DISTANCE_RELATION_EXPORT base_relation {
            public:
                static const float max_distance; //! max_distance for relations

            public:
                base_relation();
                virtual float min() const; //! min distance by default is 0
                virtual float max() const; //! max distance between two relation (by default is '''distance::max_distance''');
                virtual float operator()(const relation& r1, const relation& r2) const = 0;

                typedef std::vector<std::tuple<relation, relation, float>> _t_distance;
                virtual float min_distance(const std::vector<relation>& r1, const std::vector<relation>& r2, std::vector<_t_distance>& dist_combs) const;
                virtual float min_distance(const std::vector<relation>& r1, const std::vector<relation>& r2, std::vector<_t_distance>& dist_combs, float penalization) const;

                //! Max and min values for the distance between two relation sets.
                virtual float min(const std::vector<relation>& r1, const std::vector<relation>& r2, float penalization) const;
                virtual float max(const std::vector<relation>& r1, const std::vector<relation>& r2, float penalization) const;
            protected:
        };

    }
}


