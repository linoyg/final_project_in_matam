
#ifndef PROJECT_IN_MATAM_GRAPH_H
#define PROJECT_IN_MATAM_GRAPH_H

#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Graph {
private:
    string name_of_the_graph;
    set<string> vertex;
    set<pair<string, string>> edge;

public:
    //constructor
    explicit Graph(string new_graph);

    Graph(string new_graph, set<string> new_vertex, set<pair<string, string>> new_edge);

    //copy constructor
    Graph(const Graph &other) = default;

    //destructor
    ~Graph() = default;

    Graph &operator=(const Graph &) = default;

    //operators and functions
    bool operator==(const Graph &g) const;

    bool operator<(const Graph &g) const;

    friend set<string> getSetOfVertex(const Graph &g);

    friend set<pair<string, string>> getSetOfEdges(const Graph &g1);

    friend string getNameOfGraphThatExists(const Graph &g1);

    void setName(const string& name);

    void addVertex(const char* v);

    void addEdge(const char* v1,const char* v2);


    friend Graph operator+(const Graph &g1, const Graph &g2);

    friend Graph operator^(const Graph &g1, const Graph &g2);

    friend Graph operator-(const Graph &g1, const Graph &g2);

    Graph operator!();

    friend Graph operator*(const Graph &g1, const Graph &g2);


    friend void printGraph(const Graph graph_to_print, ostream &os);

    static bool checkIfForbiddenName(string s);

    static string getNameOfGraph(string name);

    static string getNameOfVertex(string name);

    static bool checkIfLegalCharInGraphName(char c);

    static bool checkIfLegalCharInVertexName(char c);

    static Graph parseImmediate(const vector<string>& words, const string& name);


    class invalidName:std::exception {};
};



#endif //PROJECT_IN_MATAM_GRAPH_H
