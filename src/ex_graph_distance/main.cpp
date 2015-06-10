
#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>
#include "../wordnet/wordnet.h"
#include "../wordnet/hyperonym_graph.h"
#include "../conceptual_graph/conceptual_graph.h"
#include "../distance_synset/shortest_path.h"
#include "../distance_synset/distance_sussna.h"
#include "../distance_synset/distance_wu_palmer.h"
#include "../distance_synset/distance_leacock_chodorow.h"
#include "../distance_synset/distance_resnik.h"
#include "../distance_synset/distance_jiang_conrath.h"
#include "../distance_synset/distance_lin.h"
#include "../distance_graph/mine.h"
#include "../distance_graph/mcs.h"
#include "../corpus/semcor.h"

using namespace wn;
using namespace std;
namespace fs = ::boost::filesystem;

struct graph_dist {
    graph_dist(conceptual_graph& g1, conceptual_graph& g2) : graph1(g1), graph2(g2) {};

    template <class GraphDistance>
    void distance_graphs(distance::base_synset& words_dist, distance::base_relation& rels_dist) {
        GraphDistance graph_distance(words_dist, rels_dist);
        auto penalize_node = words_dist.upper_bound();
        auto penalize_edge = rels_dist.upper_bound();
        auto min_d = graph_distance.lower_bound(graph1, graph2, penalize_node, penalize_edge);
        auto max_d = graph_distance.upper_bound(graph1, graph2, penalize_node, penalize_edge);
        cout << " - Similarity in [" << min_d << ", " << max_d << "]" << endl;

        auto data = graph_distance.max_similarity(graph1, graph2, penalize_node, penalize_edge);
        cout << " - Max similarity is " << data << endl;
        cout << " - Ratio " << data / max_d << endl;
    }

    conceptual_graph& graph1;
    conceptual_graph& graph2;
};

int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "usage: " << argv[0] << " <path/to/wordnet/dict/> <path/to/semcor/>" << endl;
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
    auto cat = wnet.get_synsets("cat", pos_t::N)[0];
    std::cout << " - cat >> " << cat << endl;

    auto drink = wnet.get_synsets("drink", pos_t::V)[0];
    std::cout << " - drink >> " << drink << endl;

    auto water = wnet.get_synsets("water", pos_t::N)[0];
    std::cout << " - water >> " << water << endl;
    auto wine = wnet.get_synsets("wine", pos_t::N)[0];
    std::cout << " - wine >> " << wine << endl;
    auto mountain = wnet.get_synsets("mountain", pos_t::N)[0];
    std::cout << " - mountain >> " << mountain << endl;
    auto top = wnet.get_synsets("top", pos_t::N)[0];
    std::cout << " - top >> " << top << endl;

    auto red = wnet.get_synsets("red", pos_t::A)[0];
    std::cout << " - red >> " << red << endl;



    conceptual_graph cgraph1;
    { // Graph#1: The red dog drinks water in the top of a mountain
    cout << endl;
    cout << "Graph#1: The red dog drinks water in the top of a mountain." << endl;
    auto id_drink = cgraph1.add_node(drink);
    auto id_dog = cgraph1.add_node(dog);
    auto id_red = cgraph1.add_node(red);
    auto id_water = cgraph1.add_node(water);
    auto id_top = cgraph1.add_node(top);
    auto id_mountain = cgraph1.add_node(mountain);

    cgraph1.add_relation(id_drink, id_dog, 1);
    cgraph1.add_relation(id_dog, id_red, 1);
    cgraph1.add_relation(id_drink, id_water, 1);
    cgraph1.add_relation(id_drink, id_top, 1);
    cgraph1.add_relation(id_top, id_mountain, 1);
    cgraph1.print(std::cout);
    }

    conceptual_graph cgraph2;
    { // Graph#2: The dog drinks water under the top of a mountain
    cout << endl;
    cout << "Graph#2: The dog drinks water under the top of a mountain." << endl;
    auto id_drink = cgraph2.add_node(drink);
    auto id_dog = cgraph2.add_node(dog);
    auto id_water = cgraph2.add_node(water);
    auto id_top = cgraph2.add_node(top);
    auto id_mountain = cgraph2.add_node(mountain);
    cgraph2.add_relation(id_drink, id_dog, 1);
    cgraph2.add_relation(id_drink, id_water, 1);
    cgraph2.add_relation(id_drink, id_top, 100);
    cgraph2.add_relation(id_top, id_mountain, 1);
    cgraph2.print(std::cout);
    }

    
    distance::shortest_path shortest_path(wnet);
    distance::sussna distance_sussna(graph);
    distance::wu_palmer distance_wu_palmer(graph);
    distance::leacock_chodorow distance_leacock_chodorow(graph);
    distance::resnik distance_resnik(graph, corpus);
    distance::jiang_conrath distance_jiang_conrath(graph, corpus);
    distance::lin distance_lin(graph, corpus);

    graph_dist dist_graphs(cgraph1, cgraph2);
    distance::base_relation distance_relation;

    cout << endl;
    cout << "# Distance 'shortest_path' between graphs" << endl;
    cout << "#-------------------------------" << endl;
    dist_graphs.distance_graphs<distance::mcs>(shortest_path, distance_relation);

    cout << endl;
    cout << "# Distance 'Sussna' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    dist_graphs.distance_graphs<distance::mcs>(distance_sussna, distance_relation);

    cout << endl;
    cout << "# Distance 'Wu Palmer' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    dist_graphs.distance_graphs<distance::mcs>(distance_wu_palmer, distance_relation);

    cout << endl;
    cout << "# Distance 'Leacock & Chodorow' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    dist_graphs.distance_graphs<distance::mcs>(distance_leacock_chodorow, distance_relation);

    cout << endl;
    cout << "# Distance 'Resnik' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    dist_graphs.distance_graphs<distance::mcs>(distance_resnik, distance_relation);

    cout << endl;
    cout << "# Distance 'Jiang && Conrath' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    dist_graphs.distance_graphs<distance::mcs>(distance_jiang_conrath, distance_relation);

    cout << endl;
    cout << "# Distance 'Lin' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    dist_graphs.distance_graphs<distance::mcs>(distance_lin, distance_relation);


}
