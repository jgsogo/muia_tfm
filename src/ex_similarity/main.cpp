
#include <iostream>
#include <vector>

#include "wnb/core/wordnet.hh"
#include "wnb/nltk_similarity.hh"

using namespace std;
using namespace wnb;

void info(wordnet& wn, const std::string& word) {
    nltk_similarity similarity(wn);
    auto synsets = wn.get_synsets(word);

    for (auto& synset: synsets) {
        cout << synset.id << "[" << synset.pos << "] : ";
        for (auto& w: synset.words) {
            cout << w << ", ";
        }
        cout << " -> " << synset.gloss << "." << endl;

        auto map = similarity.hypernym_map(synset.id);        
        for (auto it = map.begin(); it!=map.end(); ++it) {
            auto data = wn.wordnet_graph[it->first];
            cout << "\t" << it->second << ": ";
            for (auto& w: data.words) {
	        cout << w << ", ";
	    }
	    cout << endl;
        }
    }
}

int main(int argc, char** argv) {
	if (argc != 2) {
		cout << "usage: " << argv[0] << " <path/to/wordnet-3.0/>" << endl;
		exit(1);
	}
	wordnet wn(argv[1], true);

    //cout << endl << "==== WORD -- Cat" << endl;
    //info(wn, "cat");

    //cout << endl << "==== WORD -- Dog" << endl;
    //info(wn, "dog");

	cout << "Similarity between 'cat' and 'dog'" << endl;
    vector<synset> synsets1 = wn.get_synsets("cat");
    vector<synset> synsets2 = wn.get_synsets("dog");

    nltk_similarity similarity(wn);

    for (auto& s1: synsets1) {
        cout << "_____________________" << endl << endl;
        cout << s1.id << "[" << get_name_from_pos(s1.pos) << "] : ";
        for (auto& w: s1.words) {
            cout << w << ", ";
        }
        cout << " -> " << s1.gloss << "." << endl;

        for (auto& s2: synsets2) {
            if (s1.pos == s2.pos) {
                auto distance = similarity.shortest_path_distance(s1, s2);
                cout << "\t" << distance << "\t|";
                for(auto& w: s2.words) {
                    cout << w << ", ";
                }
                //cout << " -> " << s2.gloss << ".";
                cout << endl;
            }
        }
    }
    
}
