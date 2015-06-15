
#include "sample_file.h"
#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "../conceptual_graph/unl_relation.h"

using namespace std;

bool is_comment(const string& line) {
    return (line.substr(0, 1).compare(";") == 0);
}

bool section_title(const string& line, string& title) {
    if (line.substr(0, 1).compare("#") == 0) {
        title = line.substr(1);
        boost::algorithm::trim(title);
        return true;
    }
    return false;
}

ifstream& find_section(ifstream& infile, const string& section) {
    string line, title;
    while (std::getline(infile, line)) {
        if (section_title(line, title) && section.compare(title)==0) {
            break;
        }
    }
    return infile;
}

tuple<size_t, string, wn::lex_sense> parse_term(const string& term) {
    // term := id%lemma%lex_sense
    tuple<size_t, string, wn::lex_sense> ret = make_tuple(1, "", wn::lex_sense());
    stringstream ss(term);
    string item;
    vector<string> elems;
    while (getline(ss, item, '%')) {
        elems.push_back(item);
    }

    auto it_rev = elems.rbegin();
    wn::lex_sense lexsn = wn::parse_lexsn(*it_rev++);
    string lemma = (*it_rev++);
    size_t id = (it_rev != elems.rend()) ? atoi((*it_rev).c_str()) : 0;
    
    return make_tuple(id, lemma, lexsn);
}

void parse_graph(const string& filename, const string& section,
                 const wn::wordnet& wnet, wn::unl_graph& graph) {
    // Look for file and point to section
    ifstream infile(filename);
    find_section(infile, section);

    std::map<tuple<size_t, string, wn::lex_sense>, wn::conceptual_graph::synset_id> node_map;
    bool in_graph = false;
    string line, title;
    while (std::getline(infile, line) && !section_title(line, title)) {
        if (is_comment(line)) {
            continue;
        }

        boost::algorithm::trim(line);
        // Look for unl graph
        if (!in_graph) {
            in_graph = (line.compare("{unl}")==0);
        }
        else {
            if (line.compare("{/unl}")==0) {
                break;
            }
            // Here we have the UNL graph, parse it!
            auto found_s = line.find("(");
            auto found_e = line.find(")", found_s);
            auto found_c = line.find(",", found_s);

            auto rel_type = line.substr(0, found_s);
            auto term1 = line.substr(found_s+1, found_c-found_s-1);
            boost::trim(term1);
            auto term2 = line.substr(found_c+1, found_e-found_c-1);
            boost::trim(term2);

            cout << ".." << rel_type << "|" << term1 << "|" << term2 << "|" << endl;
            auto term1_data = parse_term(term1);
            auto term2_data = parse_term(term2);

            auto term1_it = node_map.insert(make_pair(term1_data, 0));
            auto term2_it = node_map.insert(make_pair(term2_data, 0));
            if (term1_it.second) {
                auto term1_id = wn::search_synset(wnet, get<1>(term1_data), get<2>(term1_data));
                if (term1_id == -1) {
                    cerr << "Error: term '" << term1 << "' not found!" << endl;
                }
                term1_it.first->second = graph.add_node(wnet.wordnet_graph[term1_id]);
            }
            if (term2_it.second) {
                auto term2_id = wn::search_synset(wnet, get<1>(term2_data), get<2>(term2_data));
                if (term2_id == -1) {
                    cerr << "Error: term '" << term2 << "' not found!" << endl;
                }
                term2_it.first->second = graph.add_node(wnet.wordnet_graph[term2_id]);
            }

            wn::unl::relation::type unl_rel_type;
            wn::unl::from_string(rel_type, unl_rel_type);

            graph.add_relation(term1_it.first->second, term2_it.first->second, unl_rel_type);
        }
    }
 }
