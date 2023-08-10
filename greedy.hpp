#ifndef _GREEDY_H_
#define _GREEDY_H_

#include <queue>

struct ComparePairs {
    bool operator()(const pair<pair<int, int>, int>& p1, const pair<pair<int, int>, int>& p2) {
        if (p1.first.first != p2.first.first) {
            return p1.first.first > p2.first.first; // Smallest first number comes first
        } else {
            return p1.first.second < p2.first.second; // Highest second number comes first
        }
    }
};

//selects the node coloration with the lowest maxValue in this step. Returns the selected color if coloring was possible and UNDEFINED if it was not. updates the avaliableColors matrix
int getNodeBestStepColor(int nodeCount, int colorCount, int** nodeAjacencyList, float* weights, int* coloration, float* totalColorWeights, int node, int* avaliableColors);

//colors the graph following the getNodeBestStepColor() heuristic. returns UNDEFINED if was not able to construct following the heuristic
int greedyConstruction(int nodeCount, int colorCount, int** nodeAjacencyList, float* weights, int* coloration, float* totalColorWeights, int* adjacentNodeQuantity, int* avaliableColors);

#endif /* _GREEDY_H_ */