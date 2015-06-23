
#pragma once

#include "../wordnet/wordnet.h"
#include "../conceptual_graph/unl_graph.h"

bool parse_graph(const std::string& filename,
                 const std::string& section,
                 const wn::wordnet& wnet,
                 wn::unl_graph& graph);
