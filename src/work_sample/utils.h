
#pragma once

#include <iostream>
#include <fstream>
#include <time.h>
#include <mutex>

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
    float distance_graphs(unl_graph& result,
                          distance::base_graph::conceptual_graph_corresponde& s1_to_result,
                          distance::base_graph::conceptual_graph_corresponde& s2_to_result,
                          distance::base_synset& words_dist, distance::base_relation& rels_dist, float synset_tolerance = 0.f, float relation_tolerance = 0.f, const std::string& more_txt = "") const {
        GraphDistance graph_distance(words_dist, rels_dist);
        auto penalize_node = words_dist.upper_bound();
        auto penalize_edge = rels_dist.upper_bound();
        auto min_d = graph_distance.lower_bound(graph1, graph2, penalize_node, penalize_edge);
        auto max_d = graph_distance.upper_bound(graph1, graph2, penalize_node, penalize_edge);
        //cout << " - Similarity in [" << min_d << ", " << max_d << "]" << endl;

        // Variables to hold results
        auto data = graph_distance.max_similarity(graph1, graph2, synset_tolerance, relation_tolerance, result, s1_to_result, s2_to_result);
        //cout << " - Max similarity is " << data << endl;
        cout << "\t - " << more_txt << " -- " << title << ": " << data / max_d;
        cout << "\t\t|>> nodes = " << result.get_nodes().size() << "  |>> edges = " << result.get_edges().size() << endl;
        //result.print(std::cout);
        return data / max_d;
    }

    template <class GraphDistance>
    float distance_graphs(distance::base_synset& words_dist, distance::base_relation& rels_dist, float synset_tolerance = 0.f, float relation_tolerance = 0.f, const std::string& more_txt = "") const {
        unl_graph result;
        distance::base_graph::conceptual_graph_corresponde s1_to_result;
        distance::base_graph::conceptual_graph_corresponde s2_to_result;
        return this->distance_graphs<GraphDistance>(result, s1_to_result, s2_to_result, words_dist, rels_dist, synset_tolerance, relation_tolerance, more_txt);
    }

    const conceptual_graph& graph1;
    const conceptual_graph& graph2;
    std::string title;
};



std::mutex fout_mutex;
void comparison_task_plot(std::ofstream& fout, const std::string& filename, const std::string& graph, const std::string& distance, const float& tol_synset_value, const float& tol_relation_value, graph_dist& graph_dist_, distance::base_synset& words_dist, distance::base_relation& rels_dist, const std::string& output_file) {
    unl_graph result;
    distance::base_graph::conceptual_graph_corresponde s1_to_result;
    distance::base_graph::conceptual_graph_corresponde s2_to_result;

    const clock_t begin_time = clock();
    auto data = graph_dist_.distance_graphs<distance::mcs>(result, s1_to_result, s2_to_result, words_dist, rels_dist, tol_synset_value, tol_relation_value, distance);
    //auto data = 0.f;
    auto seconds = float(clock() - begin_time) / CLOCKS_PER_SEC;

    // Print results to file
    ofstream graph_match_file;
    graph_match_file.open(output_file, ofstream::out | ofstream::trunc);

    result.print(graph_match_file, true);
    graph_match_file << endl << endl;
    graph_match_file << "// Correspondence to original (original -> intersect)" << endl;
    for (auto& item: s1_to_result) {
        graph_match_file << "// " << item.first << " <-> " << item.second << endl;
    }
    graph_match_file << endl << "// Correspondence to other (" << graph << " -> intersect)" << endl;
    for (auto& item: s2_to_result) {
        graph_match_file << "// " << item.first << " <-> " << item.second << endl;
    }
    graph_match_file.flush();
    graph_match_file.close();

    fout_mutex.lock();
    fout << filename << ";\t" << graph << ";\t" << distance << ";\t" << tol_synset_value << ";\t" << tol_relation_value << ";\t"
        << data
        << ";\t" << seconds << "\n";
    fout.flush();
    fout_mutex.unlock();
}

void comparison_task(std::ofstream& fout, const std::string& filename, const std::string& graph, const std::string& distance, const float& tol_synset_value, const float& tol_relation_value, graph_dist& graph_dist_, distance::base_synset& words_dist, distance::base_relation& rels_dist) {
    const clock_t begin_time = clock();
    auto data = graph_dist_.distance_graphs<distance::mcs>(words_dist, rels_dist, tol_synset_value, tol_relation_value, distance);
    //auto data = 0.f;
    auto seconds = float(clock() - begin_time) / CLOCKS_PER_SEC;

    fout_mutex.lock();
    fout << filename << ";\t" << graph << ";\t" << distance << ";\t" << tol_synset_value << ";\t" << tol_relation_value << ";\t"
        << data
        << ";\t" << seconds << "\n";
    fout.flush();
    fout_mutex.unlock();
}
