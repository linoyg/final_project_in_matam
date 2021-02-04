//
// Created by linoy ganti on 8/8/2020.
//

#ifndef PROJECT_IN_MATAM_RUNSHELL_H
#define PROJECT_IN_MATAM_RUNSHELL_H

void runAutomat(char *x1, char *x2);
void runNotAutomat();

class THE_GRAPH_IS_NOT_EXISTS:std::exception{};
class Invalid_Sentence:std::exception{};
#endif //PROJECT_IN_MATAM_RUNSHELL_H
