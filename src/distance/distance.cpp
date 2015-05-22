
//#include "stdafx.h"
#include "distance.h"
#include <numeric>

using namespace wn;
using namespace std;

distance::distance(const wnb::wordnet& wordnet) : wordnet(wordnet) {
}

float distance::min() const {
	return 0;
}

float distance::max() const {
	return std::numeric_limits<float>::max();
}


float distance::min_distance(vector<wnb::synset> v1, vector<wnb::synset> v2, vector<distance::_t_distance>& dist_combs) const {
    // Look for the combination that minimizes distance between the two sets.
    assert(v1.size() == v2.size());

    vector<float> distances; distances.reserve(v1.size()*v1.size()); // distance 'matrix'
    for (auto it1 = v1.begin(); it1 != v1.end(); ++it1) {
        for (auto it2 = v2.begin(); it2 != v2.end(); ++it2) {
            distances.push_back(this->operator()(*it1, *it2));
        }
    }

    vector<size_t> indexes(v1.size());
    std::iota(indexes.begin(), indexes.end(), 0);

    vector<pair<vector<size_t>, float>> permutations;
    float min_value = numeric_limits<float>::max();
    do {
        float sum = 0.f;
        for (auto i = 0; i < v1.size(); ++i) {
            sum += distances[v1.size() * i + indexes[i]];
        }
        if (sum <= min_value){
            auto it_perm = permutations.insert(permutations.end(), make_pair(vector<size_t>(), sum));
            std::copy(indexes.begin(), indexes.end(), std::back_inserter(it_perm->first));
            min_value = sum;
        }
    } while (next_permutation(indexes.begin(), indexes.end()));

    // Build return value
    for (auto it_perm = permutations.begin(); it_perm != permutations.end(); ++it_perm) {
        if (it_perm->second == min_value) {
            auto s1 = v1.begin();
            auto new_comb = dist_combs.insert(dist_combs.end(), vector<tuple<wnb::synset, wnb::synset, float>>());
            for (auto index = 0; index < it_perm->first.size(); ++index, ++s1) {
                new_comb->push_back(make_tuple(*s1, v2[it_perm->first[index]], distances[v1.size() * index + it_perm->first[index]]));
            }
        }
    }
    return min_value;
}
