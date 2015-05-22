
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

pair<vector<pair<wnb::synset, wnb::synset>>, float> distance::min_distance(vector<wnb::synset> v1, vector<wnb::synset> v2) const {
    // Look for the combination that minimizes distance between the two sets.
    assert(v1.size() == v2.size());

	vector<float> distances; distances.reserve(v1.size()*v1.size()); // distance 'matrix'
	size_t index = 0;
	for (auto it1 = v1.begin(); it1 != v1.end(); ++it1) {
		for (auto it2 = v2.begin(); it2 != v2.end(); ++it2) {
			distances[index] = this->operator()(*it1, *it2);
		}
	}

	vector<size_t> indexes;  indexes.reserve(v1.size()); // indexes
	size_t n(0);
	std::generate_n(std::back_inserter(indexes), v1.size(), [n]()mutable{return n++; });

	vector<size_t> permutation; permutation.reserve(v1.size());
	float min_value = numeric_limits<float>::max();
	do {
		float sum = 0.f;
		for (auto i = 0; i < v1.size(); ++i) {
			sum += distances[8 * i + indexes[0]];
		}
		if (sum < min_value){
			std::copy(indexes.begin(), indexes.end(), permutation.begin());
		}
	} while (next_permutation(indexes.begin(), indexes.end()));

	// Build return value
	pair<vector<pair<wnb::synset, wnb::synset>>, float> ret;
	for (auto& s1 : v1) {
		for (auto& index : permutation) {
			ret.first.push_back(make_pair(s1, v2[index]));
		}
	}
	ret.second = min_value;
	return ret;
}
