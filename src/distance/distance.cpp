
//#include "stdafx.h"
#include "distance.h"

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

pair<vector<pair<wnb::synset, wnb::synset>>, float> distance::min_distance(vector<wnb::synset> v1, vector<wnb::synset> v2) const {
    // Look for the combination that minimizes distance between the two sets.
    assert(v1.size() == v2.size());
    auto accumulator = [](const float& lhs, const float& rhs) { return lhs + rhs;};
    auto distance = [this](const wnb::synset& s1, const wnb::synset& s2) { return this->operator()(s1, s2); };

    vector<wnb::synset> permutation(v1.size());
    float min_value = numeric_limits<float>::max();
    sort(v1.begin(), v1.end());
    do {
        float sum = inner_product(v1.begin(), v1.end(), v2.begin(), 0.f, accumulator, distance);
        if (sum < min_value) {
            min_value = sum;
            permutation = vector<wnb::synset>(v1.begin(), v1.end());
        }
    } while (next_permutation(v1.begin(), v1.end()));

    // Build return value
    pair<vector<pair<wnb::synset, wnb::synset>>, float> ret;
    for (auto& s1: permutation) {
        for (auto& s2: v2) {
        ret.first.push_back(make_pair(s1,s2));
        }
    }
    ret.second = min_value;
    return ret;
}
