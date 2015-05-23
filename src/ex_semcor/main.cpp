
#include <iostream>
#include <vector>

#include "wnb/core/wordnet.hh"
#include "corpus/semcor.h"

using namespace std;
using namespace wnb;


int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "usage: " << argv[0] << " <path/to/wordnet-3.0/> <path/to/semcor/>" << endl;
		exit(1);
	}
    cout << endl;
    cout << "# Loading WordNet" << endl;
    cout << "#-------------------------------" << endl;
	wordnet wn(argv[1]);

    cout << "# Reading SemCor" << endl;
    cout << "#-------------------------------" << endl;
	wn::semcor corpus(wn);
    vector<string> filenames;
    string basepath = argv[2];
    filenames.push_back(basepath + "brown1/tagfiles/br-a01.xml");
    //filenames.push_back(basepath + "brown1/tagfiles/br-a01");
    //filenames.push_back(basepath + "brown1/tagfiles/br-a01");

    corpus.add_documents(filenames);
}
