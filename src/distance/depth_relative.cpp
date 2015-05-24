
#include "depth_relative.h"
#include "../wordnet/hyperonym_graph.h"

using namespace wn::distance;
using namespace std;


depth_relative::depth_relative(const hyperonym_graph& graph) : graph(graph) {
}

depth_relative::~depth_relative() {
}

