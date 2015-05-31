
#include "information_based.h"

using namespace wn;
using namespace wn::distance;
using namespace std;


information_based::information_based(const hyperonym_graph& graph_, const corpus& corpus_) : graph(graph_), corpus_(corpus_) {
}

information_based::~information_based() {
}

