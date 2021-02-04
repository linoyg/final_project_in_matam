#include "PyGraph.h"
#include "Graph.h"

Graph *create() {
    Graph* ptr= nullptr;
    try {
        ptr = new Graph("temp");
    }
    catch (Graph::invalidName &) {
        cout << "Error: invalidName" << endl;
    }
    return ptr;
}

void destroy(Graph *graph) {
    try {
        delete graph;
    }
    catch (Graph::invalidName &) {
        cout << "Error: invalidName" << endl;
    }
}

Graph *addVertex(Graph *graph, const char* v) {
    try {
        graph->addVertex(v);
    }
    catch (Graph::invalidName &) {
        cout << "Error: invalidName" << endl;
    }
    return graph;
}

Graph* addEdge(Graph* graph ,const char* v1,const char* v2){
    try {
        graph->addEdge(v1, v2);
    }
    catch (Graph::invalidName &) {
        cout << "Error: invalidName" << endl;
    }
    return graph;
}

void disp(Graph* g){
    printGraph(*g,cout);
}

Graph* graphUnion(Graph* graph_in1, Graph* graph_in2, Graph* graph_out){
    try {
        *graph_out = (*graph_in1) + (*graph_in2);

    }
    catch (Graph::invalidName &) {
        cout << "Error: invalidName" << endl;
    }
    return graph_out;
}

Graph* graphIntersection(Graph* graph_in1, Graph* graph_in2, Graph* graph_out){
    try {
        *graph_out = (*graph_in1) ^ (*graph_in2);

    }
    catch (Graph::invalidName &) {
            cout << "Error: invalidName" << endl;
    }
    return graph_out;
}

Graph* graphDifference(Graph* graph_in1, Graph* graph_in2, Graph* graph_out){
    try {
        *graph_out=(*graph_in1)-(*graph_in2);
    }
    catch (Graph::invalidName &) {
        cout << "Error: invalidName" << endl;
    }
    return graph_out;

}

Graph* graphProduct(Graph* graph_in1, Graph* graph_in2, Graph* graph_out){
    try {
        *graph_out=(*graph_in1)*(*graph_in2);

    }
    catch (Graph::invalidName &) {
        cout << "Error: invalidName" << endl;
    }
    return graph_out;
}

Graph* graphComplement(Graph* graph_in, Graph* graph_out){
    try {
        *graph_out=!(*graph_in);

    }
    catch (Graph::invalidName &) {
        cout << "Error: invalidName" << endl;
    }
    return graph_out;
}

