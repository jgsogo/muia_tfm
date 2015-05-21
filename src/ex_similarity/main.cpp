
#include <iostream>
#include <vector>

#include "wnb/core/wordnet.hh"
#include "distance/shortest_path.h"

using namespace std;
using namespace wnb;


int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "usage: " << argv[0] << " <path/to/wordnet-3.0/>" << endl;
		exit(1);
	}
	wordnet wn(argv[1], true);

	cout << "Similarity between 'cat' and 'dog'" << endl;
    vector<synset> synsets1 = wn.get_synsets("cat");
    vector<synset> synsets2 = wn.get_synsets("dog");

	cout << "94185: " << wn.wordnet_graph[94185] << endl;
	cout << "94190: " << wn.wordnet_graph[94190] << endl;

	wn::shortest_path dist(wn);
	cout << " - min_distance = " << dist.min() << endl;
	cout << " - max_distance = " << dist.max() << endl;

    for (auto& s1: synsets1) {
        cout << "_____________________" << endl << endl;
        cout << s1 << " -> " << s1.gloss << "." << endl;

        for (auto& s2: synsets2) {
            if (s1.pos == s2.pos) {
				auto distance = dist(s1, s2);
				cout << "\t" << distance << "\t| " << s2 << endl;
            }
        }
    }
}
