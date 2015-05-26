
#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>
#include "wnb/core/wordnet.hh"
#include "../conceptual_graph/conceptual_graph.h"
#include "../distance/shortest_path.h"
#include "../graph_distance/mine.h"

using namespace std;
using namespace wnb;
namespace fs = ::boost::filesystem;


int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "usage: " << argv[0] << " <path/to/wordnet-3.0/> <path/to/semcor/>" << endl;
		exit(1);
	}
    cout << endl;
    cout << "# Loading WordNet" << endl;
    cout << "#-------------------------------" << endl;
	wordnet wn(argv[1], true);

    
    cout << endl;
    cout << "# Build conceptual graph" << endl;
    cout << "#-------------------------------" << endl;
    auto dog = wn.get_synsets("dog", pos_t::N)[0];
    std::cout << " - dog >> " << dog << endl;
    auto drink = wn.get_synsets("drink", pos_t::V)[0];
    std::cout << " - drink >> " << drink << endl;
    auto water = wn.get_synsets("water", pos_t::N)[0];
    std::cout << " - water >> " << water << endl;
    auto wine = wn.get_synsets("wine", pos_t::N)[0];
    std::cout << " - wine >> " << wine << endl;


    // Build a sample cgraph
    wn::conceptual_graph cgraph1;
    auto id_drink = cgraph1.add_node(drink);
    auto id_dog = cgraph1.add_node(dog);
    auto id_water = cgraph1.add_node(water);
    cgraph1.add_relation(id_drink, id_dog, 10);
    cgraph1.add_relation(id_drink, id_water, 12);

    wn::conceptual_graph cgraph2;
    id_drink = cgraph2.add_node(drink);
    id_dog = cgraph2.add_node(dog);
    auto id_wine = cgraph2.add_node(wine);
    cgraph2.add_relation(id_drink, id_dog, 10);
    cgraph2.add_relation(id_drink, id_wine, 12);

    cout << endl;
    cout << "Graph#1: The dog drinks water." << endl;
    cgraph1.print(std::cout);
    cout << "Graph#2: The dog drinks wine." << endl;
    cgraph2.print(std::cout);

    cout << endl;
    cout << "# Compute distance" << endl;
    cout << "#-------------------------------" << endl;
    wn::distance::shortest_path shortest_path_distance(wn);
    wn::distance::mine mine_distance(shortest_path_distance);
    cout << " - shortest_path(cgraph1, cgraph2)=" << mine_distance.min_distance(cgraph1, cgraph2);
    
}
