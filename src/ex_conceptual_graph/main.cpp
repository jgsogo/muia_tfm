
#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>
#include "../wordnet/wordnet.h"
#include "../conceptual_graph/conceptual_graph.h"
#include "../conceptual_graph/unl_graph.h"

using namespace wn;
using namespace std;
namespace fs = ::boost::filesystem;


int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "usage: " << argv[0] << " <path/to/wordnet-3.0/> <path/to/semcor/>" << endl;
		exit(1);
	}
    cout << endl;
    cout << "# Loading WordNet" << endl;
    cout << "#-------------------------------" << endl;
	wordnet wnet(argv[1], true);

    /*
    cout << endl;
    cout << "# Reading SemCor" << endl;
    cout << "#-------------------------------" << endl;
	wn::semcor corpus(wn);
    string basepath = argv[2];

    // Parse files in SemCor corpus
    auto read_corpus_dir = [&corpus](const string& directory) {
        if(fs::is_directory(directory)) {
            cout << "## Reading files in " << directory << endl;
            fs::recursive_directory_iterator it(directory);
            fs::recursive_directory_iterator endit;
            while(it != endit) {
                if(fs::is_regular_file(*it) && it->path().extension() == ".xml") {
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
    

    // Print some stats
    cout << endl;
    cout << "# Stats about SemCor" << endl;
    cout << "#-------------------------------" << endl;
    auto documents = corpus.get_documents();
    auto index = corpus.get_index();
    cout << " - documents parsed: " << documents.size() << endl;
    cout << " - index size: " << index.size() << endl;
    */
    
    cout << endl;
    cout << "# Build conceptual graph" << endl;
    cout << "#-------------------------------" << endl;
    // Build a sample cgraph
    conceptual_graph cgraph;
    auto dog = wnet.get_synsets("dog", pos_t::N)[0];
    std::cout << " - dog >> " << dog << endl;
    auto drink = wnet.get_synsets("drink", pos_t::V)[0];
    std::cout << " - drink >> " << drink << endl;
    auto water = wnet.get_synsets("water", pos_t::N)[0];
    std::cout << " - water >> " << water << endl;
    
    auto id_drink = cgraph.add_node(drink);
    auto id_dog = cgraph.add_node(dog);
    auto id_water = cgraph.add_node(water);
    cgraph.add_relation(id_drink, id_dog, 10);
    cgraph.add_relation(id_drink, id_water, 12);

    cgraph.print(std::cout);
    
    
    cout << endl;
    cout << "# Build UNL graph" << endl;
    cout << "#-------------------------------" << endl;
    // Build a sample unl_graph
    unl_graph unlgraph;
    auto id_drink_unl = unlgraph.add_node(drink);
    unlgraph.add_attribute(id_drink_unl, "attr1");
    auto id_dog_unl = unlgraph.add_node(dog);
    auto id_water_unl = unlgraph.add_node(water);
    unlgraph.add_relation(id_drink_unl, id_dog_unl, 10);
    unlgraph.add_relation(id_drink_unl, id_water_unl, 12);

    unlgraph.print(std::cout);
    
}
