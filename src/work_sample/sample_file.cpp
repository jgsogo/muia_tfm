
#include "sample_file.h"
#include <sstream>
#include <fstream>
#include <boost/algorithm/string.hpp>

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
}

tuple<size_t, string, wn::lex_sense> parse_term(const string& term) {
    // term := id%lemma%lex_sense
}

void parse_graph(const string& filename, const string& section,
                 const wn::wordnet& wnet, wn::unl_graph& graph) {
    // Look for file and point to section
    ifstream infile(filename);
    find_section(infile, section);

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
            auto term2 = line.substr(found_c+1, found_e-found_c-1);

            cout << ".." << rel_type << "|" << term1 << "|" << term2 << "|" << endl;
            auto term1_data = parse_term(term1);
            auto term2_data = parse_term(term2);
        }
    }

 }
