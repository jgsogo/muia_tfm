
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

#include "wnb/core/wordnet.hh"
#include "../wordnet/hyperonym_graph.h"
#include "../distance/shortest_path.h"
#include "../distance/distance_sussna.h"
#include "../distance/distance_wu_palmer.h"
#include "../distance/distance_leacock_chodorow.h"
#include "../distance/distance_resnik.h"
#include "../distance/distance_jiang_conrath.h"
#include "../distance/distance_lin.h"
#include "../corpus/semcor.h"

using namespace std;
using namespace wnb;
namespace fs = ::boost::filesystem;

void print_orphans(vector<synset>::iterator begin, vector<synset>::iterator end, const wordnet& wn) {
    for (; begin != end; ++begin) {
        auto orph1 = *begin;
        cout << endl << orph1 << endl;
        // out_edges
        cout << " - out_edges targets: " << endl;
        boost::graph_traits<wordnet::graph>::out_edge_iterator e, e_end;
        std::tie(e, e_end) = boost::out_edges(orph1.id, wn.wordnet_graph);
        for (; e != e_end; ++e) {
            auto edge = wn.wordnet_graph[*e];
            cout << "\t" << info_helper::symbols[edge.pointer_symbol];
            auto v = boost::target(*e, wn.wordnet_graph);
            cout << ": " << wn.wordnet_graph[v];
            cout << endl;
        }

        // in_edges
        cout << " - in_edges sources: " << endl;
        boost::graph_traits<wordnet::graph>::in_edge_iterator in, in_end;
        std::tie(in, in_end) = boost::in_edges(orph1.id, wn.wordnet_graph);
        for (; in != in_end; ++in) {
            auto edge = wn.wordnet_graph[*in];
            cout << "\t" << info_helper::symbols[edge.pointer_symbol];
            auto v = boost::source(*in, wn.wordnet_graph);
            cout << ": " << wn.wordnet_graph[v];
            cout << endl;
        }

    }
}

