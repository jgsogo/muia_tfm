
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>
#include <thread>

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

#include "sample_file.h"
#include "utils.h"

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
    cout << "# Computing distances" << endl;
    cout << "#-------------------------------" << endl;
    distance::shortest_path shortest_path(wnet);
    distance::resnik distance_resnik(graph, corpus);
    distance::jiang_conrath distance_jiang_conrath(graph, corpus);
    distance::lin distance_lin(graph, corpus);
    distance::sussna distance_sussna_(graph);
    distance::wu_palmer distance_wu_palmer_(graph);
    distance::leacock_chodorow distance_leacock_chodorow_(graph);

    cache_distance distance_sussna(distance_sussna_);
    cache_distance distance_wu_palmer(distance_wu_palmer_);
    cache_distance distance_leacock_chodorow(distance_leacock_chodorow_);


    distance::base_relation_unl distance_relation;

    // Preparing output
    auto tol_synset_values = { 0.f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f };
    auto tol_relation_values = tol_synset_values;
    string sample_file_id = sample_file.substr(sample_file.find_last_of("\\/")+1);
    string output = sample_file.substr(0, sample_file.find_last_of(".")) + "-" + get_current_datetime() + ".csv";
    cout << "Output file '" << output << "'" << endl;
    ofstream fout;
    fout.open(output, ofstream::out | ofstream::app);
    if (fout.fail()) {
        cerr << "open failed: " << strerror(errno) << '\n';
        return -1;
    }
    fout << "# file\ttranslator\tdistance-meassure\tsynset-tolerance\trelation-tolerance\tsimilarity-value\tcomputation-time" << endl;

    // DO WORK!
    graph_dist dist_google(original, google, "google");
    graph_dist dist_yandex(original, yandex,   "yandex");
    for (auto& tol_synset_value: tol_synset_values) {
        for (auto& tol_relation_value: tol_relation_values) {
            cout << " - tol_synset_value = " << tol_synset_value << endl;
            cout << " - tol_relation_value = " << tol_relation_value << endl;

            vector<thread> ths;

            auto work_google = [&](distance::base_synset& words_dist, const string& dtype) {
                stringstream ss; ss << sample_file.substr(0, sample_file.find_last_of(".")) << "-google-" << dtype  << "-synset_" << tol_synset_value << "-relation_" << tol_relation_value << ".dot";
                ths.push_back(std::thread(&comparison_task_plot, std::ref(fout), sample_file_id, "google", dtype, tol_synset_value, tol_relation_value, std::ref(dist_google), std::ref(words_dist), std::ref(distance_relation), ss.str()));
            };

            auto work_yandex = [&](distance::base_synset& words_dist, const string& dtype) {
                stringstream ss; ss << sample_file.substr(0, sample_file.find_last_of(".")) << "-yandex-" << dtype  << "-synset_" << tol_synset_value << "-relation_" << tol_relation_value << ".dot";
                ths.push_back(std::thread(&comparison_task_plot, std::ref(fout), sample_file_id, "yandex", dtype, tol_synset_value, tol_relation_value, std::ref(dist_yandex), std::ref(words_dist), std::ref(distance_relation), ss.str()));
            };

            //void comparison_task(ofstream fout, const std::string& filename, const std::string& graph, const std::string& distance, const float& tol_synset_value, const float& tol_relation_value, graph_dist& graph_dist_, distance::base_synset& words_dist, distance::base_relation& rels_dist)
            work_google(shortest_path, "shortest_path");
            work_google(distance_sussna, "sussna");
            work_google(distance_wu_palmer, "wu-palmer");
            work_google(distance_leacock_chodorow, "leacock-chodorow");
            work_google(distance_resnik, "resnik");
            work_google(distance_jiang_conrath, "jiang-conrath");
            work_google(distance_lin, "lin");

            work_yandex(shortest_path, "shortest_path");
            work_yandex(distance_sussna, "sussna");
            work_yandex(distance_wu_palmer, "wu-palmer");
            work_yandex(distance_leacock_chodorow, "leacock-chodorow");
            work_yandex(distance_resnik, "resnik");
            work_yandex(distance_jiang_conrath, "jiang-conrath");
            work_yandex(distance_lin, "lin");

            cout << "waiting for threads to join..." << endl;
            for (auto& th : ths) {
                th.join();
            }
        }
    }
    fout.close();
}
