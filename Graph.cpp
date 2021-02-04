
#include "Graph.h"
#include "Tokenize.h"

// Graph
// NamedGraph
Graph::Graph(string new_graph) : name_of_the_graph(getNameOfGraph(new_graph)) {}

Graph::Graph(string new_graph, set<string> new_vertex, set<pair<string, string>> new_edge)
        : name_of_the_graph(getNameOfGraph(new_graph)) {

    for (auto &i : new_vertex) {
        if (vertex.find(i) == vertex.end()) {
            vertex.insert(getNameOfVertex(i));
        } else {
            throw invalidName{};
        }
    }

    for (auto j = new_edge.begin(); j != new_edge.end(); j++) {
        string first_word = getNameOfVertex(j->first);
        string second_word = getNameOfVertex(j->second);
        //chack if the edge is a vertex.
        if (vertex.find(first_word) != vertex.end() && vertex.find(second_word) != vertex.end()
            && first_word != second_word) {
            edge.insert(pair<string, string>(first_word, second_word));
        } else {
            throw invalidName{};
        }
    }
}

set<string> getSetOfVertex(const Graph &g1) {
    set<string> vertices_set;
    for (auto i = g1.vertex.begin(); i != g1.vertex.end(); i++) {
        vertices_set.insert(*i);
    }
    return vertices_set;
}

set<pair<string, string>> getSetOfEdges(const Graph &g1) {
    set<pair<string, string>> edges_set;
    for (auto i = g1.edge.begin(); i != g1.edge.end(); i++) {
        string x = i->first;
        string y = i->second;
        pair<string, string> z;
        z.first = x;
        z.second = y;
        edges_set.insert(z);
    }
    return edges_set;
}

string getNameOfGraphThatExists(const Graph &g1) {
    string s = g1.name_of_the_graph;
    return s;
}

void Graph::addVertex(const char* v) {
    string s= getNameOfVertex(v);
   this->vertex.insert(s);
}

void Graph::addEdge(const char* v1,const char* v2){
    if(vertex.find(v1) == vertex.end() || vertex.find(v2) == vertex.end()){
        throw invalidName{};
    }
    pair<string,string> p(v1,v2);
    this->edge.insert(p);
}


bool Graph::operator==(const Graph &g) const {
    return this->name_of_the_graph == g.name_of_the_graph ? true : false;
}


bool Graph::operator<(const Graph &g) const {
    return this->name_of_the_graph < g.name_of_the_graph;
}


Graph operator+(const Graph &g1, const Graph &g2) {
    set<string> union_vertices_set;
    set_union(g1.vertex.begin(), g1.vertex.end(), g2.vertex.begin(), g2.vertex.end(),
              inserter(union_vertices_set, union_vertices_set.begin()));
    set<pair<string, string>> union_edge_set;
    set_union(g1.edge.begin(), g1.edge.end(), g2.edge.begin(), g2.edge.end(),
              inserter(union_edge_set, union_edge_set.begin()));
    Graph x("temp", union_vertices_set, union_edge_set);
    return x;
}


Graph operator^(const Graph &g1, const Graph &g2) {
    set<string> union_vertices_set;
    set_intersection(g1.vertex.begin(), g1.vertex.end(), g2.vertex.begin(), g2.vertex.end(),
                     inserter(union_vertices_set, union_vertices_set.begin()));
    set<pair<string, string>> union_edge_set;
    set_intersection(g1.edge.begin(), g1.edge.end(), g2.edge.begin(), g2.edge.end(),
                     inserter(union_edge_set, union_edge_set.begin()));
    Graph x("temp", union_vertices_set, union_edge_set);
    return x;
}

Graph operator-(const Graph &g1, const Graph &g2) {
    set<string> union_vertices_set;
    set_difference(g1.vertex.begin(), g1.vertex.end(), g2.vertex.begin(), g2.vertex.end(),
                   inserter(union_vertices_set, union_vertices_set.begin()));
    set<pair<string, string>> union_edge_set;
    set_difference(g1.edge.begin(), g1.edge.end(), g2.edge.begin(), g2.edge.end(),
                   inserter(union_edge_set, union_edge_set.begin()));

    set<pair<string, string>> rigth_edge_set;
    rigth_edge_set = union_edge_set;
    for (auto j = union_edge_set.begin(); j != union_edge_set.end(); j++) {
        //chack if the edge is a vertex.
        if (union_vertices_set.find(j->first) == union_vertices_set.end() ||
            union_vertices_set.find(j->second) == union_vertices_set.end()) {
            rigth_edge_set.erase(pair<string, string>(j->first, j->second));
        }
    }

    Graph x("temp", union_vertices_set, rigth_edge_set);
    return x;
}

Graph operator*(const Graph &g1, const Graph &g2) {
    //new set of vertex
    set<string> mult_vertices_set;
    for (auto i = g1.vertex.begin(); i != g1.vertex.end(); i++) {
        for (auto j = g2.vertex.begin(); j != g2.vertex.end(); j++) {
            string x = '[' + *i + ';' + *j + ']';
            mult_vertices_set.insert(x);
        }
    }
    //new set of edge
    set<pair<string, string>> mult_edge_set;
    for (auto i = g1.edge.begin(); i != g1.edge.end(); i++) {
        for (auto j = g2.edge.begin(); j != g2.edge.end(); j++) {
            string x = '[' + i->first + ';' + j->first + ']';
            string y = '[' + i->second + ';' + j->second + ']';
            pair<string, string> z;
            z.first = x;
            z.second = y;
            mult_edge_set.insert(z);
        }
    }
    Graph w("temp", mult_vertices_set, mult_edge_set);
    return w;
}


