
#include "information_based.h"
#include <numeric>
#include "distance_resnik.h"

using namespace wn;
using namespace wn::distance;
using namespace std;


information_based::information_based(const hyperonym_graph& graph_, const corpus& corpus_) : graph(graph_) {
    // Word count based on Resnik (1995)
    resnik::parse_corpus(graph_, corpus_, concept_count, all_count, max_count);
}

information_based::information_based(const hyperonym_graph& graph_, const map<synset, size_t>& concept_count,
                                     size_t all_count, size_t max_count)
    : graph(graph_), concept_count(concept_count), all_count(all_count), max_count(max_count) {

}


information_based::~information_based() {
}

