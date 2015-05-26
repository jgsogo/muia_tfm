
#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>
#include "wnb/core/wordnet.hh"
#include "../wordnet/hyperonym_graph.h"
#include "../conceptual_graph/conceptual_graph.h"
#include "../distance/shortest_path.h"
#include "../distance/distance_sussna.h"
#include "../distance/distance_wu_palmer.h"
#include "../distance/distance_leacock_chodorow.h"
#include "../distance/distance_resnik.h"
#include "../distance/distance_jiang_conrath.h"
#include "../distance/distance_lin.h"
#include "../graph_distance/mine.h"
#include "../corpus/semcor.h"

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
    wn::hyperonym_graph graph(wn);

    cout << endl;
    cout << "# Reading SemCor" << endl;
    cout << "#-------------------------------" << endl;
    wn::semcor corpus(wn);
    string basepath = argv[2];
    // Parse files in SemCor corpus
    auto read_corpus_dir = [&corpus](const string& directory) {
        if (fs::is_directory(directory)) {
            cout << "## Reading files in " << directory << endl;
            fs::recursive_directory_iterator it(directory);
            fs::recursive_directory_iterator endit;
            while (it != endit) {
                if (fs::is_regular_file(*it) && it->path().extension() == ".xml") {
                    auto filename = fs::absolute(it->path());
                    auto doc_index = corpus.add_document(filename.string());
                    cout << "\t" << filename << " --> " << doc_index.size() << " synsets." << endl;
                }
                ++it;
            }
        }
    };
    read_corpus_dir(basepath + "brown1/");
    read_corpus_dir(basepath + "brown2/");
    read_corpus_dir(basepath + "brownv/");


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


    auto distance_graphs = [&cgraph1, &cgraph2](wn::distance::base& dist) {
        wn::distance::mine mine_distance(dist);
        auto penalize_node = dist.max();
        auto penalize_edge = mine_distance.max_edge_distance();
        auto data = mine_distance.min_distance(cgraph1, cgraph2, penalize_node, penalize_edge);
        cout << " - Distance in [" << mine_distance.min(cgraph1, cgraph2, penalize_node, penalize_edge) << ", " << mine_distance.max(cgraph1, cgraph2, penalize_node, penalize_edge) << "]" << endl;
        cout << " - Min distance is " << data << endl;
    };

    wn::distance::shortest_path shortest_path(wn);
    wn::distance::sussna distance_sussna(graph);
    wn::distance::wu_palmer distance_wu_palmer(graph);
    wn::distance::leacock_chodorow distance_leacock_chodorow(graph);
    wn::distance::resnik distance_resnik(graph, corpus);
    wn::distance::jiang_conrath distance_jiang_conrath(graph, corpus);
    wn::distance::lin distance_lin(graph, corpus);

    cout << endl;
    cout << "# Distance 'shortest_path' between graphs" << endl;
    cout << "#-------------------------------" << endl;
    distance_graphs(shortest_path);

    cout << endl;
    cout << "# Distance 'Sussna' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    distance_graphs(distance_sussna);

    cout << endl;
    cout << "# Distance 'Wu Palmer' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    distance_graphs(distance_wu_palmer);

    cout << endl;
    cout << "# Distance 'Leacock & Chodorow' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    distance_graphs(distance_leacock_chodorow);

    cout << endl;
    cout << "# Distance 'Resnik' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    distance_graphs(distance_resnik);

    cout << endl;
    cout << "# Distance 'Jiang && Conrath' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    distance_graphs(distance_jiang_conrath);

    cout << endl;
    cout << "# Distance 'Lin' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    distance_graphs(distance_lin);


}
