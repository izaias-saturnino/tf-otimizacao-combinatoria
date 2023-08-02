#include <time.h>
#include <stdlib.h>

void greedyConstruction(int nodeCount, int colorCount, int** nodeAjacencyList, int* weights, int* coloration){
    srand(time(NULL));
    int node = rand() % nodeCount;
    int color = rand() % colorCount;

    coloration[node] = color;

    for (int i = 0; i < nodeCount; i++)
    {
        //color every adjacent node that is not colored respecting the coloring restrictions
    }
    // select an adjacent node randomly
    // color its ajacent nodes
    // repeat
}