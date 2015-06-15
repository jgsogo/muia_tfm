
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>

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

using namespace wn;
using namespace std;
namespace fs = ::boost::filesystem;


struct graph_dist {
    graph_dist(conceptual_graph& g1, conceptual_graph& g2) : graph1(g1), graph2(g2) {};

    template <class GraphDistance>
    void distance_graphs(distance::base_synset& words_dist, distance::base_relation& rels_dist, float synset_tolerance = 0.f, float relation_tolerance = 0.f) {
        GraphDistance graph_distance(words_dist, rels_dist);
        auto penalize_node = words_dist.upper_bound();
        auto penalize_edge = rels_dist.upper_bound();
        auto min_d = graph_distance.lower_bound(graph1, graph2, penalize_node, penalize_edge);
        auto max_d = graph_distance.upper_bound(graph1, graph2, penalize_node, penalize_edge);
        cout << " - Similarity in [" << min_d << ", " << max_d << "]" << endl;

        // Variables to hold results
        unl_graph result;
        auto data = graph_distance.max_similarity(graph1, graph2, synset_tolerance, relation_tolerance, result);
        //cout << " - Max similarity is " << data << endl;
        cout << " - Ratio " << data / max_d << endl;
        //result.print(std::cout);
    }

    conceptual_graph& graph1;
    conceptual_graph& graph2;
};


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

    cout << "## Original graph" << endl;
    wn::unl_graph original;
    parse_graph(sample_file, "Original", wnet, original);
    original.print(std::cout);

    cout << "## Google graph" << endl;
    wn::unl_graph google;
    parse_graph(sample_file, "Google", wnet, google);
    google.print(std::cout);

    cout << "## Yandex graph" << endl;
    wn::unl_graph yandex;
    parse_graph(sample_file, "Yandex", wnet, yandex);
    yandex.print(std::cout);

    cout << endl;
    cout << "# Computing distances" << endl;
    cout << "#-------------------------------" << endl;
    distance::shortest_path shortest_path(wnet);
    distance::sussna distance_sussna(graph);
    distance::wu_palmer distance_wu_palmer(graph);
    distance::leacock_chodorow distance_leacock_chodorow(graph);
    distance::resnik distance_resnik(graph, corpus);
    distance::jiang_conrath distance_jiang_conrath(graph, corpus);
    distance::lin distance_lin(graph, corpus);

    graph_dist dist_original(original, google);
    graph_dist dist_yandex(original, yandex);
    distance::base_relation_unl distance_relation;

    auto tolerance = .5f;
    cout << endl;
    cout << "# Distance 'shortest_path' between graphs" << endl;
    cout << "#-------------------------------" << endl;
    dist_original.distance_graphs<distance::mcs>(shortest_path, distance_relation, tolerance, tolerance);
    dist_yandex.distance_graphs<distance::mcs>(shortest_path, distance_relation, tolerance, tolerance);

    cout << endl;
    cout << "# Distance 'distance_sussna' between graphs" << endl;
    cout << "#-------------------------------" << endl;
    //dist_original.distance_graphs<distance::mcs>(distance_sussna, distance_relation, tolerance, tolerance);
    //dist_yandex.distance_graphs<distance::mcs>(distance_sussna, distance_relation, tolerance, tolerance);

    cout << endl;
    cout << "# Distance 'distance_wu_palmer' between graphs" << endl;
    cout << "#-------------------------------" << endl;
    dist_original.distance_graphs<distance::mcs>(distance_wu_palmer, distance_relation, tolerance, tolerance);
    dist_yandex.distance_graphs<distance::mcs>(distance_wu_palmer, distance_relation, tolerance, tolerance);

    cout << endl;
    cout << "# Distance 'distance_leacock_chodorow' between graphs" << endl;
    cout << "#-------------------------------" << endl;
    dist_original.distance_graphs<distance::mcs>(distance_leacock_chodorow, distance_relation, tolerance, tolerance);
    dist_yandex.distance_graphs<distance::mcs>(distance_leacock_chodorow, distance_relation, tolerance, tolerance);

    cout << endl;
    cout << "# Distance 'distance_resnik' between graphs" << endl;
    cout << "#-------------------------------" << endl;
    dist_original.distance_graphs<distance::mcs>(distance_resnik, distance_relation, tolerance, tolerance);
    dist_yandex.distance_graphs<distance::mcs>(distance_resnik, distance_relation, tolerance, tolerance);

    cout << endl;
    cout << "# Distance 'distance_jiang_conrath' between graphs" << endl;
    cout << "#-------------------------------" << endl;
    dist_original.distance_graphs<distance::mcs>(distance_jiang_conrath, distance_relation, tolerance, tolerance);
    dist_yandex.distance_graphs<distance::mcs>(distance_jiang_conrath, distance_relation, tolerance, tolerance);

    cout << endl;
    cout << "# Distance 'distance_lin' between graphs" << endl;
    cout << "#-------------------------------" << endl;
    dist_original.distance_graphs<distance::mcs>(distance_lin, distance_relation, tolerance, tolerance);
    dist_yandex.distance_graphs<distance::mcs>(distance_lin, distance_relation, tolerance, tolerance);

}
