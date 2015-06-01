
#include "distance_relation.h"
#include <numeric>

using namespace wn;
using namespace wn::distance;
using namespace std;

const float base_relation::max_distance = 1.f; // TODO: Max for any type of distance metric

base_relation::base_relation() {
}

float base_relation::min() const {
    return 0.f;
}

float base_relation::max() const {
    return 1.f;
}

float base_relation::operator()(const relation& r1, const relation& r2) const {
    if (r1.type == r2.type) {
        return this->min();
    }
    else {
        return this->max();
    }
}

float base_relation::min_distance(const std::vector<relation>& r1, const std::vector<relation>& r2, std::vector<_t_distance>& dist_combs) const {
    assert(r1.size() == r2.size());
    return this->min_distance(r1, r2, dist_combs, 0.f);
}

float base_relation::min_distance(const std::vector<relation>& r1, const std::vector<relation>& r2, std::vector<_t_distance>& dist_combs, float penalize_each) const {
    // Look for the combination that minimizes distance between the two sets.
    assert(r1.size() <= r2.size());
    auto penalization = (r2.size() - r1.size())*penalize_each;
    assert(r1.size()*base_relation::max_distance <= (std::numeric_limits<float>::max() - penalization));

    // v1.size() is number of rows
    // v2.size() is number of columns

    vector<float> distances; distances.reserve(r1.size()*r2.size()); // distance 'matrix'
    for (auto it1 = r1.begin(); it1 != r1.end(); ++it1) {
        for (auto it2 = r2.begin(); it2 != r2.end(); ++it2) {
            distances.push_back(this->operator()(*it1, *it2));
        }
    }

    vector<size_t> indexes(r2.size());
    std::iota(indexes.begin(), indexes.end(), 0);

    vector<pair<vector<size_t>, float>> permutations;
    float min_value = base_relation::max_distance;
    do {
        float sum = 0.f;
        for (auto i = 0; i < r1.size(); ++i) {
            sum += distances[r2.size() * i + indexes[i]];
        }
        if (sum <= min_value){
            auto it_perm = permutations.insert(permutations.end(), make_pair(vector<size_t>(), sum));
            std::copy(indexes.begin(), indexes.end(), std::back_inserter(it_perm->first));
            min_value = sum;
        }
    } while (next_permutation(indexes.begin(), indexes.end()));

    // Build return value
    vector<vector<size_t>> unique_indexes;
    auto repeated_indexes = [&unique_indexes](vector<size_t>::iterator init, vector<size_t>::iterator fin) ->bool {
        for(auto& seq_indexes: unique_indexes) {
            if (equal(seq_indexes.begin(), seq_indexes.end(), init)) {
                return true;
            };
        }
        return false;
    };
    for (auto it_perm = permutations.begin(); it_perm != permutations.end(); ++it_perm) {
        if (it_perm->second == min_value && !repeated_indexes(it_perm->first.begin(), it_perm->first.begin() + r1.size())) {
            unique_indexes.push_back(vector<size_t>(it_perm->first.begin(), it_perm->first.begin() + r1.size()));
            auto s1 = r1.begin();
            auto new_comb = dist_combs.insert(dist_combs.end(), vector<tuple<relation, relation, float>>());
            for (auto index = 0; index < r1.size(); ++index, ++s1) {
                new_comb->push_back(make_tuple(*s1, r2[it_perm->first[index]], distances[r2.size() * index + it_perm->first[index]]));
            }
        }
    }

    if (r2.size() > r1.size()) {
        // There can be repeated solutions: (v2.size - v1.size) elements at the end
    }

    return min_value + penalization;
}

float base_relation::min_distance(const vector<relation>& r1, const vector<relation>& r2, float edge_penalization) const {
    if (r1.size() > r2.size()) {
        return this->min_distance(r2, r1, edge_penalization);
    }
    else {
        assert(r2.size() >= r1.size());
        float distance = r1.size()*this->max();
        auto relation_less = [](const relation& lhs, const relation& rhs){ return lhs.type < rhs.type; };
        vector<relation> aux_rel2(r2.begin(), r2.end());
        sort(aux_rel2.begin(), aux_rel2.end(), relation_less);
        do {
            float aux_distance = std::inner_product(r1.begin(), r1.end(), aux_rel2.begin(), 0.f,
                [](const float& lhs, const float& rhs){ return lhs + rhs; },
                [this](const relation& lhs, const relation& rhs){ return this->operator()(lhs, rhs); });
            distance = std::min(distance, aux_distance);
        } while (next_permutation(aux_rel2.begin(), aux_rel2.end(), relation_less));
        return distance + (r2.size() - r1.size())*edge_penalization;
    }
}

float base_relation::min(const std::vector<relation>& r1, const std::vector<relation>& r2, float penalization) const {
    return abs(int(r2.size()) - int(r1.size()))*penalization;
}

float base_relation::max(const std::vector<relation>& r1, const std::vector<relation>& r2, float penalization) const {
    auto min_elements = std::min(r2.size(), r1.size());
    return min_elements*this->max() + abs(int(r2.size()) - int(r1.size()))*penalization;
}