int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "usage: " << argv[0] << " <path/to/wordnet-3.1/dict/> <path/to/semcor/>" << endl;
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
    cout << "# Stats about loaded WordNet" << endl;
    cout << "#-------------------------------" << endl;
    cout << "Distance 'shortest_path':" << endl;
    wn::distance::shortest_path shortest_path(wn);
    cout << " - min_distance = " << shortest_path.min() << endl;
    cout << " - max_distance = " << shortest_path.max() << endl;

    cout << "Distance 'sussna':" << endl;
    wn::distance::sussna distance_sussna(graph);
    cout << " - min_distance = " << distance_sussna.min() << endl;
    cout << " - max_distance = " << distance_sussna.max() << endl;

    cout << "Distance 'Wu and Palmer':" << endl;
    wn::distance::wu_palmer distance_wu_palmer(graph);
    cout << " - min_distance = " << distance_wu_palmer.min() << endl;
    cout << " - max_distance = " << distance_wu_palmer.max() << endl;

    cout << "Distance 'Leacock and Chodorow':" << endl;
    wn::distance::leacock_chodorow distance_leacock_chodorow(graph);
    cout << " - min_distance = " << distance_leacock_chodorow.min() << endl;
    cout << " - max_distance = " << distance_leacock_chodorow.max() << endl;

    cout << "Distance 'Resnik 1995':" << endl;
    wn::distance::resnik distance_resnik(graph, corpus);
    cout << " - min_distance = " << distance_resnik.min() << endl;
    cout << " - max_distance = " << distance_resnik.max() << endl;

    cout << "Distance 'Jiang && Conrath':" << endl;
    wn::distance::jiang_conrath distance_jiang_conrath(graph, corpus);
    cout << " - min_distance = " << distance_jiang_conrath.min() << endl;
    cout << " - max_distance = " << distance_jiang_conrath.max() << endl;

    cout << "Distance 'Lin':" << endl;
    wn::distance::lin distance_lin(graph, corpus);
    cout << " - min_distance = " << distance_lin.min() << endl;
    cout << " - max_distance = " << distance_lin.max() << endl;

    /*
    auto orphs = wn::hyperonym_graph::orphans(wn, true);
    decltype(orphs) orphs_nouns; std::copy_if(orphs.begin(), orphs.end(), std::back_inserter(orphs_nouns), [](const synset& s){return s.pos == pos_t::N; });
    decltype(orphs) orphs_verbs; std::copy_if(orphs.begin(), orphs.end(), std::back_inserter(orphs_verbs), [](const synset& s){return s.pos == pos_t::V; });
    decltype(orphs) orphs_adjs;  std::copy_if(orphs.begin(), orphs.end(), std::back_inserter(orphs_adjs), [](const synset& s){return s.pos == pos_t::A || s.pos==pos_t::S; });
    decltype(orphs) orphs_advs;  std::copy_if(orphs.begin(), orphs.end(), std::back_inserter(orphs_advs), [](const synset& s){return s.pos == pos_t::R; });
    cout << "Orphans (" << orphs.size() << "):" << endl;
    cout << "\t nouns: " << orphs_nouns.size() << endl;
    cout << "\t verbs: " << orphs_verbs.size() << endl;
    cout << "\t adjs: " << orphs_adjs.size() << endl;
    cout << "\t advs: " << orphs_advs.size() << endl;
    auto n_orphs = 1;
    cout << endl; print_orphans(orphs_nouns.begin(), (orphs_nouns.size() > n_orphs) ? orphs_nouns.begin() + n_orphs : orphs_nouns.end(), wn);
    cout << endl; print_orphans(orphs_verbs.begin(), (orphs_verbs.size() > n_orphs) ? orphs_verbs.begin() + n_orphs : orphs_verbs.end(), wn);
    cout << endl; print_orphans(orphs_adjs.begin(), (orphs_adjs.size() > n_orphs) ? orphs_adjs.begin() + n_orphs : orphs_adjs.end(), wn);
    cout << endl; print_orphans(orphs_advs.begin(), (orphs_advs.size() > n_orphs) ? orphs_advs.begin() + n_orphs : orphs_advs.end(), wn);
    */

    cout << endl;
    cout << "# Distance between synsets" << endl;
    cout << "#-------------------------------" << endl;
    vector<synset> synsets1 = wn.get_synsets("cat");
    vector<synset> synsets2 = wn.get_synsets("dog");
    cout << "cat[0] = " << synsets1[0] << endl;
    cout << "dog[0] = " << synsets2[0] << endl;
    cout << "shortest_path(cat[0], dog[0]) = " << shortest_path(synsets1[0], synsets2[0]) << endl;
    cout << "sussna(cat[0], dog[0]) = " << distance_sussna(synsets1[0], synsets2[0]) << endl;
    cout << "wu_palmer(cat[0], dog[0]) = " << distance_wu_palmer(synsets1[0], synsets2[0]) << endl;
    cout << "leacock_chodorow(cat[0], dog[0]) = " << distance_leacock_chodorow(synsets1[0], synsets2[0]) << endl;
    cout << "resnik(cat[0], dog[0]) = " << distance_resnik(synsets1[0], synsets2[0]) << endl;
    cout << "jiang_conrath(cat[0], dog[0]) = " << distance_jiang_conrath(synsets1[0], synsets2[0]) << endl;
    cout << "lin(cat[0], dog[0]) = " << distance_lin(synsets1[0], synsets2[0]) << endl;


    auto n = std::min(size_t(3), std::min(synsets1.size(), synsets2.size()));
    auto distance_synsets = [n, &synsets1, &synsets2](wn::distance::base& dist){
        auto penalize_each = dist.max();
        vector<wn::distance::base::_t_distance> distances;
        auto s1 = vector<synset>(synsets1.begin(), synsets1.begin() + n);
        auto data = dist.min_distance(s1, synsets2, distances, penalize_each);
        auto min_d = dist.min(s1, synsets2, penalize_each);
        auto max_d = dist.max(s1, synsets2, penalize_each);
        cout << " - Distance € [" << min_d << ", " << max_d  << "]" << endl;
        cout << " - Min distance is " << data << endl;
        cout << " - Ratio " << (data-min_d) / (max_d-min_d) << endl;
        cout << " - Combinations: " << distances.size() << endl;
        for (auto it_dist = distances.begin(); it_dist != distances.end(); ++it_dist) {
            cout << " - Candidate pairs: " << endl;
            auto dist_sum = 0.f;
            for (auto& p : *it_dist) {
                dist_sum += get<2>(p);
                cout << "\t" << get<2>(p) << "\t|" << get<0>(p) << endl;
                cout << "\t\t|" << get<1>(p) << endl;
                cout << endl;
            }
            cout << "\t" << penalize_each << "*" << synsets2.size()-n << "=" << penalize_each*(synsets2.size()-n) << endl;
            cout << "\t=" << data << endl;
        }
    };

    cout << endl;
    cout << "# Distance 'shortest_path' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    distance_synsets(shortest_path);

    cout << endl;
    cout << "# Distance 'Sussna' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    distance_synsets(distance_sussna);

    cout << endl;
    cout << "# Distance 'Wu Palmer' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    distance_synsets(distance_wu_palmer);

    cout << endl;
    cout << "# Distance 'Leacock & Chodorow' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    distance_synsets(distance_leacock_chodorow);

    cout << endl;
    cout << "# Distance 'Resnik' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    distance_synsets(distance_resnik);

    cout << endl;
    cout << "# Distance 'Jiang && Conrath' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    distance_synsets(distance_jiang_conrath);

    cout << endl;
    cout << "# Distance 'Lin' between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    distance_synsets(distance_lin);


}
