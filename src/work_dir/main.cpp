
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>
#include <time.h>
#include <thread>
#include <mutex>

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

using namespace wn;
using namespace std;
namespace fs = ::boost::filesystem;

std::string get_current_datetime() {
    // Credit: http://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%H-%M-%S", &tstruct);

    return buf;
}

struct graph_dist {
    graph_dist(conceptual_graph& g1, conceptual_graph& g2, const std::string& title) : graph1(g1), graph2(g2), title(title) {};

    template <class GraphDistance>
    float distance_graphs(distance::base_synset& words_dist, distance::base_relation& rels_dist, float synset_tolerance = 0.f, float relation_tolerance = 0.f, const std::string& more_txt = "") const {
        GraphDistance graph_distance(words_dist, rels_dist);
        auto penalize_node = words_dist.upper_bound();
        auto penalize_edge = rels_dist.upper_bound();
        auto min_d = graph_distance.lower_bound(graph1, graph2, penalize_node, penalize_edge);
        auto max_d = graph_distance.upper_bound(graph1, graph2, penalize_node, penalize_edge);
        //cout << " - Similarity in [" << min_d << ", " << max_d << "]" << endl;

        // Variables to hold results
        unl_graph result;
        auto data = graph_distance.max_similarity(graph1, graph2, synset_tolerance, relation_tolerance, result);
        //cout << " - Max similarity is " << data << endl;
        cout << "\t - " << more_txt << " -- " << title << ": " << data / max_d << endl;
        //result.print(std::cout);
        return data / max_d;
    }

    const conceptual_graph& graph1;
    const conceptual_graph& graph2;
    std::string title;
};

std::mutex fout_mutex;
void comparison_task(std::ofstream& fout, const std::string& filename, const std::string& graph, const std::string& distance, const float& tol_synset_value, const float& tol_relation_value, graph_dist& graph_dist_, distance::base_synset& words_dist, distance::base_relation& rels_dist) {
    const clock_t begin_time = clock();
    auto data = graph_dist_.distance_graphs<distance::mcs>(words_dist, rels_dist, tol_synset_value, tol_relation_value, distance);
    auto seconds = float(clock() - begin_time) / CLOCKS_PER_SEC;

    fout_mutex.lock();
    fout << filename << ";\t" << graph << ";\t" << distance << ";\t" << tol_synset_value << ";\t" << tol_relation_value << ";\t"
        << data
        << ";\t" << seconds << "\n";
    fout.flush();
    fout_mutex.unlock();
}


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
    distance::shortest_path shortest_path(wnet);
    distance::sussna distance_sussna(graph);
    distance::wu_palmer distance_wu_palmer(graph);
    distance::leacock_chodorow distance_leacock_chodorow(graph);
    distance::resnik distance_resnik(graph, corpus);
    distance::jiang_conrath distance_jiang_conrath(graph, corpus);
    distance::lin distance_lin(graph, corpus);

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
    auto tol_synset_values = {0.f, 0.4f};
    auto tol_relation_values = {0.f, 0.4f};
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
                ofstream fgoo; fgoo.open(directory + fileid + "_google.dot"); original.print(fgoo, true); fgoo.close();
                wn::unl_graph yandex;
                auto yandex_graph = parse_graph(filename, "Yandex", wnet, yandex);
                ofstream fyan; fyan.open(directory + fileid + "_yandex.dot"); original.print(fyan, true); fyan.close();

                if (ori_graph && google_graph) {
                    graph_dist dist_original(original, google, "google");
                    for (auto tol_synset_value : tol_synset_values) {
                        for (auto tol_relation_value : tol_relation_values) {
                            cout << " - tol_synset_value = " << tol_synset_value << endl;
                            cout << " - tol_relation_value = " << tol_relation_value << endl;

                            vector<thread> ths;
                            //void comparison_task(ofstream fout, const std::string& filename, const std::string& graph, const std::string& distance, const float& tol_synset_value, const float& tol_relation_value, graph_dist& graph_dist_, distance::base_synset& words_dist, distance::base_relation& rels_dist) {
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "shortest_path", tol_synset_value, tol_relation_value, std::ref(dist_original), std::ref(shortest_path), std::ref(distance_relation)));
                            //ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "sussna", tol_synset_value, tol_relation_value, dist_original, distance_sussna, distance_relation));
                            //ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "wu-palmer", tol_synset_value, tol_relation_value, dist_original, distance_wu_palmer, distance_relation));
                            //ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "leacock-chodorow", tol_synset_value, tol_relation_value, dist_original, distance_leacock_chodorow, distance_relation));
                            //ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "resnik", tol_synset_value, tol_relation_value, dist_original, distance_resnik, distance_relation));
                            //ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "jiang-conrath", tol_synset_value, tol_relation_value, dist_original, distance_jiang_conrath, distance_relation));
                            //ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "google", "lin", tol_synset_value, tol_relation_value, dist_original, distance_lin, distance_relation));

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
                            /*
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "shortest_path", tol_synset_value, tol_relation_value, dist_yandex, shortest_path, distance_relation));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "sussna", tol_synset_value, tol_relation_value, dist_yandex, distance_sussna, distance_relation));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "wu-palmer", tol_synset_value, tol_relation_value, dist_yandex, distance_wu_palmer, distance_relation));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "leacock-chodorow", tol_synset_value, tol_relation_value, dist_yandex, distance_leacock_chodorow, distance_relation));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "resnik", tol_synset_value, tol_relation_value, dist_yandex, distance_resnik, distance_relation));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "jiang-conrath", tol_synset_value, tol_relation_value, dist_yandex, distance_jiang_conrath, distance_relation));
                            ths.push_back(std::thread(&comparison_task, std::ref(fout), it->path().filename().string(), "yandex", "lin", tol_synset_value, tol_relation_value, dist_yandex, distance_lin, distance_relation));
                            */

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
