
#include "distance_resnik.h"
#include <numeric>

using namespace wn;
using namespace wn::distance;
using namespace std;

void resnik::parse_corpus(const hyperonym_graph& graph, const corpus& corpus_, 
                          std::map<synset, std::size_t>& concept_count, std::size_t& all_count, std::size_t& max_count) {
    auto corpus_index = corpus_.get_index();
    for (auto& s : corpus_index) {
        auto hypernyms = graph.hypernym_map(s.first);
        auto synset_count = std::accumulate(s.second.begin(), s.second.end(), 0, [](const size_t& lhs, const pair<corpus::doc_id, size_t>& doc_count){ return lhs + doc_count.second; });
        // Append counts
        // Hypernym_map returns also myself: concept_count.insert(make_pair(s.first, 0)).first->second += synset_count;
        for (auto& hypernym : hypernyms) {
            concept_count.insert(make_pair(hypernym.first, 0)).first->second += synset_count;
        }
        all_count += synset_count;
    }
    max_count = std::max_element(concept_count.begin(), concept_count.end(), [](const pair<synset, size_t>& lhs, const pair<synset, size_t>& rhs){return lhs.second < rhs.second; })->second;
    assert(all_count <= max_count);
}


resnik::resnik(const hyperonym_graph& graph, const corpus& corpus_) : information_based(graph, corpus_) {    
}

resnik::resnik( const hyperonym_graph& graph, const std::map<synset, std::size_t>& concept_count,
                std::size_t all_count, std::size_t max_count)
    : information_based(graph, concept_count, all_count, max_count) {
}

resnik::~resnik() {
}

float resnik::operator()(const synset& s1, const synset& s2) const {
    auto sim_value = this->similarity(s1, s2);
    return 1.f - sim_value;
}

float resnik::similarity(const synset& s1, const synset& s2) const {
    if (s1 == s2) {
        return 1.f;
    }
    auto sim_value = this->similarity_exact(s1, s2);
    auto max_sim_value = -log(1 / float(all_count));
    return (sim_value / max_sim_value);
}

float resnik::similarity_exact(const synset& s1, const synset& s2) const {
    auto similarity = 0.f;
    auto lowest_common_hypernym = graph.lowest_hypernym(s1, s2);
    for (auto& lch : lowest_common_hypernym) {
        auto it_lch = concept_count.find(lch);
        if (it_lch != concept_count.end()) {
            auto aux_similarity = -log(it_lch->second / float(all_count));
            similarity = std::max(similarity, aux_similarity);
        }
    }
    return similarity;
}

float resnik::upper_bound() const {
    return 1.f;
}
