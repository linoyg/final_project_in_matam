#include <iostream>
#include <fstream>
#include <map>
#include "Graph.h"
#include "Tokenize.h"
#include "Commands.h"
#include "Expression.h"
#include <cctype>
#include"RunShell.h"

using namespace std;


using namespace std;

bool executeCommand(set<Graph> &set_of_graphs, const vector<string> &vec, std::ostream &os);

void runAutomat(char *x1, char *x2) {
//open the file
    ifstream in_fli(x1);
    ofstream outFile(x2);

    //to read lines form the files
    string line;
    set<Graph> set_of_graphs;

    while (getline(in_fli, line)) {
        //remove the space from the string
        vector<string> vec = splitSentence(line);
        if (!executeCommand(set_of_graphs, vec, outFile)) {
            break;
        }
    }
    //finsh reading the file and close all the files
    in_fli.close();
    outFile.close();
}

void runNotAutomat() {
    string prompt = "Gcalc> ";
    std::cout << prompt;
    string line;
    set<Graph> set_of_graphs;
    while (getline(cin, line)) {
        //remove the space from the string
        //TO DO: to chack if i neeed the endl in the end!!!

        //select the right function
        vector<string> vec = splitSentence(line);
        if (!executeCommand(set_of_graphs, vec, cout)) {
            break;
        }
        std::cout << prompt;
    }
}

string joinStrings(const vector<string> &strs, size_t startIndex, size_t lastIndex) {
    string concated;
    for (unsigned int i = startIndex; i < lastIndex + 1; ++i) {
        concated.append(strs[i]);
    }
    return concated;
}

