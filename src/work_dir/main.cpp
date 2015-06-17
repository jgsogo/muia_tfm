
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
    cout << "# Classes to compute distances: " << endl;
    cout << "#-------------------------------" << endl;
    cout << " - shortest path" << endl << " - sussna" << endl << " - wu-palmer" << endl;
    cout << " - leacock-chodorwo" << endl << " - resnik" << endl << " - jiang-conrath" << endl;
    cout << " - lin" << endl;
    distance::shortest_path shortest_path_(wnet);
    distance::resnik distance_resnik_(graph, corpus);
    distance::jiang_conrath distance_jiang_conrath_(graph, corpus);
    distance::lin distance_lin_(graph, corpus);
    distance::sussna distance_sussna_(graph);
    distance::wu_palmer distance_wu_palmer_(graph);
    distance::leacock_chodorow distance_leacock_chodorow_(graph);

    distance::base_relation_unl distance_relation;

    // Directory to work in
    string directory = argv[3];
    cout << endl;
    cout << "# Work on directory '" << directory << "': " << endl;
    cout << "#-------------------------------" << endl;
    fs::recursive_directory_iterator it(directory);
    fs::recursive_directory_iterator endit;
    // Output file
    string output = directory + get_current_datetime() + ".csv";
    cout << "Output file '" << output << "'" << endl;
    ofstream fout;
    fout.open(output, ofstream::out | ofstream::app);
    if (fout.fail()) {
        cerr << "open failed: " << strerror(errno) << '\n';
        return -1;
    }
    fout << "# file;\ttranslator;\tdistance-meassure;\tsynset-tolerance;\trelation-tolerance;\tsimilarity-value;\tcomputation-time" << endl;
    // Variables to control loops
    auto tol_synset_values = { 0.f, .5f, .1f, .15f, .2f, .25f, .3f, .35f, .4f, .45f, .5f, .55f,
                              .6f, .65f, .7f, .75f, .8f, .85f, .9f, .95f, .99f };
    auto tol_relation_values = tol_synset_values;
    while (it != endit) {
        if (fs::is_regular_file(*it) && it->path().extension() == ".txt") {
            auto filename = fs::absolute(it->path()).string();
            auto fileid_ = it->path().filename().string();
            auto fileid = fileid_.substr(0, fileid_.find("."));
            cout << endl << "## File: '" << filename << "':" << endl;
            try {
                wn::unl_graph original;
                auto ori_graph = parse_graph(filename, "Original", wnet, original);
                ofstream fori; fori.open(directory + fileid + "_original.dot"); original.print(fori, true); fori.close();
                wn::unl_graph google;
                auto google_graph = parse_graph(filename, "Google", wnet, google);
                ofstream fgoo; fgoo.open(directory + fileid + "_google.dot"); google.print(fgoo, true); fgoo.close();
                wn::unl_graph yandex;
                auto yandex_graph = parse_graph(filename, "Yandex", wnet, yandex);
                ofstream fyan; fyan.open(directory + fileid + "_yandex.dot"); yandex.print(fyan, true); fyan.close();

                // Some distance meassures required high overhead, but we can cache them
                cache_distance shortest_path(shortest_path_);
                cache_distance distance_resnik(distance_resnik_);
                cache_distance distance_jiang_conrath(distance_jiang_conrath_);
                cache_distance distance_lin(distance_lin_);
                cache_distance distance_sussna(distance_sussna_);
                cache_distance distance_wu_palmer(distance_wu_palmer_);
                cache_distance distance_leacock_chodorow(distance_leacock_chodorow_);

                if (ori_graph && google_graph) {
                    graph_dist dist_original(original, google, "google");
                    for (auto tol_synset_value : tol_synset_values) {
                        for (auto tol_relation_value : tol_relation_values) {
                            cout << " - tol_synset_value = " << tol_synset_value << endl;
                            cout << " - tol_relation_value = " << tol_relation_value << endl;

                            vector<thread> ths;
                            //void comparison_task(ofstream fout, const std::string& filename, const std::string& graph, const std::string& distance, const float& tol_synset_value, const float& tol_relation_value, graph_dist& graph_dist_, distance::base_synset& words_dist, distance::base_relation& rels_dist) {
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "shortest_path", tol_synset_value, tol_relation_value, std::ref(dist_original), std::ref(shortest_path), std::ref(distance_relation)));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "sussna", tol_synset_value, tol_relation_value, std::ref(dist_original), std::ref(distance_sussna), std::ref(distance_relation)));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "wu-palmer", tol_synset_value, tol_relation_value, std::ref(dist_original), std::ref(distance_wu_palmer), std::ref(distance_relation)));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "leacock-chodorow", tol_synset_value, tol_relation_value, std::ref(dist_original), std::ref(distance_leacock_chodorow), std::ref(distance_relation)));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "resnik", tol_synset_value, tol_relation_value, std::ref(dist_original), std::ref(distance_resnik), std::ref(distance_relation)));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "jiang-conrath", tol_synset_value, tol_relation_value, std::ref(dist_original), std::ref(distance_jiang_conrath), std::ref(distance_relation)));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "lin", tol_synset_value, tol_relation_value, std::ref(dist_original), std::ref(distance_lin), std::ref(distance_relation)));

                            cout << "waiting for threads to join..." << endl;
                            for (auto& th : ths) {
                                th.join();
                            }

                        }
                    }
                }
                if (ori_graph && yandex_graph) {
                    graph_dist dist_yandex(original, yandex, "yandex");
                    for (auto tol_synset_value : tol_synset_values) {
                        for (auto tol_relation_value : tol_relation_values) {
                            cout << " - tol_synset_value = " << tol_synset_value << endl;
                            cout << " - tol_relation_value = " << tol_relation_value << endl;

                            vector<thread> ths;
                            //void comparison_task(ofstream fout, const std::string& filename, const std::string& graph, const std::string& distance, const float& tol_synset_value, const float& tol_relation_value, graph_dist& graph_dist_, distance::base_synset& words_dist, distance::base_relation& rels_dist) {
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "shortest_path", tol_synset_value, tol_relation_value, std::ref(dist_yandex), std::ref(shortest_path), std::ref(distance_relation)));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "sussna", tol_synset_value, tol_relation_value, std::ref(dist_yandex), std::ref(distance_sussna), std::ref(distance_relation)));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "wu-palmer", tol_synset_value, tol_relation_value, std::ref(dist_yandex), std::ref(distance_wu_palmer), std::ref(distance_relation)));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "leacock-chodorow", tol_synset_value, tol_relation_value, std::ref(dist_yandex), std::ref(distance_leacock_chodorow), std::ref(distance_relation)));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "resnik", tol_synset_value, tol_relation_value, std::ref(dist_yandex), std::ref(distance_resnik), std::ref(distance_relation)));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "jiang-conrath", tol_synset_value, tol_relation_value, std::ref(dist_yandex), std::ref(distance_jiang_conrath), std::ref(distance_relation)));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "lin", tol_synset_value, tol_relation_value, std::ref(dist_yandex), std::ref(distance_lin), std::ref(distance_relation)));

                            cout << "waiting for threads to join..." << endl;
                            for (auto& th : ths) {
                                th.join();
                            }
                        }
                    }
                }
            }
            catch (std::exception& e) {
                cerr << "Error: '" << e.what() << "'" << endl;
            }
        }
        ++it;
    }
    fout.close();
    return 0;
}
