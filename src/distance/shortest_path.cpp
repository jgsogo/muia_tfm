
#include "shortest_path.h"
#include "wnb/nltk_similarity.hh"

using namespace wn;

shortest_path::shortest_path(const wnb::wordnet& wordnet) : distance(wordnet) {
}

float shortest_path::operator()(const synset& s1, const synset& s2) {
	wnb::nltk_similarity sim(wordnet);
	return sim.shortest_path_distance(s1, s2);
}