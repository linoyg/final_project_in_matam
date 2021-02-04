//
// Created by linoy ganti on 8/4/2020.
//

#ifndef PROJECT_IN_MATAM_TOKENIZE_H
#define PROJECT_IN_MATAM_TOKENIZE_H

#include <vector>
#include "Graph.h"

using namespace std;

vector<string> splitSentence(const string& sentence) ;
bool findEqual(const vector<string>& words);
bool findOperator(const std::vector<std::string>& words);

class InvalidDefinition:std::exception{};

Graph PlacementOfGraph(vector<string> words);

#endif //PROJECT_IN_MATAM_TOKENIZE_H
