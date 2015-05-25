
#include "information_based.h"

using namespace wn::distance;
using namespace std;


information_based::information_based(const wn::hyperonym_graph& graph, const wn::corpus& corpus) : graph(graph), corpus(corpus) {
}

information_based::~information_based() {
}

