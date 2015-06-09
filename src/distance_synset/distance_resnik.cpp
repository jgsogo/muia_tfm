
#include "distance_resnik.h"
#include <numeric>

using namespace wn;
using namespace wn::distance;
using namespace std;

resnik::resnik(const hyperonym_graph& graph, const corpus& corpus_) : information_based(graph, corpus_) {
    auto corpus_index = corpus_.get_index();
    for (auto& s: corpus_index) {
        auto hypernyms = graph.hypernym_map(s.first);
        auto synset_count = std::accumulate(s.second.begin(), s.second.end(), 0, [](const size_t& lhs, const pair<corpus::doc_id, size_t>& doc_count){ return lhs+doc_count.second;});
        // Append counts
        concept_count.insert(make_pair(s.first, 0)).first->second += synset_count;
        for (auto& hypernym: hypernyms) {
            concept_count.insert(make_pair(hypernym.first, 0)).first->second += synset_count;
        }
        all_count += synset_count*(hypernyms.size()+1); // TODO: Verificar esta operación. Podría ser simplemente ``all_count += synset_count``.
    }
    max_count = std::max_element(concept_count.begin(), concept_count.end(), [](const pair<synset, size_t>& lhs, const pair<synset, size_t>& rhs){return lhs.second < rhs.second; })->second;
}

resnik::~resnik() {
}

float resnik::operator()(const synset& s1, const synset& s2) const {
    auto similarity = 0.f;
	auto lowest_common_hypernym = graph.lowest_hypernym(s1, s2);
	for(auto& lch: lowest_common_hypernym) {
        auto it_lch = concept_count.find(lch);
        if (it_lch != concept_count.end()) {
            auto aux_similarity = -log(it_lch->second/float(all_count));
            similarity = std::max(similarity, aux_similarity);
        }        
	}

    if (similarity == 0) {
        return this->upper_bound();
    }

    return 1.f/similarity;
}

float resnik::upper_bound() const {
    // TODO: Think about a better approach for this 'max_distance' computation.
    auto min_similarity = -log(max_count / float(all_count));
    return 1.f / min_similarity;
}