Graph Graph::operator!() {
    for (auto i = this->vertex.begin(); i != this->vertex.end(); i++) {
        for (auto j = this->vertex.begin(); j != this->vertex.end(); j++) {
            pair<string, string> x1;
            x1.first = *i;
            x1.second = *j;
            //chack if the edge is in the graph if it is delete him.
            if (this->edge.find(x1) != this->edge.end()) {
                this->edge.erase(x1);
            } else {
                if (i != j) {
                    this->edge.insert(x1);
                }
            }

        }
    }
    return *this;

}


void printGraph(const Graph graph_to_print, ostream &os) {
    for (const auto &i : graph_to_print.vertex) {
        os << i << endl;
    }

    os << "$" << endl;

    for (auto j = graph_to_print.edge.begin(); j != graph_to_print.edge.end(); j++) {
        os << j->first << " " << j->second << endl;
    }
}

bool Graph::checkIfForbiddenName(string s) {
    return s == "print" || s == "delete" || s == "who" || s == "reset" || s == "quit" || s == "save" || s == "load";
}

bool Graph::checkIfLegalCharInGraphName(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || ('0' <= c && c <= '9');
}

bool Graph::checkIfLegalCharInVertexName(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || ('0' <= c && c <= '9') || c == '[' || c == ']' ||
           c == ';';
}


string Graph::getNameOfGraph(string name) {
    if ('0' <= name[0] && name[0] <= '9') {
        throw Graph::invalidName{};
    }
    if (checkIfForbiddenName(name)) {
        throw Graph::invalidName{};
    }
    for (unsigned int i = 0; i < name.length(); i++) {
        char cr = name[i];
        if (checkIfLegalCharInGraphName(cr) == false) {
            throw Graph::invalidName{};
        }
    }
    return name;
}


string Graph::getNameOfVertex(string name) {
    //check if the word is ok.
    int count_of_parenthesis = 0;
    for (unsigned int count_of_char = 0; count_of_char < name.length(); count_of_char++) {
        char i = name[count_of_char];
        if (!checkIfLegalCharInVertexName(i)) {
            throw invalidName{};
        }
        if (i == '[') {
            count_of_parenthesis++;
        }
        if (i == ']') {
            if (count_of_parenthesis > 0) {
                count_of_parenthesis--;
            } else {
                throw invalidName{};
            }
        }
        if (i == ';') {
            if (count_of_parenthesis > 0) {
                continue;
            }
            throw invalidName{};
        }
        if (count_of_char == name.length() - 1) {
            if (count_of_parenthesis != 0) {
                throw invalidName{};
            }
        }
    }
    if (count_of_parenthesis != 0) {
        throw invalidName{};
    }
    return name;
}

Graph Graph::parseImmediate(const vector<string> &words, const string &name) {
    //write the name of the graph.
    string name_if_new_graph = name;

    if (words[0] != "{") {
        throw InvalidDefinition{};
    }

    if (words[words.size() - 1] != "}") {
        throw InvalidDefinition{};
    }
    //empty graph.
    if (words.size() == 2) {
        Graph g1(name_if_new_graph);
        return g1;
    }
    //definition a  new Graph
    set<string> vertex;
    set<pair<string, string>> edge;

    unsigned int index_of_edges = 0;
    for (unsigned int i = 1; i < words.size(); i++) {
        if (i % 2 == 1 && words[i] != ",") {
            if (vertex.find(words[i]) != vertex.end()) {
                throw Graph::invalidName{};
            }
            vertex.insert(words[i]);
            continue;
        }
        if (words[i] == "," && i % 2 == 0) {
            continue;
        }
        if (words[i] == "|" && i % 2 == 0) {
            index_of_edges = i;
            break;
        }
        if (words[i] == "}" && i == words.size() - 1) {
            Graph g1(name_if_new_graph, vertex, edge);
            return g1;
        }

        throw InvalidDefinition{};
    }

    //check if there is only vertex.
    if (index_of_edges == words.size() - 2) {
        Graph g1(name_if_new_graph, vertex, edge);
        return g1;
    }

    string string_first;
    string string_second;

    for (unsigned int i = index_of_edges + 1; i < words.size(); i = i + 6) {

        if (words[i] == "<" && words[i + 2] == "," && words[i + 4] == ">" && words[i + 5] == ",") {
            string_first = words[i + 1];
            string_second = words[i + 3];
            edge.insert(pair<string, string>(string_first, string_second));
            continue;
        }
        if (words[i] == "<" && words[i + 2] == "," && words[i + 4] == ">" && words[i + 5] == "}") {
            string_first = words[i + 1];
            string_second = words[i + 3];
            edge.insert(pair<string, string>(string_first, string_second));
            break;
        }

        throw InvalidDefinition{};

    }
    Graph g1(name_if_new_graph, vertex, edge);
    return g1;
}

void Graph::setName(const string &name) {
    name_of_the_graph = getNameOfGraph(name);
}

