
#include <iostream>
#include <vector>

#include "wnb/core/wordnet.hh"
#include "distance/shortest_path.h"
#include "wordnet/hyperonym_graph.h"

using namespace std;
using namespace wnb;

void print_orphans(vector<synset>::iterator begin, vector<synset>::iterator end, const wordnet& wn) {
    for (; begin != end; ++begin) {
        auto orph1 = *begin;
        cout << endl << orph1 << endl;
        // out_edges
        cout << " - out_edges: " << endl;
        boost::graph_traits<wordnet::graph>::out_edge_iterator e, e_end;
        std::tie(e, e_end) = boost::out_edges(orph1.id, wn.wordnet_graph);
        for (; e != e_end; ++e) {
            auto edge = wn.wordnet_graph[*e];
            cout << "\t" << info_helper::symbols[edge.pointer_symbol];
            auto v = boost::target(*e, wn.wordnet_graph);
            cout << ": " << wn.wordnet_graph[v];
            cout << endl;
        }
        // out_edges
        cout << " - in_edges: " << endl;
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
	if (argc != 2) {
		cout << "usage: " << argv[0] << " <path/to/wordnet-3.0/>" << endl;
		exit(1);
	}
    cout << endl;
    cout << "# Loading WordNet" << endl;
    cout << "#-------------------------------" << endl;
	wordnet wn(argv[1]);

    cout << endl;
    cout << "# Stats about loaded WordNet" << endl;
    cout << "#-------------------------------" << endl;
    cout << "Distance 'shortest_path':" << endl;
    wn::shortest_path dist(wn);
    cout << " - min_distance = " << dist.min() << endl;
    cout << " - max_distance = " << dist.max() << endl;

    wn::hyperonym_graph graph(wn, true);
    auto orphs = graph.orphans();
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
    
    cout << endl;
    cout << "# Distance between synsets" << endl;
    cout << "#-------------------------------" << endl;
    vector<synset> synsets1 = wn.get_synsets("cat");
    vector<synset> synsets2 = wn.get_synsets("dog");
    cout << "cat[0] = " << synsets1[0] << endl;
    cout << "dog[0] = " << synsets2[0] << endl;
    cout << "distance(cat[0], dog[0]) = " << dist(synsets1[0], synsets2[0]) << endl;

    cout << endl;
    cout << "# Distance between synset sets" << endl;
    cout << "#-------------------------------" << endl;
    auto n = std::min(synsets1.size(), synsets2.size());
    vector<wn::distance::_t_distance> distances;
    auto data = dist.min_distance(vector<synset>(synsets1.begin(), synsets1.begin() + n), vector<synset>(synsets2.begin(), synsets2.begin() + n), distances);
    cout << " - Min distance is " << data << endl;
    cout << " - Combinations: " << distances.size() << endl;
    for (auto it_dist = distances.begin(); it_dist != distances.end() && it_dist != distances.begin() + 3; ++it_dist) {
        cout << " - Candidate pairs: " << endl;
        auto dist_sum = 0;
        for (auto& p : *it_dist) {
            dist_sum += get<2>(p);
            cout << "\t" << get<2>(p) << "\t|" << get<0>(p) << endl;
            cout << "\t\t|" << get<1>(p) << endl;
            cout << endl;
        }
        cout << "\t=" << dist_sum << endl;
    }

}
