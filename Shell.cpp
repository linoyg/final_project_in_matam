
#include <iostream>
#include "Graph.h"
#include "RunShell.h"

int main(int argc, char *argv[]) {
    string prompt = "Gcalc> ";
    //Automat
    if (argc == 3) {

        runAutomat(argv[1], argv[2]);
    }
        // not automat
    else {

        runNotAutomat();

    }

    return 0;
}
