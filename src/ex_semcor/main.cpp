
#include <iostream>
#include <vector>

#include <boost/filesystem.hpp>
#include "../wordnet/wordnet.h"
#include "corpus/semcor.h"

using namespace wn;
using namespace std;
namespace fs = ::boost::filesystem;


int main(int argc, char** argv) {
	if (argc != 3) {
		cout << "usage: " << argv[0] << " <path/to/wordnet-3.0/> <path/to/semcor/>" << endl;
		exit(1);
	}
    cout << endl;
    cout << "# Loading WordNet" << endl;
    cout << "#-------------------------------" << endl;
	wordnet wnet(argv[1]);

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

    // Print some stats
    cout << endl;
    cout << "# Stats about SemCor" << endl;
    cout << "#-------------------------------" << endl;
    auto documents = corpus.get_documents();
    auto index = corpus.get_index();
    cout << " - documents parsed: " << documents.size() << endl;
    cout << " - index size: " << index.size() << endl;

}
