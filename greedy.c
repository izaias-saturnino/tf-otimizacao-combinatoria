#include <time.h>
#include <stdlib.h>

void greedyConstruction(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration){
    srand(time(NULL));
    int node = rand() % nodeCount;
    int color = rand() % colorCount;

    coloration[node] = color;

    // color every adjacent node that is not colored respecting the coloring restrictions
    // in such a way to minimize the maxColorValue at every step
    // select an adjacent node randomly
    // color its ajacent nodes
    // repeat
}