bool executeCommand(set<Graph> &set_of_graphs, const vector<string> &vec, std::ostream &os) {
    try {
        //chack if the is equal.
        if (vec.size() >= 3 && vec[1] == "=" && vec[2] != "load") {
            handleAssignCommand(set_of_graphs, vec);
            return true;
        }
            //THE IS NOT EQUAL

        else if (vec[0] == "print") {

            //if the is operators in the print
            if (vec.size() > 4) {
                string expressionStr;
                for (unsigned int i = 2; i < vec.size() - 1; i++) {
                    expressionStr.append(vec[i]);
                }
                auto expression = parseExpression(expressionStr);
                Graph graph = expression->evaluate(set_of_graphs);

                printGraph(graph, os);
                return true;
            }

            if (vec[1] == "(" && vec[3] == ")") {
                string name_of_first_graph = vec[2];
                Graph g1(name_of_first_graph);
                if (set_of_graphs.find(g1) == set_of_graphs.end()) {
                    throw THE_GRAPH_IS_NOT_EXISTS{};
                }

                printGraph(*set_of_graphs.find(g1), os);
                return true;
            }
            throw Invalid_Sentence{};

        } else if (vec[0] == "who" && vec.size() == 1) {
            //print all the name of the graph that exist in the set
            for (auto i = set_of_graphs.begin(); i != set_of_graphs.end(); i++) {
                os << getNameOfGraphThatExists(*i) << endl;
            }
        } else if ((vec[0] == "reset" && vec.size() == 1)) {
            set_of_graphs.clear();
        } else if (vec[0] == "delete" && vec.size() == 4 && vec[1] == "("
                   && vec[3] == ")") {
            string name_of_first_graph = vec[2];
            Graph g1(name_of_first_graph);
            if (set_of_graphs.find(g1) != set_of_graphs.end()) {
                set_of_graphs.erase(set_of_graphs.find(g1));
            } else {
                throw THE_GRAPH_IS_NOT_EXISTS{};
            }
        }
            //stop the program
        else if ((vec[0] == "quit" && vec.size() == 1)) {
            return false;
        } else if (vec[0] == "save" && vec[1] == "(" && vec[vec.size() - 1] == ")" && vec.size() == 6) {
            string name_of_graph1 = vec[2];
            Graph g1(name_of_graph1);
            if (set_of_graphs.find(g1) == set_of_graphs.end()) {
                throw THE_GRAPH_IS_NOT_EXISTS{};
            }
            Graph graph = *set_of_graphs.find(g1);
            set<string> set_of_vertex = getSetOfVertex(graph);
            set<pair<string, string>> set_of_edges = getSetOfEdges(graph);
            std::ofstream outfile(vec[vec.size() - 2], std::ios_base::binary);
            unsigned int num = set_of_vertex.size();
            outfile.write((const char *) &num, sizeof(unsigned int));
            num = set_of_edges.size();
            outfile.write((const char *) &num, sizeof(unsigned int));

            string name_of_vertex;
            unsigned int num_of_chars;
            for (string ver : set_of_vertex) {
                num_of_chars = ver.size();
                name_of_vertex = ver;
                outfile.write((const char *) &num_of_chars, sizeof(unsigned int));
                for (const char &c : name_of_vertex) {
                    outfile.write(&c, sizeof(char));
                }
            }

            string name_of_first_edge;
            unsigned int num_of_first_edge;
            string name_of_second_edge;
            unsigned int num_of_second_edge;
            for (auto i = set_of_edges.begin(); i != set_of_edges.end(); i++) {
                num_of_first_edge = i->first.size();
                name_of_first_edge = i->first;
                outfile.write((const char *) &num_of_first_edge, sizeof(unsigned int));
                for (const char &c : name_of_first_edge) {
                    outfile.write(&c, sizeof(char));
                }
                num_of_second_edge = i->second.size();
                name_of_second_edge = i->second;
                outfile.write((const char *) &num_of_second_edge, sizeof(unsigned int));
                for (const char &ch : name_of_second_edge) {
                    outfile.write(&ch, sizeof(char));
                }
            }
            outfile.close();
            return true;

        } else if (vec[0] == "save" && vec[1] == "(" && vec[vec.size() - 1] == ")") {
            string expressionStr;
            for (unsigned int i = 2; i < vec.size() - 3; i++) {
                expressionStr.append(vec[i]);
            }
            auto expression = parseExpression(expressionStr);
            Graph graph = expression->evaluate(set_of_graphs);

            set<string> set_of_vertex = getSetOfVertex(graph);
            set<pair<string, string>> set_of_edges = getSetOfEdges(graph);
            std::ofstream outfile(vec[vec.size() - 2], std::ios_base::binary);
            unsigned int num = set_of_vertex.size();
            outfile.write((const char *) &num, sizeof(unsigned int));
            num = set_of_edges.size();
            outfile.write((const char *) &num, sizeof(unsigned int));

            string name_of_vertex;
            unsigned int num_of_chars;
            for (string ver : set_of_vertex) {
                num_of_chars = ver.size();
                name_of_vertex = ver;
                outfile.write((const char *) &num_of_chars, sizeof(unsigned int));
                for (const char &c : name_of_vertex) {
                    outfile.write(&c, sizeof(char));
                }
            }

            string name_of_first_edge;
            unsigned int num_of_first_edge;
            string name_of_second_edge;
            unsigned int num_of_second_edge;
            for (auto i = set_of_edges.begin(); i != set_of_edges.end(); i++) {
                num_of_first_edge = i->first.size();
                name_of_first_edge = i->first;
                outfile.write((const char *) &num_of_first_edge, sizeof(unsigned int));
                for (const char &c : name_of_first_edge) {
                    outfile.write(&c, sizeof(char));
                }
                num_of_second_edge = i->second.size();
                name_of_second_edge = i->second;
                outfile.write((const char *) &num_of_second_edge, sizeof(unsigned int));
                for (const char &ch : name_of_second_edge) {
                    outfile.write(&ch, sizeof(char));
                }
            }
            outfile.close();
            return true;

        } else if (vec[2] == "load" && vec[1] == "=" && vec[3] == "(" && vec[vec.size() - 1] == ")") {

            string name_of_graph = vec[0];
            set<string> set_of_vertex;
            set<pair<string, string>> set_of_edges;
            //open the file
            std::ifstream infile(vec[vec.size() - 2], std::ios_base::binary);

            //num of edges and num of vertex/
            unsigned int num_of_vertex;
            infile.read((char *) &num_of_vertex, sizeof(unsigned int));
            unsigned int num_of_edge;
            infile.read((char *) &num_of_edge, sizeof(unsigned int));

            for (unsigned int i = 0; i < num_of_vertex; i++) {
                unsigned int num_of_chars;
                infile.read((char *) &num_of_chars, sizeof(unsigned int));
                string s = "";
                for (unsigned int j = 0; j < num_of_chars; j++) {
                    char c;
                    infile.read((char *) &c, sizeof(char));
                    s = s + c;
                }
                set_of_vertex.insert(s);
            }

            for (unsigned int i = 0; i < num_of_edge; i++) {
                unsigned int num_of_chars_of_the_first;
                infile.read((char *) &num_of_chars_of_the_first, sizeof(unsigned int));
                string first = "";
                for (unsigned int j = 0; j < num_of_chars_of_the_first; j++) {
                    char c;
                    infile.read((char *) &c, sizeof(char));
                    first = first + c;
                }
                unsigned int num_of_chars_of_the_second;
                infile.read((char *) &num_of_chars_of_the_second, sizeof(unsigned int));
                string second = "";
                for (unsigned int j = 0; j < num_of_chars_of_the_second; j++) {
                    char c;
                    infile.read((char *) &c, sizeof(char));
                    second = second + c;
                }
                //insret the pair to the set.
                pair<string, string> p(first, second);

                set_of_edges.insert(p);
            }
            Graph g1(name_of_graph, set_of_vertex, set_of_edges);
            if (set_of_graphs.find(g1) == set_of_graphs.end()) {
                set_of_graphs.insert(g1);
                infile.close();
                return true;
            }
            else {
                infile.close();
                throw THE_GRAPH_IS_NOT_EXISTS{};
            }
        }
        else {
            throw Invalid_Sentence{};
        }
    }

    catch (THE_GRAPH_IS_NOT_EXISTS &) {
        os << "Error: THE_GRAPH_IS_NOT_EXISTS" << endl;
        return true;
    }
    catch (InvalidDefinition &) {
        os << "Error: InvalidDefinition" << endl;
        return true;
    }

    catch (Invalid_Sentence &) {
        os << "Error: Invalid_Sentence" << endl;
        return true;
    }
    catch (Graph::invalidName &) {
        os << "Error: invalidName" << endl;
        return true;
    }
    return true;
}
