#include "Commands.h"
#include "Expression.h"

bool davidI(string perv_word,string next);

Graph getAssignedGraph(set<Graph> &set_of_graphs, const vector<string> &words) {
    //write the name of the graph.
    string name_if_new_graph = words[0];

    if (words[1] != "=") {
        throw InvalidDefinition{};
    }
    if (words.size() < 3) {
        throw InvalidDefinition{};
    }
    string expressionStr;
    string perv_word=words[1];
    for (unsigned int i = 2; i < words.size(); ++i) {
        string next=words[i];
        bool chack = davidI(perv_word,next);
        if(chack){
            expressionStr.append(" ");
        }
        perv_word=words[i];
        expressionStr.append(words[i]);
    }

    auto expression = parseExpression(expressionStr);
    Graph graph = expression->evaluate(set_of_graphs);

    graph.setName(name_if_new_graph);
    return graph;
}
bool davidI(string perv_word,string next){
if(perv_word != "{" && perv_word != "}" && perv_word != "<" && perv_word !="!" &&
perv_word != ">" &&perv_word != "," && perv_word != "+" && perv_word != "*" &&
perv_word != "^" && perv_word != "-" && perv_word != "=" && perv_word != "|" &&
perv_word != "(" && perv_word != ")") {
    if(next != "{" && next != "}"&& next != "<" && next !="!" && next != ">" && next != ","&&
        next != "+" && next != "*" &&next != "^" && next != "-"&&
        next != "=" && next != "|" && next != "(" && next != ")") {
    return true;
    }
    return false;

}
    return false;
}

void handleAssignCommand(set<Graph> &set_of_graphs, const vector<string> &vec) {
    Graph graph = getAssignedGraph(set_of_graphs, vec);
    //chang a graph that exsistd
    if (set_of_graphs.find(graph) != set_of_graphs.end()) {
        set_of_graphs.erase(graph);
        set_of_graphs.insert(graph);
    } else {
        set_of_graphs.insert(graph);
    }
}
