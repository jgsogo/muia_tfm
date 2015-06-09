
//#include "stdafx.h"
#include "distance.h"
#include <numeric>

using namespace wn;
using namespace wn::distance;
using namespace std;

const float base_synset::max_distance = 100000.f; //! TODO: ¿De alguna forma quiero/puedo saber cuál es el mayor valor de distancia posible?

base_synset::base_synset() {
}

float base_synset::lower_bound() const {
	return 0;
}

float base_synset::upper_bound() const {
    return max_distance;
}

float base_synset::lower_bound(const std::vector<synset>& v1, const std::vector<synset>& v2, float penalization) const {
    auto min_elements = std::min(v2.size(), v1.size());
    return min_elements*this->lower_bound() + abs(int(v2.size()) - int(v1.size()))*penalization;
}

float base_synset::upper_bound(const std::vector<synset>& v1, const std::vector<synset>& v2, float penalization) const {
    auto min_elements = std::min(v2.size(), v1.size());
    return min_elements*this->upper_bound() + abs(int(v2.size()) - int(v1.size()))*penalization;
}

/*
bool base_synset::connected(const synset& s1, const synset& s2) const {
    return (this->operator()(s1, s2) < base_synset::max_distance);
}
*/

float base_synset::min_distance(const vector<synset>& v1, const vector<synset>& v2, vector<_t_distance>& dist_combs) const {
    assert(v1.size() == v2.size());
    return this->min_distance(v1, v2, dist_combs, 0.f);
    }

float base_synset::min_distance(const vector<synset>& v1, const vector<synset>& v2, vector<_t_distance>& dist_combs, float penalize_each) const {
    // Look for the combination that minimizes distance between the two sets.
    assert(v1.size() <= v2.size());
    auto penalization = (v2.size() - v1.size())*penalize_each;
    assert(v1.size()*base_synset::max_distance <= (std::numeric_limits<float>::max() - penalization));

    // v1.size() is number of rows
    // v2.size() is number of columns

    vector<float> distances; distances.reserve(v1.size()*v2.size()); // distance 'matrix'
    for (auto it1 = v1.begin(); it1 != v1.end(); ++it1) {
        for (auto it2 = v2.begin(); it2 != v2.end(); ++it2) {
            distances.push_back(this->operator()(*it1, *it2));
        }
    }

    vector<size_t> indexes(v2.size());
    std::iota(indexes.begin(), indexes.end(), 0);

    vector<pair<vector<size_t>, float>> permutations;
    float min_value = base_synset::max_distance;
    do {
        float sum = 0.f;
        for (auto i = 0; i < v1.size(); ++i) {
            sum += distances[v2.size() * i + indexes[i]];
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
        if (it_perm->second == min_value && !repeated_indexes(it_perm->first.begin(), it_perm->first.begin() + v1.size())) {
            unique_indexes.push_back(vector<size_t>(it_perm->first.begin(), it_perm->first.begin() + v1.size()));
            auto s1 = v1.begin();
            auto new_comb = dist_combs.insert(dist_combs.end(), vector<tuple<synset, synset, float>>());
            for (auto index = 0; index < v1.size(); ++index, ++s1) {
                new_comb->push_back(make_tuple(*s1, v2[it_perm->first[index]], distances[v2.size() * index + it_perm->first[index]]));
            }
        }
    }

    if (v2.size() > v1.size()) {
        // There can be repeated solutions: (v2.size - v1.size) elements at the end
    }

    return min_value + penalization;
}


float base_synset::similarity(const synset& s1, const synset& s2) const {
    auto distance = this->operator()(s1, s2);
    return wn::distance::similarity(*this, distance);
}

float similarity(const base_synset& metric, const float& distance_value) {
    auto upper_bound = metric.upper_bound();
    throw(std::exception("not implemented"));
    return 0.f;
}