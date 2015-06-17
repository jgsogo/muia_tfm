
#include <iostream>
#include <fstream>
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
#include "../distance_graph/mine.h"
#include "../distance_graph/mcs.h"
#include "../distance_relation/distance_relation_unl.h"
#include "../corpus/semcor.h"

#include "../work_sample/sample_file.h"
#include "../work_sample/utils.h"


int main(int argc, char** argv) {
    if (argc != 4) {
        cout << "usage: " << argv[0] << " <path/to/wordnet/dict/> <path/to/semcor/> <path/to/sample/dir/>" << endl;
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
    cout << "Sample file '" << sample_file << "'" << endl;

    cout << "## Original graph" << endl;
    wn::unl_graph original;
    parse_graph(sample_file, "Original", wnet, original);
    //original.print(std::cout);
    cout << " - num_nodes = " << original.get_nodes().size() << endl;
    cout << " - num_edges = " << original.get_edges().size() << endl;

    cout << "## Google graph" << endl;
    wn::unl_graph google;
    parse_graph(sample_file, "Google", wnet, google);
    //google.print(std::cout);
    cout << " - num_nodes = " << google.get_nodes().size() << endl;
    cout << " - num_edges = " << google.get_edges().size() << endl;

    cout << "## Yandex graph" << endl;
    wn::unl_graph yandex;
    parse_graph(sample_file, "Yandex", wnet, yandex);
    //yandex.print(std::cout);
    cout << " - num_nodes = " << yandex.get_nodes().size() << endl;
    cout << " - num_edges = " << yandex.get_edges().size() << endl;


    cout << endl;
    cout << "# Classes to compute distances: " << endl;
    cout << "#-------------------------------" << endl;
    distance::shortest_path distance_synset(wnet);
    distance::base_relation_unl distance_relation;
    auto tol_synset = 0.f;
    auto tol_relation = 0.f;
    cout << " - tol_synset = " << tol_synset << endl;
    cout << " - tol_relation = " << tol_relation << endl;

    unl_graph result;
    distance::base_graph::conceptual_graph_corresponde s1_to_result;
    distance::base_graph::conceptual_graph_corresponde s2_to_result;

    distance::mcs distance_mcs(distance_synset, distance_relation);
    auto data = distance_mcs.max_similarity(original, google, tol_synset, tol_relation, result, s1_to_result, s2_to_result);
    cout << " - sim_value = " << data << endl;

    cout << endl << "# DEBUG" << endl;
    cout << "#---------------" << endl;
    result.print(cout);
    cout << endl << "// Correspondence 'result <-> google'" << endl;
    for (auto& item: s2_to_result) {
        cout << "\t" << item.first << " <-> " << item.second << endl;
    }
    cout << endl << "// Correspondence 'result <-> original'" << endl;
    for (auto& item: s1_to_result) {
        cout << "\t" << item.first << " <-> " << item.second << endl;
    }


    return 0;
}
