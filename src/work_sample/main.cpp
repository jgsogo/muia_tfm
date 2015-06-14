
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

#include "../wordnet/wordnet.h"
#include "../wordnet/hyperonym_graph.h"
#include "../distance_synset/shortest_path.h"
#include "../distance_synset/distance_sussna.h"
#include "../distance_synset/distance_wu_palmer.h"
#include "../distance_synset/distance_leacock_chodorow.h"
#include "../distance_synset/distance_resnik.h"
#include "../distance_synset/distance_jiang_conrath.h"
#include "../distance_synset/distance_lin.h"
#include "../corpus/semcor.h"

#include "sample_file.h"

using namespace wn;
using namespace std;
namespace fs = ::boost::filesystem;


int main(int argc, char** argv) {
    if (argc != 4) {
        cout << "usage: " << argv[0] << " <path/to/wordnet/dict/> <path/to/semcor/> <path/to/sample/file.txt>" << endl;
        exit(1);
    }

    cout << endl;
    cout << "# Loading WordNet" << endl;
    cout << "#-------------------------------" << endl;
	wordnet wnet(argv[1], true);
	hyperonym_graph graph(wnet);
    /*
    cout << endl;
    cout << "# Reading SemCor" << endl;
    cout << "#-------------------------------" << endl;
	semcor corpus(wnet);
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
    */
    cout << endl;
    cout << "# Reading sample file" << endl;
    cout << "#-------------------------------" << endl;
    string sample_file = argv[3];

    wn::unl_graph original;
    parse_graph(sample_file, "Original", wnet, original);

}
