
#ifndef PROJECT_IN_MATAM_PYGRAPH_H
#define PROJECT_IN_MATAM_PYGRAPH_H

#include "Graph.h"


Graph* create();
void destroy(Graph* graph);
Graph* addVertex(Graph* graph,const char* v);
Graph* addEdge(Graph* graph ,const char* v1,const char* v2);
void disp(Graph* g);
Graph* graphUnion(Graph* graph_in1,Graph* graph_in2,Graph* graph_out);
Graph* graphIntersection(Graph* graph_in1,Graph* graph_in2,Graph* graph_out);
Graph* graphDifference(Graph* graph_in1,Graph* graph_in2,Graph* graph_out);
Graph* graphProduct(Graph* graph_in1,Graph* graph_in2,Graph* graph_out);
Graph* graphComplement(Graph* graph_in, Graph* graph_out);
#endif //PROJECT_IN_MATAM_PYGRAPH_H
