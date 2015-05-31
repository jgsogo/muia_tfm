
#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>
#include "../wordnet/wordnet.h"
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
#include "../graph_distance/mcs.h"
#include "../corpus/semcor.h"

using namespace wn;
using namespace std;
namespace fs = ::boost::filesystem;

struct graph_dist {
    graph_dist(conceptual_graph& g1, conceptual_graph& g2) : graph1(g1), graph2(g2) {};

    template <class GraphDistance>
    void distance_graphs(distance::base_synset& words_dist) {
        GraphDistance graph_distance(words_dist);
        auto penalize_node = words_dist.max();
        auto penalize_edge = graph_distance.max_edge_distance();
        auto data = graph_distance.min_distance(graph1, graph2, penalize_node, penalize_edge);
        auto min_d = graph_distance.min(graph1, graph2, penalize_node, penalize_edge);
        auto max_d = graph_distance.max(graph1, graph2, penalize_node, penalize_edge);
        cout << " - Distance in [" << min_d << ", " << max_d << "]" << endl;
        cout << " - Min distance is " << data << endl;
        cout << " - Ratio " << (data - min_d) / (max_d - min_d) << endl;
    }

    conceptual_graph& graph1;
    conceptual_graph& graph2;
};

int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "usage: " << argv[0] << " <path/to/wordnet-3.0/> <path/to/semcor/>" << endl;
		exit(1);
	}
    cout << endl;
    cout << "# Loading WordNet" << endl;
    cout << "#-------------------------------" << endl;
	wordnet wnet(argv[1], true);
    hyperonym_graph graph(wnet);

    cout << endl;
    cout << "# Reading SemCor" << endl;
    cout << "#-------------------------------" << endl;
    semcor corpus(wnet);
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
    auto dog = wnet.get_synsets("dog", pos_t::N)[0];
    std::cout << " - dog >> " << dog << endl;
    auto drink = wnet.get_synsets("drink", pos_t::V)[0];
    std::cout << " - drink >> " << drink << endl;
    auto water = wnet.get_synsets("water", pos_t::N)[0];
    std::cout << " - water >> " << water << endl;
    auto wine = wnet.get_synsets("wine", pos_t::N)[0];
    std::cout << " - wine >> " << wine << endl;
    auto red = wnet.get_synsets("red", pos_t::N)[0];
    std::cout << " - red >> " << red << endl;


    // Build a sample cgraph
    conceptual_graph cgraph1;
    auto id_drink = cgraph1.add_node(drink);
    auto id_dog = cgraph1.add_node(dog);
    auto id_water = cgraph1.add_node(water);
    auto id_red = cgraph1.add_node(red);
    cgraph1.add_relation(id_drink, id_dog, 10);
    cgraph1.add_relation(id_drink, id_water, 12);
    cgraph1.add_relation(id_dog, id_red, 8);

    conceptual_graph cgraph2;
    id_drink = cgraph2.add_node(drink);
    id_dog = cgraph2.add_node(dog);
    id_red = cgraph2.add_node(red);
    auto id_wine = cgraph2.add_node(wine);
    cgraph2.add_relation(id_drink, id_dog, 10);
    cgraph2.add_relation(id_drink, id_wine, 12);
    cgraph2.add_relation(id_wine, id_red, 8);

    cout << endl;
    cout << "Graph#1: The dog drinks water." << endl;
    cgraph1.print(std::cout);
    cout << "Graph#2: The dog drinks wine." << endl;
    cgraph2.print(std::cout);


    /*
    auto distance_graphs = [&cgraph1, &cgraph2](distance::base& words) {
        distance::mine mine_distance(dist);
        auto penalize_node = dist.max();
        auto penalize_edge = mine_distance.max_edge_distance();
        auto data = mine_distance.min_distance(cgraph1, cgraph2, penalize_node, penalize_edge);
        auto min_d = mine_distance.min(cgraph1, cgraph2, penalize_node, penalize_edge);
        auto max_d = mine_distance.max(cgraph1, cgraph2, penalize_node, penalize_edge);
        cout << " - Distance in [" << min_d << ", " << max_d << "]" << endl;
        cout << " - Min distance is " << data << endl;
        cout << " - Ratio " << (data - min_d) / (max_d - min_d) << endl;
    };
    */
    distance::shortest_path shortest_path(wnet);
    distance::sussna distance_sussna(graph);
    distance::wu_palmer distance_wu_palmer(graph);
    distance::leacock_chodorow distance_leacock_chodorow(graph);
    distance::resnik distance_resnik(graph, corpus);
    distance::jiang_conrath distance_jiang_conrath(graph, corpus);
    distance::lin distance_lin(graph, corpus);

    graph_dist dist_graphs(cgraph1, cgraph2);

    cout << endl;
    cout << "# Distance 'shortest_path' between graphs" << endl;
    cout << "#-------------------------------" << endl;
    cout << "###### Using 'distance::mine' for graphs" << endl;
    dist_graphs.distance_graphs<distance::mine>(shortest_path);
    cout << "###### Using 'distance::mcs' for graphs" << endl;
    dist_graphs.distance_graphs<distance::mcs>(shortest_path);
    exit(1);

    cout << endl;
    cout << "# Distance 'Sussna' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    dist_graphs.distance_graphs<distance::mine>(distance_sussna);

    cout << endl;
    cout << "# Distance 'Wu Palmer' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    dist_graphs.distance_graphs<distance::mine>(distance_wu_palmer);

    cout << endl;
    cout << "# Distance 'Leacock & Chodorow' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    dist_graphs.distance_graphs<distance::mine>(distance_leacock_chodorow);

    cout << endl;
    cout << "# Distance 'Resnik' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    dist_graphs.distance_graphs<distance::mine>(distance_resnik);

    cout << endl;
    cout << "# Distance 'Jiang && Conrath' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    dist_graphs.distance_graphs<distance::mine>(distance_jiang_conrath);

    cout << endl;
    cout << "# Distance 'Lin' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    dist_graphs.distance_graphs<distance::mine>(distance_lin);


}
