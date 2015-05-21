
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